#ifndef QH2_HH
#define QH2_HH


// The QH2 class 
// LSZ 14 Feb 26

// A class storing a particular efficiency histogram binned in momentum and pseudorapidity and its settings

#include "QProperty.hh"
#include "QHistogramSource.hh"

#include "TH2D.h"
#include "TAxis.h"

#include <string>
#include <map>
#include <utility>

class TH3D;

// A phase-space region restriction: axis name ("P", "ETA", "nLongTracks") ->
// (low, high) physical boundaries. Only bins fully enclosed by [low, high] are
// kept (a bin counts only if its whole [lowEdge, upEdge] lies within the range).
using QRegion = std::map<std::string, std::pair<double, double>>;

// Per-bin kinematic reweighting for a 3D source: {source_total, target_total}.
// Each 3D bin of this histogram is multiplied by weight = target_total /
// source_total before marginalisation, so the summed efficiency adopts the
// target's kinematic profile. (For L0->Lc: first = L0 total, second = Lc total.)
using QReweight = std::pair<TH3D*, TH3D*>;

class QH2{
protected:
    TH2D        *_total    = nullptr; // histogram for all particles used for calibration
    TH2D        *_passed   = nullptr; // histogram for particles passing the cut
    QProperty   *_property = nullptr; // the property of the histogram
    std::string  _path;               // the full path to the histogram including the file name

    // Optional region restriction applied to sum_total()/sum_passed(). Resolved
    // to enclosed bin-index windows in the (P=x, ETA=y) plane; the nLongTracks
    // (z) restriction for 3D inputs is applied at marginalisation time.
    bool _has_region = false;
    int  _ix_lo = 0, _ix_hi = -1;     // P    (x) enclosed bin range (1-based, inclusive)
    int  _iy_lo = 0, _iy_hi = -1;     // ETA  (y) enclosed bin range

    // First/last bins fully enclosed by [lo, hi] on the given axis. Returns
    // {1, 0} (an empty range) if no bin is fully enclosed.
    static std::pair<int, int> _enclosed_bins(const TAxis *axis, double lo, double hi);

public:
    QH2(const std::string &batch,
        const std::string &polarity,
        const std::string &first_particle,
        const std::string &second_particle,
        const std::string &identification_type,
        const double       cut_value,
        const std::string &directory,
        const QRegion     *region   = nullptr,
        const QReweight   *reweight = nullptr);
                     // constructor

    QH2(const std::string &batch,
        const std::string &polarity,
        const std::string &first_particle,
        const std::string &second_particle,
        const std::string &identification_type,
        const double       cut_value,
        const QHistogramSource &source,
        const QRegion     *region   = nullptr,
        const QReweight   *reweight = nullptr);
                     // constructor overload with a histogram source resolver
                     // (region: enclosed-bin restriction; reweight: per-bin
                     //  target/source kinematic reweighting, 3D sources only)

    double sum_total () const;
    double sum_passed() const;   // Integral() of the total and passed histograms across all phase space

    TH2D *get_total()  const;    // getter for the total histogram
    TH2D *get_passed() const;    // getter for the passed histogram

    void add(const QH2 &added_hist);  // addition of a second histogram

    virtual ~QH2();          // destructor
};

#endif
