#!/bin/bash
set -eo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export PATH=/data/lhcb/users/lins/u3_PIDQuantify/bin:$PATH
source /cvmfs/sft.cern.ch/lcg/views/LCG_108a_LHCB_Core/x86_64-el9-gcc13-opt/setup.sh

g++ -O3 "$script_dir/plot_26c2d_comparison.cc" -o "$script_dir/.executable_26c2d" \
    $(root-config --cflags --libs) $(PIDQuantify-config)
cd "$script_dir"
./.executable_26c2d
