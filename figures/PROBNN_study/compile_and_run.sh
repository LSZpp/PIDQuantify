#!/bin/bash
set -eo pipefail

export PATH=/data/lhcb/users/lins/u3_PIDQuantify/bin:$PATH
source /cvmfs/sft.cern.ch/lcg/views/LCG_108a_LHCB_Core/x86_64-el9-gcc13-opt/setup.sh

source_file="${1:-ROC_probnn_study.cc}"
shift || true

g++ -O3 "$source_file" -o .executable $(root-config --cflags --libs) $(PIDQuantify-config)
./.executable "$@"
