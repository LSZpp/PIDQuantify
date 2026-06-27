#include "QROCCurve.hh"
#include "QH2.hh"

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
                    :_first_particle (first_particle),
                     _second_particle(second_particle),
                     _loosest_cut  (loosest_cut),
                     _strictest_cut(strictest_cut),
                     _cut_interval (cut_interval){
    // Create an empty TGraphErrors, prepare to fill in points
    _curve = new TGraphErrors();

    // Use the QH2 class to automatically create all the points on the curve
    unsigned short cut_count = 0;
    // Iterate by integer index so a non-binary-exact step (e.g. 0.05) does not
    // drift and both endpoints are hit deterministically. n_points matches the
    // job-side grid count exactly (e.g. ProbNN -15..0/0.05 -> 301 points).
    const int n_points = static_cast<int>(std::lround((strictest_cut - loosest_cut) / cut_interval));
    for (int point_index = 0; point_index <= n_points; ++point_index){
        const double cut = loosest_cut + point_index * cut_interval;
        QH2 *ID_point_hist = new QH2(batch,
                                     polarity,
                                     first_particle,
                                     second_particle,
                                     "ID",
                                     cut,
                                     id_source,
                                     region,
                                     reweight);
        std::pair<double, double> ID_efficiency = _calculate_efficiency(*ID_point_hist);
        delete ID_point_hist;

        QH2 *misID_point_hist = new QH2(batch,
                                        polarity,
                                        first_particle,
                                        second_particle,
                                        "misID",
                                        cut,
                                        misid_source,
                                        region,
                                        reweight);
        std::pair<double, double> misID_efficiency = _calculate_efficiency(*misID_point_hist);
        delete misID_point_hist;

        _curve->SetPoint     (cut_count, ID_efficiency.first , misID_efficiency.first );
        _curve->SetPointError(cut_count, ID_efficiency.second, misID_efficiency.second);

        cut_count++;        
    }
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
