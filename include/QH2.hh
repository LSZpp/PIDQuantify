#ifndef QH2_HH
#define QH2_HH

// The QH2 class 
// LSZ 14 Feb 25

// A class storing a particular efficiency histogram binned in momentum and pseudorapidity and its settings

#include "QProperty.hh"

#include "TH2D.h"

#include <string> 
#include <iostream>

class QH2{
protected:
    TH2D        *_total    = nullptr; // histogram for all particles used for calibration
    TH2D        *_passed   = nullptr; // histogram for particles passing the cut
    QProperty   *_property = nullptr; // the property of the histogram
    std::string  _path;               // the full path to the histogram including the file name

public:
    QH2(const std::string &batch,
        const std::string &polarity,
        const std::string &first_particle,
        const std::string &second_particle,
        const std::string &identification_type,
        const double       cut_value,
        const std::string &directory);
                     // constructor

    ~QH2();          // destructor
};

#endif
