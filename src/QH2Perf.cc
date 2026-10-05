#include "QH2Perf.hh"

#include "TH2D.h"

void QH2Perf::_project(){ 
    // Project the total and passed histograms using the ProjectionX / ProjectionY function in TH2D
    // Honour any region restriction: the eta profile is built only from the
    // momentum bins inside the region and the p profile only from the eta bins
    // inside it. Without this the eta profile silently averages over whatever
    // momentum range the file happens to cover, so two samples binned from
    // different momenta are not comparable (QH2 has already resolved the region
    // to enclosed-bin windows, defaulting to the full axes).
    const int ix_lo = _has_region ? _ix_lo : 1;
    const int ix_hi = _has_region ? _ix_hi : _total->GetNbinsX();
    const int iy_lo = _has_region ? _iy_lo : 1;
    const int iy_hi = _has_region ? _iy_hi : _total->GetNbinsY();

    _total_p    = dynamic_cast<TH1D*>(_total ->ProjectionX("total_p"   , iy_lo, iy_hi));
    _total_eta  = dynamic_cast<TH1D*>(_total ->ProjectionY("total_eta" , ix_lo, ix_hi));
    _passed_p   = dynamic_cast<TH1D*>(_passed->ProjectionX("passed_p"  , iy_lo, iy_hi));
    _passed_eta = dynamic_cast<TH1D*>(_passed->ProjectionY("passed_eta", ix_lo, ix_hi));

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
            // The binomial error is 0 at full efficiency; ROOT's Divide("B")
            // only zeroes it when passed == total exactly, but with sWeights a
            // bin can have passed > total (eff > 1, negative-weight events that
            // fail the cut) where Divide returns a spurious abs() error. Mirror
            // the ROC guard (QROCCurve::_calculate_efficiency) and zero it.
            if (efficiency >= 1.) efficiency_err = 0.;
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
                 const std::string &directory,
                 const QRegion     *region)
                :QH2Perf(batch,
                         polarity,
                         first_particle,
                         second_particle,
                         identification_type,
                         cut_value,
                         QHistogramSource::legacy(directory),
                         region){
}

QH2Perf::QH2Perf(const std::string &batch,
                 const std::string &polarity,
                 const std::string &first_particle,
                 const std::string &second_particle,
                 const std::string &identification_type,
                 const double       cut_value,
                 const QHistogramSource &source,
                 const QRegion     *region)
                :QH2(batch,
                     polarity,
                     first_particle,
                     second_particle,
                     identification_type,
                     cut_value,
                     source,
                     region){
    // Create the 1-dimensional projected histograms and corresponding efficiencies
    _project();
    _calculate_eff();
}

QH2Perf::QH2Perf(const std::vector<std::string> &batches,
                 const std::vector<std::string> &polarities,
                 const std::string &first_particle,
                 const std::string &second_particle,
                 const std::string &identification_type,
                 const double       cut_value,
                 const std::string &directory,
                 const QRegion     *region)
                :QH2Perf(batches,
                         polarities,
                         first_particle,
                         second_particle,
                         identification_type,
                         cut_value,
                         QHistogramSource::legacy(directory),
                         region){
}

QH2Perf::QH2Perf(const std::vector<std::string> &batches,
                 const std::vector<std::string> &polarities,
                 const std::string &first_particle,
                 const std::string &second_particle,
                 const std::string &identification_type,
                 const double       cut_value,
                 const QHistogramSource &source,
                 const QRegion     *region)
                :QH2(batches[0],
                     polarities[0],
                     first_particle,
                     second_particle,
                     identification_type,
                     cut_value,
                     source,
                     region){
    // Check that the batch vector and polarity vector has no size mismatches
    if (batches.size() != polarities.size())
        throw std::runtime_error("Batch vector and polarity vector mismatch");
    // Add the remaining batches to the base QH2 histogram
    for (size_t vector_index = 1; vector_index < batches.size(); vector_index++){
        QH2 *temp_hist = new QH2(batches[vector_index],
                                 polarities[vector_index],
                                 first_particle,
                                 second_particle,
                                 identification_type,
                                 cut_value,
                                 source,
                                 region);
        add(*temp_hist);
        delete temp_hist;
    }
    // Project and calculate efficiencies from the combined histogram
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
