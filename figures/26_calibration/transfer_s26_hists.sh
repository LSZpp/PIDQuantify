#!/bin/bash
# Replace the 2026 K/Pi histograms with bovill's fresh George-binning outputs,
# then recreate the matching ROOT files.  No 2025 or proton inputs are touched.

SRC_BASE="/data/lhcb/users/bovill/2025_data/PID_Calibration/eff_hists"
DEST_BASE="/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d"
NJOBS="${NJOBS:-30}"
TAGS=(s26c1 s26c2)

# Match the production efficiency scripts: avoid inheriting a foreign ROOT or
# Python stack, then use the PIDCalib conda environment through LbEnv.
unset PYTHONHOME PYTHONPATH ROOTSYS LD_LIBRARY_PATH CMAKE_PREFIX_PATH
source /cvmfs/lhcb.cern.ch/lib/LbEnv

for tag in "${TAGS[@]}"; do
  src="${SRC_BASE}/2026_${tag}_beta_fixed"
  total=$(find "$src" -maxdepth 1 -type f -name '*-binning_scheme_George.pkl' | wc -l)
  fresh=$(find "$src" -maxdepth 1 -type f -name '*-binning_scheme_George.pkl' -mmin -1440 | wc -l)
  [ "$total" -eq 4008 ] && [ "$fresh" -eq "$total" ]

  echo ">> Replacing $tag: $total fresh George-binning K/Pi pickles"
  find "$src" -maxdepth 1 -type f -name '*-binning_scheme_George.pkl' -print0 |
    xargs -0 -P "$NJOBS" -n 1 bash -c '
      f="$1"
      base="${f##*/}"
      particle="$(printf "%s" "$base" | cut -d- -f4)"
      new="${base/-binning_scheme_George/}"
      cp -f "$f" "'$DEST_BASE'/$particle/$new"
    ' _
done

for tag in "${TAGS[@]}"; do
  echo ">> Recreating ROOT files for $tag"
  find "$DEST_BASE/K" "$DEST_BASE/Pi" -maxdepth 1 -type f \
    -name "effhists-2026_${tag}_beta_fixed-*.pkl" -print0 |
    xargs -0 -P "$NJOBS" -n 1 lb-conda pidcalib python3 -m pidcalib2.pklhisto2root >/dev/null

  for particle in K Pi; do
    pkl=$(find "$DEST_BASE/$particle" -maxdepth 1 -type f -name "effhists-2026_${tag}_beta_fixed-*.pkl" | wc -l)
    root=$(find "$DEST_BASE/$particle" -maxdepth 1 -type f -name "effhists-2026_${tag}_beta_fixed-*.root" | wc -l)
    printf '%s %s: %s pkl, %s root\n' "$tag" "$particle" "$pkl" "$root"
  done
done
