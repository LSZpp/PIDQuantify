#include "QPerf.hh"

#include "TGraphErrors.h"
#include "TColor.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TMarker.h"
#include "TPad.h"

#include <stdexcept>
#include <cmath>
#include <sstream>
#include <iomanip>

TCanvas *QPerf::_create_figure(const std::string &canvas_name, 
                               const std::string &projection_direction){
    const std::string appended_canvas_name = "canvas_" + canvas_name;  
                                            // append "canvas_" from the left
                                            // otherwise the output macros would not work
    TCanvas *canvas = new TCanvas(appended_canvas_name.c_str(),
                                  appended_canvas_name.c_str(),
                                  800, 600); 
    
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
    gPad->SetTopMargin(0.05);

    // Provide some formatting to all histograms
    auto formatting = [&](TGraphErrors  *graph,
                          const Color_t &colour,
                          const Style_t &style){
        graph->SetLineWidth(3);
        graph->SetLineColor(colour);
        graph->SetMarkerStyle(style);
        graph->SetMarkerColor(colour);
        graph->SetMarkerSize(1.2);
        graph->SetTitle("");
        graph->GetXaxis()->SetTitle      (bin_variable_name.c_str());
        graph->GetXaxis()->SetTitleSize  ( .044   );
        graph->GetXaxis()->SetLabelSize  ( .044   );
        graph->GetXaxis()->SetTitleOffset(1.      );
        if (projection_direction == "p"  ) graph->GetXaxis()->SetRangeUser(0, 100.e3); 
        if (projection_direction == "eta") graph->GetXaxis()->SetRangeUser(1.5, 5); 
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

    // Draw the relavent TLatexes
    TLatex latex;
    latex.SetNDC();
    latex.SetTextSize(.044);
    auto assign_latex_particle = [](std::string particle) -> std::string{
        if      (particle == "P" ){return "#it{p}"  ;}
        else if (particle == "K" ){return "#it{K}"  ;}
        else if (particle == "Pi"){return "#it{#pi}";}
        return "null_result";
    };      // small function which transforms the particles into the correct format for TLatex

    // The text legends at the top
    auto cut_to_string = [](double cut_value) -> std::string{
        if (std::fabs(cut_value) - std::round(cut_value) < 1.e-9){
            return std::to_string(static_cast<int>(std::round(cut_value)));
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << cut_value;
        return oss.str();
    };       // small function which transforms the cut values to integer if integer
             // and truncates the cut value to 1dp if it is not an integer
    std::string latex_first_particle  = assign_latex_particle(_first_particle );
    std::string latex_second_particle = assign_latex_particle(_second_particle);
    std::string latex_string_ID    = latex_first_particle  + " #rightarrow " + latex_first_particle;
    std::string latex_string_misID = latex_second_particle + " #rightarrow " + latex_first_particle;
    latex.SetTextColor(kBlack);
    std::string latex_dataset_string = _batch + " MAG" + _polarity;
    std::string latex_beam_energy_string = "#sqrt{#it{s}} = 13.6 TeV Data";
    latex.DrawLatex(.15, .85, latex_dataset_string.c_str());
    latex.DrawLatex(.15, .79, latex_beam_energy_string.c_str());
    latex.DrawLatex(.35, .28, latex_string_misID.c_str());
    latex.SetTextColor(kRed);
    latex.DrawLatex(.35, .55, latex_string_ID   .c_str());

    std::string latex_cut_value_loose   = cut_to_string(_cut_value_loose );
    std::string latex_cut_value_strict  = cut_to_string(_cut_value_strict);
    std::string latex_cut_string_loose  =   "#DeltaLL( " 
                                                    + latex_first_particle
                                          + " - "   + latex_second_particle
                                          + " ) > " + latex_cut_value_loose;
    std::string latex_cut_string_strict =   "#DeltaLL( " 
                                                    + latex_first_particle
                                          + " - "   + latex_second_particle
                                          + " ) > " + latex_cut_value_strict;
    latex.SetTextColor(kBlack);
    latex.DrawLatex(.62, .85, latex_cut_string_loose .c_str());
    latex.DrawLatex(.62, .79, latex_cut_string_strict.c_str());

    // The marker legend
    TPad *legend_pad = new TPad("legend_pad", "legend_pad", 0., 0., 1., 1.);
        // ROOT should own this heap pointer, so do not delete it
    legend_pad->SetFillStyle(0);
    legend_pad->SetBorderMode(0);
    legend_pad->Draw();
    legend_pad->cd();
    auto draw_marker = [](
                          const Color_t &colour,
                          const Style_t &style,
                          double x_position,
                          double y_position){
        TMarker *marker = new TMarker();
        // ROOT should own this heap pointer, so do not delete it
        marker->SetMarkerStyle(style);
        marker->SetMarkerColor(colour);
        marker->SetMarkerSize(1.2);
        marker->SetX(x_position);
        marker->SetY(y_position);
        marker->Draw();
    };
    draw_marker(kRed,   24, .52, .865);
    draw_marker(kRed,   20, .52, .805);
    draw_marker(kBlack, 25, .58, .865);
    draw_marker(kBlack, 21, .58, .805);

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
            :_batch           (batch),
             _polarity        (polarity),
             _first_particle  (first_particle),
             _second_particle (second_particle),
             _directory       (directory),
             _cut_value_loose (cut_value_loose),
             _cut_value_strict(cut_value_strict){
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
    std::string p_name_C_macro   = "macro_" + name + "_p.C"    ; 
    std::string eta_name_C_macro = "macro_" + name + "_eta.C"  ; 
    std::string p_name_pdf       = "pdf_figure_" + name + "_p.pdf"  ; 
    std::string eta_name_pdf     = "pdf_figure_" + name + "_eta.pdf"; 
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
