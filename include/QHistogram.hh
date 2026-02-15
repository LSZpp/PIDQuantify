#ifndef QHISTOGRAM_HH
#define QHISTOGRAM_HH

// The QHistogram class 
// LSZ 14 Feb 25

// A class storing a particular efficiency histogram and its setting

#include "QProperty.hh"

#include "TH2D.h"

#include <string> 
#include <iostream>

class QHistogram{
protected:
    TH2D        *_total    = nullptr; // histogram for all particles used for calibration
    TH2D        *_passed   = nullptr; // histogram for particles passing the cut
    QProperty   *_property = nullptr; // the property of the histogram
    std::string  _path;               // the full path to the histogram including the file name

public:
    QHistogram(const std::string &batch,
               const std::string &polarity,
               const std::string &first_particle,
               const std::string &second_particle,
               const std::string &identification_type,
               const double       cut_value,
               const std::string &directory);
                     // constructor

    ~QHistogram();   // destructor
};

#endif
