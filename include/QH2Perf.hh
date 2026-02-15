#ifndef QH2PERF_HH
#define QH2PERF_HH


// The QH2Perf class 
// LSZ 15 Feb 25

// A class inherited from QH2, which stores the 1-dimensional projections of the efficiencies
// This object is exactly what is needed for performance histograms

#include "QH2.hh"

#include "TH1D.h"
#include "TGraphErrors.h"

class QH2Perf : public QH2{
private:
    // total and passed histograms with p or eta as the vertical and horizontal axes
    TH1D *_total_p    = nullptr; 
    TH1D *_total_eta  = nullptr; 
    TH1D *_passed_p   = nullptr; 
    TH1D *_passed_eta = nullptr; 

    // efficiencies for p and eta (these are the performance histograms to be plotted) 
    TGraphErrors *_eff_p   = nullptr;
    TGraphErrors *_eff_eta = nullptr;

    void _project();       // projects the 2d histograms into 1d histograms
    void _calculate_eff(); // divides the passed histograms by the total histograms to get the efficiencies

public: 
    QH2Perf(const std::string &batch,
            const std::string &polarity,
            const std::string &first_particle,
            const std::string &second_particle,
            const std::string &identification_type,
            const double       cut_value,
            const std::string &directory);
            //constructor
    
    // getters for the efficiencies
    TGraphErrors *eff_p()   const;
    TGraphErrors *eff_eta() const;

    virtual ~QH2Perf();  // destructor
};

#endif
