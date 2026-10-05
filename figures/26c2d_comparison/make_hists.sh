#!/bin/bash
# Rebuild the 2D 26c2d finals histograms without overwriting the previous set.
set -eo pipefail

TARGET="${1:?usage: $0 L0|Lc}"

case "$TARGET" in
    L0)
        PARTICLE=P
        OUTPUT_DIR=/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/26c2dcheck_L0/newL0
        ;;
    Lc)
        PARTICLE=P_Lc
        OUTPUT_DIR=/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/26c2dcheck_Lc/Lc
        ;;
    *)
        echo "Expected L0 or Lc, got: $TARGET" >&2
        exit 2
        ;;
esac

cd /home/lins/u6_PIDCalib2/src
export X509_USER_PROXY="$PWD/proxy"
chmod 600 "$X509_USER_PROXY"
source /cvmfs/lhcb.cern.ch/lib/LbEnv

SAMPLE=2026_c2_v0
POLARITY=down
BINNING_SCHEME=/home/lins/u6_PIDCalib2/src/bin_scheme_hi_stats_sim.json
mkdir -p "$OUTPUT_DIR"

CUT_LABELS=("DLLp>" "DLLp-DLLK>" "DLLp<" "DLLp-DLLK<")
CUT_VALUES=($(seq -f '%.1f' -50 0.5 50))
HIST_ARGS=()
CUT_STRINGS=()
for cut in "${CUT_VALUES[@]}"; do
    for label in "${CUT_LABELS[@]}"; do
        HIST_ARGS+=(-i "${label}${cut}")
        CUT_STRINGS+=("${label}${cut}")
    done
done

lb-conda pidcalib python3 -m pidcalib2.make_eff_hists \
    -s "$SAMPLE" -m "$POLARITY" -p "$PARTICLE" \
    -g "$BINNING_SCHEME" -b P -b ETA -o "$OUTPUT_DIR" \
    "${HIST_ARGS[@]}"

for cut in "${CUT_STRINGS[@]}"; do
    pkl="$OUTPUT_DIR/effhists-$SAMPLE-$POLARITY-$PARTICLE-$cut-P.ETA.pkl"
    [[ -f "$pkl" ]] || { echo "Missing histogram pickle: $pkl" >&2; exit 1; }
    lb-conda pidcalib python3 -m pidcalib2.pklhisto2root "$pkl"
done

echo "DONE: $TARGET -> $OUTPUT_DIR"
