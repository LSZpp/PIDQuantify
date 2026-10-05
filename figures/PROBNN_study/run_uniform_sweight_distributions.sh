#!/bin/bash
# Run the three independent PIDCalib2 sWeighted distribution jobs concurrently.
set +u
set -eo pipefail

# LbEnv provides the Python interpreter used by lb-conda.  An active virtual
# environment or PYTHONHOME can hide its bundled LbCondaWrappers package.
unset PYTHONHOME PYTHONPATH VIRTUAL_ENV CONDA_PREFIX CONDA_DEFAULT_ENV

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BINNING_FILE="$SCRIPT_DIR/binning_uniform_sweights.json"

case "${1:-2025}" in
    2025)
        SAMPLE="2025_c4_v0"
        PARTICLES=(P_Lc K Pi)
        MAX_FILES_ARGS=()
        DEFAULT_OUTPUT_DIR="$SCRIPT_DIR/pidcalib_sweights_uniform_25c4_magup_positive"
        ;;
    2017)
        SAMPLE="Turbo17"
        PARTICLES=(P_IncLc K Pi)
        MAX_FILES_ARGS=(--max-files 60)
        DEFAULT_OUTPUT_DIR="$SCRIPT_DIR/pidcalib_sweights_uniform_Turbo17_magup_positive"
        ;;
    *)
        echo "Usage: $(basename "$0") [2025|2017]" >&2
        exit 2
        ;;
esac
OUTPUT_DIR="${OUTPUT_DIR:-$DEFAULT_OUTPUT_DIR}"

source /data/lhcb/users/lins/u3_PIDQuantify/PROBNN_study/PIDCalib2_path.txt
source /cvmfs/lhcb.cern.ch/lib/LbEnv

lb_conda_path="$(command -v lb-conda)"
lb_conda_python="$(sed -n '1s/^#!//p' "$lb_conda_path")"
"$lb_conda_python" -c 'import LbCondaWrappers'

proxy_file="${X509_USER_PROXY:-/tmp/x509up_u$(id -u)}"
if [[ -f "$proxy_file" ]]; then
    export X509_USER_PROXY="$proxy_file"
elif [[ -f "$PROBNN_PROXY_FILE" ]]; then
    export X509_USER_PROXY="$PROBNN_PROXY_FILE"
else
    echo "No X.509 proxy found at $proxy_file or $PROBNN_PROXY_FILE" >&2
    exit 1
fi

mkdir -p "$OUTPUT_DIR/logs"

run_particle() {
    local particle="$1"
    local particle_dir="$OUTPUT_DIR/$particle"
    local log_file="$OUTPUT_DIR/logs/$particle.log"
    local apd_cache="$particle_dir/.apd_metadata_cache"

    (
        mkdir -p "$particle_dir" "$particle_dir/.matplotlib" "$apd_cache"
        if [[ ! -d "$apd_cache/pid" && -d "$HOME/.cache/apd" ]]; then
            cp -a "$HOME/.cache/apd/." "$apd_cache/"
        fi
        export MPLCONFIGDIR="$particle_dir/.matplotlib"
        export APD_METADATA_CACHE_DIR="$apd_cache"
        export APD_METADATA_LIFETIME="${APD_METADATA_LIFETIME:-2592000}"
        cd "$PIDCalib2_SRC"
        lb-conda pidcalib pidcalib2.plot_calib_distributions \
            --sample "$SAMPLE" --magnet up --particle "$particle" \
            --bin-var P --bin-var ETA --binning-file "$BINNING_FILE" \
            --cut "trackcharge>0" --format pdf --output-dir "$particle_dir" \
            "${MAX_FILES_ARGS[@]}"
        lb-conda pidcalib pidcalib2.pklhisto2root \
            "$particle_dir/plot_calib_distributions.pkl"
    ) >"$log_file" 2>&1 &
    jobs+=("$!:$particle:$log_file")
}

declare -a jobs=()
for particle in "${PARTICLES[@]}"; do
    run_particle "$particle"
done

status=0
for job in "${jobs[@]}"; do
    IFS=: read -r pid particle log_file <<<"$job"
    if wait "$pid"; then
        echo "$particle completed: $log_file"
    else
        echo "$particle failed; see $log_file" >&2
        status=1
    fi
done

exit "$status"
