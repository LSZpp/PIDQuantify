

Documentation: PIDQuantify
========================================================

    LSZ      14 Feb 26


This very short code base creates performance and ROC curves for particle identification at the LHCb experiment. 

It takes the output of the histograms of the PIDCalib2 software from LHCb for different cuts, and is able to perform standard analyses of these histograms to create 1-dimensional performance histograms and ROC curves.

This visualisation tool displays the efficiency of the LHCb detector correctly identifying a charged particle together with the misidentification rate of it misidentifying a charged particle into a different type of charged particle.

The only dependency of this small package is ROOT.


installation
------------------------
This should be the same for any other project: simply create a build directory 
```
mkdir -p build
cd build
```
Then make with cmake
```
cmake .. -DCMAKE_INSTALL_PREFIX=/your/current/directory
make -j20
make install
```

usage
------------------------
Simple examples for the 2024 and 2025 cases can be found inside the /figures directory (not ready yet)
