#include "QROCCurve.hh"
#include "QH2.hh"

#include <cmath>

QROCCurve::QROCCurve(const std::string &batch,
                     const std::string &polarity,
                     const std::string &first_particle,
                     const std::string &second_particle,
                     const double       loosest_cut,
                     const double       strictest_cut,
                     const double       cut_interval,
                     const std::string &directory)
                    :_loosest_cut  (loosest_cut),
                     _strictest_cut(strictest_cut),
                     _cut_interval (cut_interval){
    // Create an empty TGraphErrors, prepare to fill in points 
    _curve = new TGraphErrors();

    // Use the QH2 class to automatically create all the points on the curve
    unsigned short cut_count = 0;
    for (double cut = loosest_cut; cut <= strictest_cut; cut += cut_interval){
        auto efficiency = [](QH2 *hist) -> std::pair<double, double>{
            double total  = hist->sum_total();
            if (total <= 0.) return {0., 0.};
            double passed = hist->sum_passed();
            double e     = passed / total;
            double err_e = e >= 1. ? 0. : pow(e * (1 - e) / total ,.5);
            return {e, err_e};
        };

        QH2 *ID_point_hist = new QH2(batch,
                                     polarity, 
                                     first_particle, 
                                     second_particle,
                                     "ID",
                                     cut,
                                     directory);
        std::pair<double, double> ID_efficiency = efficiency(ID_point_hist);
        delete ID_point_hist;

        QH2 *misID_point_hist = new QH2(batch,
                                        polarity, 
                                        first_particle, 
                                        second_particle,
                                        "misID",
                                        cut,
                                        directory);
        std::pair<double, double> misID_efficiency = efficiency(misID_point_hist);
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
