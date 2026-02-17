#ifndef QROCCURVE_HH
#define QROCCURVE_HH

// The QROCCurve class
// LSZ 17 Feb 26

// A class that creates and stores a single ROCcurve

#include "TGraphErrors.h"

#include <string>

class QROCCurve{
private:
    TGraphErrors *_curve = nullptr; // the ROC curve 

    // information about the points on the ROC curve
    const double _loosest_cut;
    const double _strictest_cut;
    const double _cut_interval;

    // particles within the ROC curve
    const std::string first_particle; 
    const std::string second_particle;

public:
    QROCCurve(const std::string &batch,
              const std::string &polarity,
              const std::string &first_particle,
              const std::string &second_particle,
              const double       loosest_cut,
              const double       strictest_cut,
              const double       cut_interval,
              const std::string &directory);
                    // constructor

    TGraphErrors *get_curve() const;

    ~QROCCurve();       // destructor
};

#endif
