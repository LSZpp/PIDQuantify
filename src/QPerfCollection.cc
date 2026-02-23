#include "QPerfCollection.hh"

#include "TPad.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TLatex.h"

#include <cmath>
#include <sstream>
#include <iomanip>

QPerfCollection::QPerfCollection(const std::string &first_particle,
                                 const std::string &second_particle,
                                 const double cut)
                                :_first_particle(first_particle),
                                 _second_particle(second_particle),
                                 _cut(cut){
}

void QPerfCollection::add_perf(const std::string &batch,
                               const std::string &polarity, 
                               const std::string &name,
                               const std::string &directory){
    QH2Perf *perf_figure = new QH2Perf(batch,
                                       polarity,
                                       _first_particle,
                                       _second_particle,
                                       "ID",
                                       _cut,
                                       directory);
    _perf_figures.insert({name, perf_figure});
}

void QPerfCollection::create_figures(const std::string &canvas_name,
                                     const double min_efficiency_range,
                                     const double max_efficiency_range,
                                     const std::unordered_map<std::string, Color_t> *colour_map,
                                     const std::unordered_map<std::string, Style_t> *style_map){
    // Declare canvases
    std::string canvas_name_p   = canvas_name + "_p"  ;
    std::string canvas_name_eta = canvas_name + "_eta";

    _canvas_p   = new TCanvas(canvas_name_p  .c_str(), canvas_name_p  .c_str(), 800, 600);
    _canvas_eta = new TCanvas(canvas_name_eta.c_str(), canvas_name_eta.c_str(), 800, 600);

    // Draw the performance figures on the canvases
    unsigned short curve_count = 0;
    std::map<std::string, QH2Perf*>::const_iterator perf_figures_iterator;
    Color_t starting_colour = kP8Blue;
    auto assign_latex_particle = [](std::string particle) -> std::string{
        if      (particle == "P" ){return "#it{p}"  ;}
        else if (particle == "K" ){return "#it{K}"  ;}
        else if (particle == "Pi"){return "#it{#pi}";}
        return "null_result";
    };      // small function which transforms the particles into the correct format for TLatex
    std::string latex_first_particle  = assign_latex_particle(_first_particle );
    std::string latex_second_particle = assign_latex_particle(_second_particle);
    std::string y_label = "Efficiency"; 
    TLegend *legend = new TLegend(.3, .1, .7, .45);
        // this heap pointer should be taken care of by ROOT automatically
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(.044);
    for (perf_figures_iterator  = _perf_figures.begin();
         perf_figures_iterator != _perf_figures.end(); 
         perf_figures_iterator++){
        TGraphErrors *perf_figure_p   = perf_figures_iterator->second->eff_p  ();
        TGraphErrors *perf_figure_eta = perf_figures_iterator->second->eff_eta();
        auto formatting = [&](TCanvas           *canvas,
                              TGraphErrors      *perf_figure,
                              const std::string &projection_direction){
            canvas->cd();
            gPad->SetTopMargin(.05);
            perf_figure->Draw(curve_count == 0 ? "AP" : "P SAME");
            perf_figure->SetLineWidth(2);
            Style_t style = ((style_map == nullptr) || 
                             (style_map->find(perf_figures_iterator->first) == style_map->end()))
                            ? 24
                            : style_map->at(perf_figures_iterator->first);    // defined style of marker
            perf_figure->SetMarkerStyle(style);
            perf_figure->SetTitle("");
            perf_figure->SetMarkerSize(1.2);
            Color_t colour = ((colour_map == nullptr) ||
                              (colour_map->find(perf_figures_iterator->first) == colour_map->end()))
                             ? starting_colour + curve_count
                             : colour_map->at(perf_figures_iterator->first);    // defined colour of marker
            perf_figure->SetMarkerColor(colour);
            perf_figure->SetLineColor  (colour);
            perf_figure->SetTitle("");
            if (projection_direction == "p"  ) perf_figure->GetXaxis()->SetTitle("Momentum (MeV/#it{c})");
            if (projection_direction == "eta") perf_figure->GetXaxis()->SetTitle("Pseudorapidity"       );
            perf_figure->GetXaxis()->SetTitleSize  ( .044   );
            perf_figure->GetXaxis()->SetLabelSize  ( .044   );
            perf_figure->GetXaxis()->SetTitleOffset(1.      );
            if (projection_direction == "p"  ) perf_figure->GetXaxis()->SetRangeUser(0, 100.e3);
            if (projection_direction == "eta") perf_figure->GetXaxis()->SetRangeUser(1.5, 5);
            perf_figure->GetYaxis()->SetTitle      (y_label.c_str());
            perf_figure->GetYaxis()->SetTitleSize  ( .044   );
            perf_figure->GetYaxis()->SetLabelSize  ( .044   );
            perf_figure->GetYaxis()->SetRangeUser  (min_efficiency_range,
                                                    max_efficiency_range);
            perf_figure->GetYaxis()->SetTitleOffset(1.      );
        };      // small function that provides some basic formatting
        legend->AddEntry(perf_figure_p, perf_figures_iterator->first.c_str(), "P");
        formatting(_canvas_p  , perf_figure_p  , "p"  );
        formatting(_canvas_eta, perf_figure_eta, "eta");
        curve_count++;
    }
    TLatex latex;
    latex.SetNDC();
    latex.SetTextSize(.044);
    auto cut_to_string = [](double cut_value) -> std::string{
        if (std::fabs(cut_value) - std::round(cut_value) < 1.e-9){
            return std::to_string(static_cast<int>(std::round(cut_value)));
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << cut_value;
        return oss.str();
    };       // small function which transforms the cut values to integer if integer
             // and truncates the cut value to 1dp if it is not an integer
    std::string latex_cut_value  = cut_to_string(_cut);
    std::string latex_cut_string =   "#DeltaLL( " 
                                             + latex_first_particle
                                   + " - "   + latex_second_particle
                                   + " ) > " + latex_cut_value;
    std::string latex_beam_energy_string = "#sqrt{#it{s}} = 13.6 TeV Data";
    _canvas_p->cd();
    latex.DrawLatex(.15, .88, latex_cut_string.c_str());
    latex.DrawLatex(.15, .82, latex_beam_energy_string.c_str());
    legend->Draw();
    _canvas_eta->cd();
    latex.DrawLatex(.15, .88, latex_cut_string.c_str());
    latex.DrawLatex(.15, .82, latex_beam_energy_string.c_str());
    legend->Draw();
    _canvas_p  ->Update();
    _canvas_eta->Update();
}

void QPerfCollection::export_canvases(){
    // Create names for the .C macros and .pdf files,
    // then subsequently save these using the SaveAs method
    std::string name_C_macro_p   = "macro_"      + std::string(_canvas_p  ->GetName()) + ".C"  ; 
    std::string name_C_macro_eta = "macro_"      + std::string(_canvas_eta->GetName()) + ".C"  ; 
    std::string name_pdf_p       = "pdf_figure_" + std::string(_canvas_p  ->GetName()) + ".pdf"; 
    std::string name_pdf_eta     = "pdf_figure_" + std::string(_canvas_eta->GetName()) + ".pdf"; 
    _canvas_p  ->SaveAs(name_C_macro_p  .c_str());
    _canvas_eta->SaveAs(name_C_macro_eta.c_str());
    _canvas_p  ->SaveAs(name_pdf_p      .c_str());
    _canvas_eta->SaveAs(name_pdf_eta    .c_str());
}

QPerfCollection::~QPerfCollection(){
    std::map<std::string, QH2Perf*>::const_iterator perf_figures_iterator;
    for (perf_figures_iterator  = _perf_figures.begin();
         perf_figures_iterator != _perf_figures.end(); 
         perf_figures_iterator++){
        delete perf_figures_iterator->second;
    }
    delete _canvas_p;
    delete _canvas_eta;
}
