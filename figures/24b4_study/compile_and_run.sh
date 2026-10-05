#!/bin/bash

export PATH=/data/lhcb/users/lins/u3_PIDQuantify/bin:$PATH
source /cvmfs/sft.cern.ch/lcg/views/LCG_108a_LHCB_Core/x86_64-el9-gcc13-opt/setup.sh

g++ -O3 "${1:-plot_24b4_partitions.cc}" -o .executable $(root-config --cflags --libs) $(PIDQuantify-config)
./.executable
