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

// One sweep of a cut grid, contributing points to a ROC curve. A curve may be
// built from several of these, letting scans that live on different grids merge
// into a single curve. The usual case is a plain ">" scan plus the "<" complement
// scan of the same ProbNN discriminator: the complement grid carries thresholds
// that are dense at the high-ID-efficiency end, where the plain atanh grid steps
// by 2e-3 and leaves the curve visibly sparse.
//
// Whether a scan's efficiencies need complementing (eff -> 1 - eff) is read off
// the source itself, via QHistogramSource::probnn_complement().
struct QROCScan{
    const QHistogramSource *id_source    = nullptr;
    const QHistogramSource *misid_source = nullptr;
    double loosest_cut   = 0.;
    double strictest_cut = 0.;
    double cut_interval  = 0.;
};

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

    // One ROC point, tagged with the cut threshold that produced it.
    struct _Point{
        double threshold;   // ordering key: the physical parameter along the curve
        double id_efficiency;
        double id_error;
        double misid_efficiency;
        double misid_error;
    };

    void _fill_scan(const std::string   &batch,
                    const std::string   &polarity,
                    const QROCScan      &scan,
                    const QRegion       *region,
                    const QReweight     *reweight,
                    std::vector<_Point> &points);
        // appends the points of a single scan

public:
    QROCCurve(const std::string &batch,
              const std::string &polarity,
              const std::string &first_particle,
              const std::string &second_particle,
              const std::vector<QROCScan> &scans,
              const QRegion     *region   = nullptr,
              const QReweight   *reweight = nullptr);
                    // constructor building one curve from several cut-grid scans
                    // (e.g. a ">" scan merged with its "<" complement scan).
                    // Points are sorted by ID efficiency at the end, so the curve
                    // draws in order whatever order the scans arrive in.

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
              const QHistogramSource &misid_source,
              const QRegion     *region   = nullptr,
              const QReweight   *reweight = nullptr);
                    // constructor overload with separate ID and misID source resolvers
                    // (optionally restricted to a phase-space region and/or
                    //  per-bin kinematically reweighted)

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
              const QHistogramSource &misid_source,
              const QRegion     *region = nullptr);
                    // constructor overload with separate ID and misID source resolvers
                    // (optionally restricted to a phase-space region)

    TGraphErrors *get_curve() const;

    ~QROCCurve();       // destructor
};

#endif
