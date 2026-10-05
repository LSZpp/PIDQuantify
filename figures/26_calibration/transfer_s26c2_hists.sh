#!/bin/bash
# Transfer bovill's 2026_s26c2_beta_fixed efficiency histograms (2d, MagUp, K & Pi)
# into finals_hists, renaming to the local convention (drop -binning_scheme_George),
# then convert every copied .pkl to .root using 30 parallel workers.
set -euo pipefail

SRC="/data/lhcb/users/bovill/2025_data/PID_Calibration/eff_hists/2026_s26c2_beta_fixed"
DEST_BASE="/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d"
PYTHON="/home/lins/u6_PIDCalib2/src/pidcalib_dev/bin/python"
NJOBS=30

# Sample name used in the copied filenames.
# Leave as-is to keep bovill's name, or set e.g. "2026_c2_v0" to match your other 2026 sets.
NEW_SAMPLE="2026_s26c2_beta_fixed"

export DEST_BASE PYTHON NEW_SAMPLE

mkdir -p "$DEST_BASE/K" "$DEST_BASE/Pi"

# ---- 1+2) parallel copy with rename ----------------------------------------
# effhists-2026_s26c2_beta_fixed-up-<particle>-<cut>-P.ETA-binning_scheme_George.pkl
#   -> $DEST_BASE/<particle>/effhists-$NEW_SAMPLE-up-<particle>-<cut>-P.ETA.pkl
echo ">> Copying + renaming $(find "$SRC" -name '*.pkl' | wc -l) pkl files with $NJOBS workers..."
find "$SRC" -name '*.pkl' -print0 |
  xargs -0 -P "$NJOBS" -n 1 bash -c '
    f="$1"
    base="${f##*/}"
    particle="$(printf "%s" "$base" | cut -d- -f4)"          # effhists-<sample>-<mag>-<particle>-...
    new="${base/-binning_scheme_George/}"
    new="${new/2026_s26c2_beta_fixed/$NEW_SAMPLE}"
    cp -n "$f" "$DEST_BASE/$particle/$new"
  ' _

# ---- 3) parallel pkl -> ROOT conversion (30 cores) --------------------------
echo ">> Converting pkl -> root with $NJOBS workers..."
find "$DEST_BASE/K" "$DEST_BASE/Pi" -name "effhists-${NEW_SAMPLE}-*.pkl" -print0 |
  xargs -0 -P "$NJOBS" -n 1 bash -c '
    root="${1%.pkl}.root"
    [ -f "$root" ] || "$PYTHON" -m pidcalib2.pklhisto2root "$1" >/dev/null 2>&1 \
      || echo "FAILED: $1"
  ' _

# ---- summary ----------------------------------------------------------------
for p in K Pi; do
  npkl=$(find "$DEST_BASE/$p" -name "effhists-${NEW_SAMPLE}-*.pkl" | wc -l)
  nroot=$(find "$DEST_BASE/$p" -name "effhists-${NEW_SAMPLE}-*.root" | wc -l)
  echo "$p : $npkl pkl, $nroot root"
done
echo "Done."
