#include "QPerf.hh"

#include "TGraphErrors.h"
#include "TColor.h"
#include "TStyle.h"

#include <stdexcept>

TCanvas *QPerf::_create_figure(const std::string &canvas_name, 
                               const std::string &projection_direction){
    TCanvas *canvas = new TCanvas(canvas_name.c_str(), canvas_name.c_str(), 800, 600); 
    
    // Obtain the getter function in QH2Perf for the particular projected 1d histogram
    TGraphErrors *(QH2Perf::*eff)() const = nullptr;
    std::string bin_variable_name; 
    if (projection_direction == "p"){
        eff = &QH2Perf::eff_p;
        bin_variable_name = "Momentum (MeV/#it{c})";
    } else if (projection_direction == "eta"){
        eff = &QH2Perf::eff_eta;
        bin_variable_name = "Pseudorapidity";
    } else throw std::runtime_error("Projection direction not found");

    TGraphErrors *hist_loose_ID     = (_perf_hist_loose_ID    ->*eff)();
    TGraphErrors *hist_strict_ID    = (_perf_hist_strict_ID   ->*eff)();
    TGraphErrors *hist_loose_misID  = (_perf_hist_loose_misID ->*eff)();
    TGraphErrors *hist_strict_misID = (_perf_hist_strict_misID->*eff)();

    canvas->cd(); 

    // Provide some formatting to all histograms
    auto formatting = [&](TGraphErrors  *graph,
                          const Color_t &colour,
                          const Style_t &style){
        graph->SetLineWidth(2);
        graph->SetLineColor(colour);
        graph->SetMarkerStyle(style);
        graph->SetMarkerSize(.6);
        graph->GetXaxis()->SetTitle      (bin_variable_name.c_str());
        graph->GetXaxis()->SetTitleSize  ( .044   );
        graph->GetXaxis()->SetLabelSize  ( .044   );
        graph->GetXaxis()->SetTitleOffset(1.      );
        graph->GetYaxis()->SetTitle      ("Efficiency");
        graph->GetYaxis()->SetTitleSize  ( .044   );
        graph->GetYaxis()->SetLabelSize  ( .044   );
        graph->GetYaxis()->SetRangeUser  (0, 1.4  ); 
        graph->GetYaxis()->SetTitleOffset(1.      );
    };

    formatting(hist_loose_ID,     kRed,   24);
    formatting(hist_strict_ID,    kRed,   20);
    formatting(hist_loose_misID,  kBlack, 25);
    formatting(hist_strict_misID, kBlack, 21);
    hist_loose_ID    ->Draw("APE");
    hist_strict_ID   ->Draw("PE SAME");
    hist_loose_misID ->Draw("PE SAME");
    hist_strict_misID->Draw("PE SAME");

    // Ownership of the pointer on heap is transferred
    return canvas; 
}

QPerf::QPerf(const std::string &batch,
             const std::string &polarity,
             const std::string &first_particle,
             const std::string &second_particle,
             const std::string &directory,
             const double       cut_value_loose,
             const double       cut_value_strict)
            :_batch          (batch),
             _polarity       (polarity),
             _first_particle (first_particle),
             _second_particle(second_particle),
             _directory      (directory){
    // Create the four histograms to be placed onto the figure
    _perf_hist_loose_ID = new QH2Perf(batch,
                                      polarity,
                                      first_particle,
                                      second_particle,
                                      "ID",
                                      cut_value_loose,
                                      directory);

    _perf_hist_strict_ID = new QH2Perf(batch,
                                       polarity,
                                       first_particle,
                                       second_particle,
                                       "ID",
                                       cut_value_strict,
                                       directory);

    _perf_hist_loose_misID = new QH2Perf(batch,
                                         polarity,
                                         first_particle,
                                         second_particle,
                                         "misID",
                                         cut_value_loose,
                                         directory);

    _perf_hist_strict_misID = new QH2Perf(batch,
                                          polarity,
                                          first_particle,
                                          second_particle,
                                          "misID",
                                          cut_value_strict,
                                          directory);

    // Draw the histograms into the two canvases
    std::string canvas_name =   batch 
                              + "_" + polarity
                              + "_" + first_particle
                              + "_" + second_particle + "_";
    _canvas_p   = _create_figure(canvas_name + "p"  , "p"  );
    _canvas_eta = _create_figure(canvas_name + "eta", "eta");
}

void QPerf::export_canvases(const std::string &name){
    // Create names for the .C macros and .pdf files,
    // then subsequently save these using the SaveAs method
    std::string p_name_C_macro   = name + "_p.C"    ; 
    std::string eta_name_C_macro = name + "_eta.C"  ; 
    std::string p_name_pdf       = name + "_p.pdf"  ; 
    std::string eta_name_pdf     = name + "_eta.pdf"; 
    _canvas_p  ->SaveAs(p_name_C_macro  .c_str());
    _canvas_eta->SaveAs(eta_name_C_macro.c_str());
    _canvas_p  ->SaveAs(p_name_pdf      .c_str());
    _canvas_eta->SaveAs(eta_name_pdf    .c_str());
}

QPerf::~QPerf(){
    delete _perf_hist_loose_ID    ;
    delete _perf_hist_strict_ID   ;
    delete _perf_hist_loose_misID ;
    delete _perf_hist_strict_misID;
    delete _canvas_p  ;
    delete _canvas_eta;
}
