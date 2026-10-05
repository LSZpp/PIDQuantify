#!/bin/bash
# Build the local, sWeighted TH1D inputs before drawing plot_probnn_distributions.C.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
STUDY_DIR="${PROBNN_STUDY_DIR:-/data/lhcb/users/lins/u3_PIDQuantify/PROBNN_study}"
THREADS="${1:-64}"
MANIFEST="$SCRIPT_DIR/sweight_manifest_25c4_magup.tsv"
HISTOGRAMS="$SCRIPT_DIR/sweighted_probnn_kinematics_25c4_magup_positive.root"

if [[ ! "$THREADS" =~ ^[1-9][0-9]*$ ]]; then
    echo "Usage: $(basename "$0") [THREADS]   (default 64)" >&2
    exit 1
fi

stage() {
    echo
    echo "=== $* ==="
}

stage "Setting up the LHCb environment"
source "$STUDY_DIR/PIDCalib2_path.txt"
set +u
source /cvmfs/lhcb.cern.ch/lib/LbEnv
set -u

# Use the renewed interactive proxy, not the archived study proxy.
if [[ -f "/tmp/x509up_u$(id -u)" ]]; then
    export X509_USER_PROXY="/tmp/x509up_u$(id -u)"
fi

# Keep APD's cache writable without changing the user's authentication token.
export APD_METADATA_CACHE_DIR="$SCRIPT_DIR/.apd_metadata_cache"
export APD_METADATA_LIFETIME="${APD_METADATA_LIFETIME:-2592000}"
if [[ ! -d "$APD_METADATA_CACHE_DIR/pid" && -d "$HOME/.cache/apd" ]]; then
    mkdir -p "$APD_METADATA_CACHE_DIR"
    cp -a "$HOME/.cache/apd/." "$APD_METADATA_CACHE_DIR/"
fi

stage "Building the APD manifest (calibration tuples and their sWeight files)"
lb-conda pidcalib python3 "$SCRIPT_DIR/make_sweight_manifest.py" --output "$MANIFEST"

stage "Compiling build_sweighted_probnn_hists"
g++ -O3 -std=c++17 -pthread "$SCRIPT_DIR/build_sweighted_probnn_hists.cc" \
    -o "$SCRIPT_DIR/build_sweighted_probnn_hists" $(root-config --cflags --libs)
echo "Compiled $SCRIPT_DIR/build_sweighted_probnn_hists"

stage "Applying sWeights and filling the TH1Ds on $THREADS threads"
"$SCRIPT_DIR/build_sweighted_probnn_hists" --manifest "$MANIFEST" \
    --output "$HISTOGRAMS" --threads "$THREADS"

# The ROOT file already exists at this point, independently of any plotting failure.
stage "Drawing the distributions"
cd "$SCRIPT_DIR"
root -l -b -q 'plot_probnn_distributions.C("positive")'

stage "Done"
echo "Histograms: $HISTOGRAMS"
ls -1 "$SCRIPT_DIR"/pdf_figure_probnn_distributions_25c4_magup_positive_*.pdf
