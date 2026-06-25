#include "QROCCollection.hh"

#include "TPad.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TColor.h"
#include "TAxis.h"
#include "TLatex.h"

#include <stdexcept>
#include <unordered_map>

QROCCollection::QROCCollection(const std::string &first_particle,
                               const std::string &second_particle,
                               const double       loosest_cut,
                               const double       strictest_cut,
                               const double       cut_interval)
                              :_first_particle (first_particle),
                               _second_particle(second_particle),
                               _loosest_cut    (loosest_cut),
                               _strictest_cut  (strictest_cut),
                               _cut_interval   (cut_interval),
                               _id_source      (),
                               _misid_source   (),
                               _has_default_source(false){
}

QROCCollection::QROCCollection(const std::string &first_particle,
                               const std::string &second_particle,
                               const double       loosest_cut,
                               const double       strictest_cut,
                               const double       cut_interval,
                               const std::string &directory)
                              :QROCCollection(first_particle,
                                              second_particle,
                                              loosest_cut,
                                              strictest_cut,
                                              cut_interval,
                                              QHistogramSource::legacy(directory)){
}

QROCCollection::QROCCollection(const std::string &first_particle,
                               const std::string &second_particle,
                               const double       loosest_cut,
                               const double       strictest_cut,
                               const double       cut_interval,
                               const QHistogramSource &source)
                              :QROCCollection(first_particle,
                                              second_particle,
                                              loosest_cut,
                                              strictest_cut,
                                              cut_interval,
                                              source,
                                              source){
}

QROCCollection::QROCCollection(const std::string &first_particle,
                               const std::string &second_particle,
                               const double       loosest_cut,
                               const double       strictest_cut,
                               const double       cut_interval,
                               const QHistogramSource &id_source,
                               const QHistogramSource &misid_source)
                              :_first_particle (first_particle),
                               _second_particle(second_particle),
                               _loosest_cut    (loosest_cut),
                               _strictest_cut  (strictest_cut),
                               _cut_interval   (cut_interval),
                               _id_source      (id_source),
                               _misid_source   (misid_source),
                               _has_default_source(true){
}

void QROCCollection::add_curve(const std::string &batch, 
                               const std::string &polarity, 
                               const std::string &name){
    if (!_has_default_source){
        throw std::runtime_error("QROCCollection has no default source; use an add_curve overload with source arguments");
    }
    add_curve(batch,
              polarity,
              name,
              _id_source,
              _misid_source);
}

void QROCCollection::add_curve(const std::string &batch,
                               const std::string &polarity,
                               const std::string &name,
                               const QHistogramSource &source){
    add_curve(batch,
              polarity,
              name,
              source,
              source);
}

void QROCCollection::add_curve(const std::string &batch,
                               const std::string &polarity,
                               const std::string &name,
                               const QHistogramSource &id_source,
                               const QHistogramSource &misid_source){
    QROCCurve *curve = new QROCCurve(batch,
                                     polarity,
                                     _first_particle,
                                     _second_particle,
                                     _loosest_cut,
                                     _strictest_cut,
                                     _cut_interval,
                                     id_source,
                                     misid_source);
    _curves.insert({name, curve});
}

void QROCCollection::add_curve(const std::vector<std::string> &batches,
                               const std::vector<std::string> &polarities, 
                               const std::string &name){
    if (!_has_default_source){
        throw std::runtime_error("QROCCollection has no default source; use an add_curve overload with source arguments");
    }
    add_curve(batches,
              polarities,
              name,
              _id_source,
              _misid_source);
}

void QROCCollection::add_curve(const std::vector<std::string> &batches,
                               const std::vector<std::string> &polarities,
                               const std::string &name,
                               const QHistogramSource &source){
    add_curve(batches,
              polarities,
              name,
              source,
              source);
}

void QROCCollection::add_curve(const std::vector<std::string> &batches,
                               const std::vector<std::string> &polarities,
                               const std::string &name,
                               const QHistogramSource &id_source,
                               const QHistogramSource &misid_source){
    QROCCurve *curve = new QROCCurve(batches,
                                     polarities,
                                     _first_particle,
                                     _second_particle,
                                     _loosest_cut,
                                     _strictest_cut,
                                     _cut_interval,
                                     id_source,
                                     misid_source);
    _curves.insert({name, curve});
}

void QROCCollection::create_figure(const std::string &canvas_name,
                                   const std::unordered_map<std::string, Color_t> *colour_map){
    // Declare a canvas
    _canvas = new TCanvas(canvas_name.c_str(), canvas_name.c_str(), 800, 600);
    _canvas->cd();
    gPad->SetTopMargin(.05);
    
    // Draw the curves
    unsigned short curve_count = 0;
    std::map<std::string, QROCCurve*>::const_iterator curves_iterator;
    Color_t starting_colour = kP8Blue;
    auto assign_latex_particle = [](std::string particle) -> std::string{
        if      (particle == "P" ){return "#it{p}"  ;}
        else if (particle == "K" ){return "#it{K}"  ;}
        else if (particle == "Pi"){return "#it{#pi}";}
        return "null_result";
    };      // small function which transforms the particles into the correct format for TLatex
    std::string latex_first_particle  = assign_latex_particle(_first_particle );
    std::string latex_second_particle = assign_latex_particle(_second_particle);
    std::string x_label 
        = "Efficiency ( " + latex_first_particle  + " #rightarrow " + latex_first_particle + " )"; 
    std::string y_label 
        = "Efficiency ( " + latex_second_particle + " #rightarrow " + latex_first_particle + " )"; 
    TLegend *legend = new TLegend(.15, .5, .5, .8);
        // this heap pointer should be taken care of by ROOT automatically
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(.044);
    for (curves_iterator  = _curves.begin();
         curves_iterator != _curves.end(); 
         curves_iterator++){
        TGraphErrors *curve = curves_iterator->second->get_curve();
        curve->Draw(curve_count == 0 ? "ALP E" : "LP E SAME");
        Color_t colour = ((colour_map == nullptr) ||
                          (colour_map->find(curves_iterator->first) == colour_map->end()))
                         ? starting_colour + curve_count
                         : colour_map->at(curves_iterator->first);
        curve->SetMarkerStyle(21);
        curve->SetMarkerSize(.6);
        curve->SetMarkerColor(colour);
        curve->SetLineColor(colour);
        curve->SetTitle("");
        curve->GetXaxis()->SetTitle      (x_label.c_str());
        curve->GetXaxis()->SetTitleSize  ( .044   );
        curve->GetXaxis()->SetLabelSize  ( .044   );
        curve->GetXaxis()->SetTitleOffset(1.      );
        curve->GetXaxis()->SetRangeUser  (.7, 1.005);
        curve->GetYaxis()->SetTitle      (y_label.c_str());
        curve->GetYaxis()->SetTitleSize  ( .044   );
        curve->GetYaxis()->SetLabelSize  ( .044   );
        curve->GetYaxis()->SetRangeUser  (1.e-3,1.); 
        gPad ->SetLogy();
        curve->GetYaxis()->SetTitleOffset(1.      );
        legend->AddEntry(curve, curves_iterator->first.c_str(), "LP");
        curve_count++;
    }
    legend->Draw();
    TLatex latex;
    latex.SetNDC();
    latex.SetTextSize(.044);
    std::string latex_beam_energy_string = "#sqrt{#it{s}} = 13.6 TeV Data";
    latex.DrawLatex(.15, .85, latex_beam_energy_string.c_str());
    _canvas->Update();
};

void QROCCollection::export_canvas(){
    // Create names for the .C macros and .pdf files,
    // then subsequently save these using the SaveAs method
    std::string name_C_macro = "macro_"      + std::string(_canvas->GetName()) + ".C"  ; 
    std::string name_pdf     = "pdf_figure_" + std::string(_canvas->GetName()) + ".pdf"; 
    _canvas->SaveAs(name_C_macro.c_str());
    _canvas->SaveAs(name_pdf    .c_str());
}

QROCCollection::~QROCCollection(){
    std::map<std::string, QROCCurve*>::const_iterator curves_iterator;
    for (curves_iterator  = _curves.begin();
         curves_iterator != _curves.end(); 
         curves_iterator++){
        delete curves_iterator->second;
    }
    delete _canvas;
}
