#include "QROCCurve.hh"
#include "QH2.hh"
#include "QProperty.hh"

#include <algorithm>
#include <cmath>
#include <stdexcept>

std::pair<double, double> QROCCurve::_calculate_efficiency(const QH2 &hist){
    double total  = hist.sum_total();
    if (total <= 0.) return {0., 0.};
    double passed = hist.sum_passed();
    double e     = passed / total;
    double err_e = e >= 1. ? 0. : pow(e * (1 - e) / total ,.5);
    return {e, err_e};
}

QROCCurve::QROCCurve(const std::string &batch,
                     const std::string &polarity,
                     const std::string &first_particle,
                     const std::string &second_particle,
                     const double       loosest_cut,
                     const double       strictest_cut,
                     const double       cut_interval,
                     const std::string &directory)
                    :QROCCurve(batch,
                               polarity,
                               first_particle,
                               second_particle,
                               loosest_cut,
                               strictest_cut,
                               cut_interval,
                               QHistogramSource::legacy(directory),
                               QHistogramSource::legacy(directory)){
}

QROCCurve::QROCCurve(const std::string &batch,
                     const std::string &polarity,
                     const std::string &first_particle,
                     const std::string &second_particle,
                     const double       loosest_cut,
                     const double       strictest_cut,
                     const double       cut_interval,
                     const QHistogramSource &source)
                    :QROCCurve(batch,
                               polarity,
                               first_particle,
                               second_particle,
                               loosest_cut,
                               strictest_cut,
                               cut_interval,
                               source,
                               source){
}

void QROCCurve::_fill_scan(const std::string   &batch,
                           const std::string   &polarity,
                           const QROCScan      &scan,
                           const QRegion       *region,
                           const QReweight     *reweight,
                           std::vector<_Point> &points){
    if (!scan.id_source || !scan.misid_source)
        throw std::runtime_error("QROCScan is missing an ID or a misID source");
    if (scan.cut_interval == 0.)
        throw std::runtime_error("QROCScan has a zero cut interval");
    if (scan.id_source->probnn_complement() != scan.misid_source->probnn_complement())
        throw std::runtime_error("QROCScan mixes a complement source with a plain one; "
                                 "ID and misID must come from the same cut family");

    // A complement scan reads "X < (1 - tanh(u))" histograms. Because
    // eff(X > s) == 1 - eff(X < s), complementing both efficiencies turns them
    // into ordinary ">"-cut ROC points, at thresholds the plain grid never visits.
    const bool complement = scan.id_source->probnn_complement();

    // Iterate by integer index so a non-binary-exact step (e.g. 0.05) does not
    // drift and both endpoints are hit deterministically. n_points matches the
    // job-side grid count exactly (e.g. ProbNN -15..0/0.05 -> 301 points).
    const int n_points =
        static_cast<int>(std::lround((scan.strictest_cut - scan.loosest_cut) / scan.cut_interval));
    for (int point_index = 0; point_index <= n_points; ++point_index){
        const double cut = scan.loosest_cut + point_index * scan.cut_interval;
        QH2 *ID_point_hist = new QH2(batch,
                                     polarity,
                                     _first_particle,
                                     _second_particle,
                                     "ID",
                                     cut,
                                     *scan.id_source,
                                     region,
                                     reweight);
        std::pair<double, double> ID_efficiency = _calculate_efficiency(*ID_point_hist);
        delete ID_point_hist;

        QH2 *misID_point_hist = new QH2(batch,
                                        polarity,
                                        _first_particle,
                                        _second_particle,
                                        "misID",
                                        cut,
                                        *scan.misid_source,
                                        region,
                                        reweight);
        std::pair<double, double> misID_efficiency = _calculate_efficiency(*misID_point_hist);
        delete misID_point_hist;

        // The binomial error is symmetric under e -> 1 - e, so only the central
        // values move.
        if (complement){
            ID_efficiency.first    = 1. - ID_efficiency.first;
            misID_efficiency.first = 1. - misID_efficiency.first;
        }

        // Tag the point with the threshold it came from, so scans on different
        // grids can be merged into one properly ordered curve.
        const QProperty property(batch,
                                 polarity,
                                 _first_particle,
                                 _second_particle,
                                 "ID",
                                 cut,
                                 *scan.id_source);

        points.push_back(_Point{property.threshold(),
                                ID_efficiency.first,  ID_efficiency.second,
                                misID_efficiency.first, misID_efficiency.second});
    }
}

QROCCurve::QROCCurve(const std::string &batch,
                     const std::string &polarity,
                     const std::string &first_particle,
                     const std::string &second_particle,
                     const std::vector<QROCScan> &scans,
                     const QRegion     *region,
                     const QReweight   *reweight)
                    :_first_particle (first_particle),
                     _second_particle(second_particle),
                     _loosest_cut  (scans.empty() ? 0. : scans.front().loosest_cut),
                     _strictest_cut(scans.empty() ? 0. : scans.front().strictest_cut),
                     _cut_interval (scans.empty() ? 0. : scans.front().cut_interval){
    if (scans.empty()) throw std::runtime_error("QROCCurve needs at least one scan");

    // Create an empty TGraphErrors, prepare to fill in points
    _curve = new TGraphErrors();

    std::vector<_Point> points;
    for (const QROCScan &scan : scans){
        _fill_scan(batch, polarity, scan, region, reweight, points);
    }

    // Merged scans arrive interleaved: they sit on different grids, and a
    // complement scan runs in the opposite threshold direction. Order them by the
    // cut threshold, the physical parameter that runs along the curve from loose
    // to tight, so the "LP" draw option joins the points along the curve.
    //
    // Ordering by ID efficiency (TGraph::Sort) would NOT do: at the loose end the
    // curve is essentially vertical -- ID efficiency sits at 1 while the mis-ID
    // rate falls from 1 to ~0.5 -- so the ID efficiency carries no ordering
    // information there, and sWeight noise (which can push it a few 1e-4 past 1)
    // would shuffle the points.
    //
    // A single scan is already in threshold order by construction, and is left
    // exactly as it was, so existing single-scan figures are unaffected.
    if (scans.size() > 1){
        std::stable_sort(points.begin(), points.end(),
                         [](const _Point &a, const _Point &b){
                             return a.threshold < b.threshold;
                         });
    }

    for (size_t point_index = 0; point_index < points.size(); ++point_index){
        const _Point &point = points[point_index];
        _curve->SetPoint     (static_cast<int>(point_index),
                              point.id_efficiency, point.misid_efficiency);
        _curve->SetPointError(static_cast<int>(point_index),
                              point.id_error,      point.misid_error);
    }
}

QROCCurve::QROCCurve(const std::string &batch,
                     const std::string &polarity,
                     const std::string &first_particle,
                     const std::string &second_particle,
                     const double       loosest_cut,
                     const double       strictest_cut,
                     const double       cut_interval,
                     const QHistogramSource &id_source,
                     const QHistogramSource &misid_source,
                     const QRegion     *region,
                     const QReweight   *reweight)
                    :QROCCurve(batch,
                               polarity,
                               first_particle,
                               second_particle,
                               std::vector<QROCScan>{QROCScan{&id_source,
                                                              &misid_source,
                                                              loosest_cut,
                                                              strictest_cut,
                                                              cut_interval}},
                               region,
                               reweight){
}

QROCCurve::QROCCurve(const std::vector<std::string> &batches,
                     const std::vector<std::string> &polarities,
                     const std::string &first_particle,
                     const std::string &second_particle,
                     const double       loosest_cut,
                     const double       strictest_cut,
                     const double       cut_interval,
                     const std::string &directory)
                    :QROCCurve(batches,
                               polarities,
                               first_particle,
                               second_particle,
                               loosest_cut,
                               strictest_cut,
                               cut_interval,
                               QHistogramSource::legacy(directory),
                               QHistogramSource::legacy(directory)){
}

QROCCurve::QROCCurve(const std::vector<std::string> &batches,
                     const std::vector<std::string> &polarities,
                     const std::string &first_particle,
                     const std::string &second_particle,
                     const double       loosest_cut,
                     const double       strictest_cut,
                     const double       cut_interval,
                     const QHistogramSource &source)
                    :QROCCurve(batches,
                               polarities,
                               first_particle,
                               second_particle,
                               loosest_cut,
                               strictest_cut,
                               cut_interval,
                               source,
                               source){
}

QROCCurve::QROCCurve(const std::vector<std::string> &batches,
                     const std::vector<std::string> &polarities,
                     const std::string &first_particle,
                     const std::string &second_particle,
                     const double       loosest_cut,
                     const double       strictest_cut,
                     const double       cut_interval,
                     const QHistogramSource &id_source,
                     const QHistogramSource &misid_source,
                     const QRegion     *region)
                    :_first_particle (first_particle),
                     _second_particle(second_particle),
                     _loosest_cut  (loosest_cut),
                     _strictest_cut(strictest_cut),
                     _cut_interval (cut_interval){
    // Create an empty TGraphErrors, prepare to fill in points
    _curve = new TGraphErrors();

    // Check that the batch vector and polarity vector has no size mismatches
    if (batches.size() != polarities.size())
        throw std::runtime_error("Batch vector and polarity vector mismatch");

    // Use the QH2 class to automatically create all the points on the curve
    unsigned short cut_count = 0;
    // Iterate by integer index so a non-binary-exact step (e.g. 0.05) does not
    // drift and both endpoints are hit deterministically. n_points matches the
    // job-side grid count exactly (e.g. ProbNN -15..0/0.05 -> 301 points).
    const int n_points = static_cast<int>(std::lround((strictest_cut - loosest_cut) / cut_interval));
    for (int point_index = 0; point_index <= n_points; ++point_index){
        const double cut = loosest_cut + point_index * cut_interval;
        auto build_histogram = [&](QH2 &point_hist, const std::string &identification_type){
            for (size_t vector_index = 1; vector_index < batches.size(); vector_index++){
                QH2 *temp_hist = new QH2(batches[vector_index],
                                         polarities[vector_index],
                                         first_particle,
                                         second_particle,
                                         identification_type,
                                         cut,
                                         identification_type == "ID" ? id_source : misid_source,
                                         region);
                point_hist.add(*temp_hist);
                delete temp_hist;
            }
        };  // a function which builds the summed QH2 from the different batches and polarities
            // via repeatedly applying the add() function

        QH2 *ID_point_hist = new QH2(batches[0],
                                     polarities[0],
                                     first_particle,
                                     second_particle,
                                     "ID",
                                     cut,
                                     id_source,
                                     region);
        build_histogram(*ID_point_hist, "ID");
        std::pair<double, double> ID_efficiency = _calculate_efficiency(*ID_point_hist);
        delete ID_point_hist;

        QH2 *misID_point_hist = new QH2(batches[0],
                                        polarities[0],
                                        first_particle,
                                        second_particle,
                                        "misID",
                                        cut,
                                        misid_source,
                                        region);
        build_histogram(*misID_point_hist, "misID");
        std::pair<double, double> misID_efficiency = _calculate_efficiency(*misID_point_hist);
        delete misID_point_hist;

        _curve->SetPoint     (cut_count, ID_efficiency.first , misID_efficiency.first );
        _curve->SetPointError(cut_count, ID_efficiency.second, misID_efficiency.second);

        cut_count++;        
    }
}

TGraphErrors *QROCCurve::get_curve() const{return _curve;}

QROCCurve::~QROCCurve(){
    delete _curve;
}
