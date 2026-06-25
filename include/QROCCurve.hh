#ifndef QROCCURVE_HH
#define QROCCURVE_HH

// The QROCCurve class
// LSZ 17 Feb 26

// A class that creates and stores a single ROCcurve

#include "QH2.hh"
#include "QHistogramSource.hh"

#include "TGraphErrors.h"

#include <string>
#include <vector>
#include <utility>

class QROCCurve{
private:
    TGraphErrors *_curve = nullptr; // the ROC curve 

    // information about the points on the ROC curve
    const double _loosest_cut;
    const double _strictest_cut;
    const double _cut_interval;

    // particles within the ROC curve
    const std::string _first_particle; 
    const std::string _second_particle;

    // calculation of efficiencies
    std::pair<double, double> _calculate_efficiency(const QH2 &hist);
        // first  returned value is efficiency 
        // second returned value is the binomial error on the efficiency

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

    QROCCurve(const std::string &batch,
              const std::string &polarity,
              const std::string &first_particle,
              const std::string &second_particle,
              const double       loosest_cut,
              const double       strictest_cut,
              const double       cut_interval,
              const QHistogramSource &source);
                    // constructor overload with a shared histogram source resolver

    QROCCurve(const std::string &batch,
              const std::string &polarity,
              const std::string &first_particle,
              const std::string &second_particle,
              const double       loosest_cut,
              const double       strictest_cut,
              const double       cut_interval,
              const QHistogramSource &id_source,
              const QHistogramSource &misid_source);
                    // constructor overload with separate ID and misID source resolvers

    QROCCurve(const std::vector<std::string> &batches,
              const std::vector<std::string> &polarities,
              const std::string &first_particle,
              const std::string &second_particle,
              const double       loosest_cut,
              const double       strictest_cut,
              const double       cut_interval,
              const std::string &directory);
                    // constructor overload: create a ROC curve built from vector of different batches

    QROCCurve(const std::vector<std::string> &batches,
              const std::vector<std::string> &polarities,
              const std::string &first_particle,
              const std::string &second_particle,
              const double       loosest_cut,
              const double       strictest_cut,
              const double       cut_interval,
              const QHistogramSource &source);
                    // constructor overload with a shared histogram source resolver

    QROCCurve(const std::vector<std::string> &batches,
              const std::vector<std::string> &polarities,
              const std::string &first_particle,
              const std::string &second_particle,
              const double       loosest_cut,
              const double       strictest_cut,
              const double       cut_interval,
              const QHistogramSource &id_source,
              const QHistogramSource &misid_source);
                    // constructor overload with separate ID and misID source resolvers

    TGraphErrors *get_curve() const;

    ~QROCCurve();       // destructor
};

#endif
