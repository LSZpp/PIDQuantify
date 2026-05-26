source /cvmfs/sft.cern.ch/lcg/views/LCG_108a_LHCB_Core/x86_64-el9-gcc13-opt/setup.sh

mkdir -p build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/data/lhcb/users/lins/u3_PIDQuantify
make -j20
make install
