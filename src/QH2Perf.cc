#include "QH2Perf.hh"

#include "TH2D.h"

void QH2Perf::_project(){ 
    // Project the total and passed histograms using the ProjectionX / ProjectionY function in TH2D
    _total_p    = dynamic_cast<TH1D*>(_total ->ProjectionX("total_p"   ));
    _total_eta  = dynamic_cast<TH1D*>(_total ->ProjectionY("total_eta" ));
    _passed_p   = dynamic_cast<TH1D*>(_passed->ProjectionX("passed_p"  ));
    _passed_eta = dynamic_cast<TH1D*>(_passed->ProjectionY("passed_eta"));

    // Detach the projected histograms from their current directories
    _total_p   ->SetDirectory(nullptr);
    _total_eta ->SetDirectory(nullptr);
    _passed_p  ->SetDirectory(nullptr);
    _passed_eta->SetDirectory(nullptr);
}

void QH2Perf::_calculate_eff(){
    // Calculate the efficiency histograms 
    TH1D *hist_eff_p   = dynamic_cast<TH1D*>(_passed_p  ->Clone("eff_p"  ));
    TH1D *hist_eff_eta = dynamic_cast<TH1D*>(_passed_eta->Clone("eff_eta"));
    hist_eff_p  ->Divide(_passed_p  , _total_p  , 1., 1., "B");
    hist_eff_eta->Divide(_passed_eta, _total_eta, 1., 1., "B");

    // Use a small function which transforms these TH1Ds to TGraphErrors to be stored 
    auto convert_to_graph = [](TH1D *hist) -> TGraphErrors *{
        int number_of_bins = hist->GetNbinsX(); 
        TGraphErrors *graph = new TGraphErrors(number_of_bins);
        for (int bin = 1; bin <= number_of_bins; bin++){
            double variable       = hist->GetBinCenter (bin);
            double efficiency     = hist->GetBinContent(bin);
            double variable_err   = hist->GetBinWidth  (bin) * .5;
            double efficiency_err = hist->GetBinError  (bin);
            graph->SetPoint     (bin - 1, variable    , efficiency    );
            graph->SetPointError(bin - 1, variable_err, efficiency_err);
        }
        return graph;
    };

    // Fill the efficiency graphs
    _eff_p   = convert_to_graph(hist_eff_p  );
    _eff_eta = convert_to_graph(hist_eff_eta);

    delete hist_eff_p;
    delete hist_eff_eta;
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
    // Create the 1-dimensional projected histograms and corresponding efficiencies
    _project();
    _calculate_eff();
}

TGraphErrors *QH2Perf::eff_p()   const{return _eff_p;}
TGraphErrors *QH2Perf::eff_eta() const{return _eff_eta;}

QH2Perf::~QH2Perf(){
    delete _total_p; 
    delete _total_eta; 
    delete _passed_p; 
    delete _passed_eta;
    delete _eff_p;
    delete _eff_eta;
}
