#!/bin/bash
###########################################################################
# Publish a PUBLIC, SCRUBBED mirror of this repository to GitHub.           #
#                                                                          #
# The CERN plot data - ROOT canvas dumps (macro_*.C, from                   #
# TCanvas::SaveSource) and the figure PDFs (*.pdf) - is stripped from the    #
# ENTIRE git history, an exclusion .gitignore is added, and the result is    #
# FORCE-PUSHED to GitHub. The canonical, COMPLETE repository (with the data) #
# lives on GitLab as the `origin` remote and is never touched by this script.#
#                                                                          #
# Usage:  ./publish-github.sh            (re-run whenever GitHub should be   #
#                                         refreshed from the GitLab master)  #
#                                                                          #
# NOTE: this rewrites history and force-pushes. Anything previously public   #
# on GitHub may still survive in forks / cached views; for a guaranteed      #
# purge of old unreachable commits, also ask GitHub Support to run GC.       #
###########################################################################
set -euo pipefail

SRC="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"   # this (GitLab) repo
GITHUB_URL="git@github.com:LSZpp/PIDQuantify.git"
BRANCH="master"

WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT

echo "==> cloning local repo into a scratch mirror (originals untouched)"
git clone --no-hardlinks "$SRC" "$WORK/mirror"
cd "$WORK/mirror"

echo "==> stripping CERN data (macro_*.C, *.pdf) from ALL history"
export FILTER_BRANCH_SQUELCH_WARNING=1
git filter-branch --force --prune-empty --index-filter '
    git rm -r --cached --ignore-unmatch "*macro_*.C" "*.pdf"
' --tag-name-filter cat -- --all

echo "==> dropping filter-branch backup refs (refs/original) and repacking"
git for-each-ref --format='%(refname)' refs/original/ \
    | xargs -r -n1 git update-ref -d
git reflog expire --expire=now --all
git gc --prune=now --quiet

echo "==> adding the exclusion .gitignore to the mirror"
{
  echo ""
  echo "# CERN plot data - kept on GitLab only, never on this public mirror."
  echo "macro_*.C"
  echo "*.pdf"
} >> .gitignore
git add .gitignore
git commit -m "Public mirror: exclude CERN plot data (macro_*.C, *.pdf)"

echo "==> verifying no data files remain in the $BRANCH history (the pushed branch)"
LEAK="$(git log "$BRANCH" --pretty=format: --name-only -- '*macro_*.C' '*.pdf' | sort -u | grep -c . || true)"
if [[ "$LEAK" -ne 0 ]]; then
    echo "ABORT: $LEAK CERN data file(s) still present in $BRANCH history:" >&2
    git log "$BRANCH" --pretty=format: --name-only -- '*macro_*.C' '*.pdf' | sort -u | head >&2
    exit 1
fi
echo "    OK: 0 macro_*.C / *.pdf in the scrubbed $BRANCH history"

echo "==> force-pushing scrubbed mirror to GitHub ($BRANCH)"
git push --force "$GITHUB_URL" "$BRANCH:$BRANCH"

echo "DONE: scrubbed public mirror pushed to $GITHUB_URL"
