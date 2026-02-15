#include "QH2Perf.hh"

#include "TH2D.h"

#include <stdexcept>

void QH2Perf::_project(){
    // project the total and passed histograms using the ProjectionX / ProjectionY function in TH2D
    _total_p     = dynamic_cast<TH1D*>(_total ->ProjectionX("total_p"   ));
    _total_eta   = dynamic_cast<TH1D*>(_total ->ProjectionY("total_eta" ));
    _passed_p    = dynamic_cast<TH1D*>(_passed->ProjectionX("passed_p"  ));
    _passed_eta  = dynamic_cast<TH1D*>(_passed->ProjectionY("passed_eta"));
}

void QH2Perf::_calculate_eff(){
    // calculate the efficiency histograms 
    _eff_p   = dynamic_cast<TH1D*>(_passed_p  ->Clone("eff_p"  ));
    _eff_eta = dynamic_cast<TH1D*>(_passed_eta->Clone("eff_eta"));
    _eff_p  ->Divide(_total_p  );
    _eff_eta->Divide(_total_eta);
}

QH2Perf::QH2Perf(const std::string &batch,
                 const std::string &polarity,
                 const std::string &first_particle,
                 const std::string &second_particle,
                 const std::string &identification_type,
                 const double       cut_value,
                 const std::string &directory)
                :QH2(batch,
                     polarity,
                     first_particle,
                     second_particle,
                     identification_type,
                     cut_value,
                     directory){
    // create the 1-dimensional projected histograms and corresponding efficiencies
    _project();
    _calculate_eff();
}

TH1D *QH2Perf::eff_p()   const{return _eff_p;}
TH1D *QH2Perf::eff_eta() const{return _eff_eta;}
