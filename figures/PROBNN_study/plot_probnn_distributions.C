#include "TAxis.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TError.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TPad.h"
#include "TStyle.h"
#include "TSystem.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

struct ParticleSource {
    std::string directory;
    std::string label;
    Color_t colour;
    Style_t marker;
};

struct StudyConfig {
    std::string output_directory;
    std::string figure_tag;
    std::string dataset_label;
    std::vector<ParticleSource> sources;
};

StudyConfig study_config(const std::string &period) {
    if (period == "2025") {
        return {"pidcalib_sweights_uniform_25c4_magup_positive",
                "25c4_magup_positive", "25c4 MAGup",
                {{"P_Lc", "#it{p}", kGray + 1, 21},
                 {"K",    "#it{K}", kViolet - 2, 5},
                 {"Pi",   "#it{#pi}", kPink - 4, 24}}};
    }
    if (period == "2017") {
        return {"pidcalib_sweights_uniform_Turbo17_magup_positive",
                "Turbo17_magup_positive", "Turbo17 MAGup",
                {{"P_IncLc", "#it{p}", kGray + 1, 21},
                 {"K",       "#it{K}", kViolet - 2, 5},
                 {"Pi",      "#it{#pi}", kPink - 4, 24}}};
    }
    throw std::runtime_error("Period must be 2025 or 2017");
}

std::string source_path(const StudyConfig &study, const ParticleSource &source) {
    return study.output_directory + "/" + source.directory
         + "/plot_calib_distributions.root";
}

void require_matching_axis(const TAxis *reference, const TAxis *candidate,
                           const std::string &axis_name, const std::string &path) {
    if (reference->GetNbins() != candidate->GetNbins()) {
        throw std::runtime_error("Different " + axis_name + " bin count in " + path);
    }
    for (int bin = 1; bin <= reference->GetNbins() + 1; ++bin) {
        if (std::fabs(reference->GetBinLowEdge(bin) - candidate->GetBinLowEdge(bin)) > 1.e-9) {
            throw std::runtime_error("Different " + axis_name + " bin edge in " + path);
        }
    }
}

std::unique_ptr<TH1D> normalised_histogram(const TH1D *source, const std::string &name) {
    auto histogram = std::unique_ptr<TH1D>(
        static_cast<TH1D *>(source->Clone(name.c_str())));
    histogram->SetDirectory(nullptr);

    // PIDCalib2 stores the weighted calibration-sample totals directly in P
    // and ETA.  Normalise bin contents (not densities) to preserve the
    // convention of the existing figures.
    // Written as a positive test so that a NaN integral fails too; NaN <= 0. is
    // false, which would otherwise let an all-NaN histogram through silently.
    const double normalisation = histogram->Integral(1, histogram->GetNbinsX());
    if (!(normalisation > 0.)) {
        throw std::runtime_error("No usable in-range entries in " + name
                                 + " (integral is " + std::to_string(normalisation) + ")");
    }
    histogram->Scale(1. / normalisation);
    return histogram;
}

std::unique_ptr<TH1D> width_normalised_histogram(const TH1D *histogram,
                                                  const double reference_width,
                                                  const std::string &name) {
    auto density = std::unique_ptr<TH1D>(static_cast<TH1D *>(histogram->Clone(name.c_str())));
    density->SetDirectory(nullptr);
    for (int bin = 1; bin <= density->GetNbinsX(); ++bin) {
        const double scale = reference_width / density->GetBinWidth(bin);
        density->SetBinContent(bin, density->GetBinContent(bin) * scale);
        density->SetBinError(bin, density->GetBinError(bin) * scale);
    }
    return density;
}

std::unique_ptr<TGraphErrors> graph_from_histogram(const TH1D *histogram,
                                                    const ParticleSource &source) {
    auto graph = std::make_unique<TGraphErrors>(histogram->GetNbinsX());
    for (int bin = 1; bin <= histogram->GetNbinsX(); ++bin) {
        graph->SetPoint(bin - 1, histogram->GetBinCenter(bin), histogram->GetBinContent(bin));
        graph->SetPointError(bin - 1, 0.5 * histogram->GetBinWidth(bin), histogram->GetBinError(bin));
    }
    graph->SetLineWidth(3);
    graph->SetLineColor(source.colour);
    graph->SetMarkerStyle(source.marker);
    graph->SetMarkerColor(source.colour);
    graph->SetMarkerSize(1.2);
    graph->SetTitle("");
    return graph;
}

void draw_distribution(const StudyConfig &study, const bool project_momentum,
                       const bool normalise_by_width,
                       const std::vector<ParticleSource> &sources,
                       const std::vector<std::unique_ptr<TH1D>> &histograms) {
    const std::string variable = project_momentum ? "momentum" : "eta";
    const std::string figure_name = "probnn_distributions_" + study.figure_tag + "_"
                                  + variable + (normalise_by_width ? "_density" : "");
    const TAxis *axis = histograms.front()->GetXaxis();

    std::vector<std::unique_ptr<TGraphErrors>> graphs;
    double maximum = 0.;
    for (std::size_t index = 0; index < histograms.size(); ++index) {
        graphs.push_back(graph_from_histogram(histograms.at(index).get(), sources.at(index)));
        for (int bin = 1; bin <= histograms.at(index)->GetNbinsX(); ++bin) {
            maximum = std::max(maximum, histograms.at(index)->GetBinContent(bin)
                                        + histograms.at(index)->GetBinError(bin));
        }
    }

    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    TCanvas *canvas = new TCanvas(("canvas_" + figure_name).c_str(),
                                  ("canvas_" + figure_name).c_str(), 800, 600);
    canvas->cd();
    gPad->SetTopMargin(0.05);
    gPad->SetLeftMargin(0.14);
    gPad->SetBottomMargin(0.13);

    TGraphErrors *first_graph = graphs.front().get();
    first_graph->SetMinimum(0.);
    first_graph->SetMaximum(project_momentum ? 1.20 * maximum : 0.20);
    first_graph->Draw("APE");
    gPad->Update();

    const char *x_title = project_momentum ? "Momentum (MeV/#it{c})" : "Pseudorapidity";
    const char *y_title = normalise_by_width
        ? (project_momentum ? "Normalised candidates / (5 GeV/#it{c})"
                            : "Normalised candidates / 0.2")
        : "Normalised candidates";
    first_graph->GetXaxis()->SetTitle(x_title);
    first_graph->GetXaxis()->SetTitleSize(0.044);
    first_graph->GetXaxis()->SetLabelSize(0.044);
    first_graph->GetXaxis()->SetTitleOffset(1.0);
    // The uniform P binning starts at zero, whereas the established figures
    // start at the RICH threshold.  Display only that established range;
    // this intentionally truncates the 5--10 GeV threshold bin.
    const double display_minimum = project_momentum ? 9300. : 2.0;
    const double display_maximum = project_momentum ? 120000. : 5.0;
    first_graph->GetXaxis()->SetLimits(display_minimum, display_maximum);
    first_graph->GetXaxis()->SetRangeUser(display_minimum, display_maximum);
    first_graph->GetYaxis()->SetTitle(y_title);
    first_graph->GetYaxis()->SetTitleSize(0.044);
    first_graph->GetYaxis()->SetLabelSize(0.044);
    first_graph->GetYaxis()->SetTitleOffset(1.55);

    for (std::size_t index = 1; index < graphs.size(); ++index) {
        graphs.at(index)->Draw("PE SAME");
    }

    // Keep labels above the graph paint area; ROOT otherwise clips them for eta.
    TPad *overlay = new TPad(("overlay_" + figure_name).c_str(), "", 0., 0., 1., 1.);
    overlay->SetFillStyle(0);
    overlay->SetBorderMode(0);
    overlay->Draw();
    overlay->cd();

    TLatex latex;
    latex.SetNDC();
    const double annotation_x = project_momentum ? 0.30 : 0.20;
    latex.SetTextSize(0.05);
    latex.DrawLatex(annotation_x, 0.86, "LHCb #scale[0.8]{Work in Progress}");
    latex.SetTextSize(0.040);
    latex.DrawLatex(annotation_x, 0.80, study.dataset_label.c_str());
    latex.DrawLatex(annotation_x, 0.74, "#sqrt{#it{s}} = 13.6 TeV Data");
TLegend *legend = new TLegend(0.75, 0.69, 0.89, 0.88);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetTextSize(0.040);
    for (std::size_t index = 0; index < graphs.size(); ++index) {
        legend->AddEntry(graphs.at(index).get(), sources.at(index).label.c_str(), "PLE");
    }
    legend->Draw();

    canvas->cd();
    canvas->Modified();
    canvas->Update();
    canvas->SaveAs(("macro_" + figure_name + ".C").c_str());
    canvas->SaveAs(("pdf_figure_" + figure_name + ".pdf").c_str());
    canvas->SaveAs((figure_name + ".pdf").c_str());
}

} // namespace

void plot_probnn_distributions(const char *period = "2025") {
    const StudyConfig study = study_config(period);

    std::vector<std::unique_ptr<TFile>> files;
    std::vector<TH1D *> momentum_sources;
    std::vector<TH1D *> eta_sources;
    for (const ParticleSource &source : study.sources) {
        const std::string path = source_path(study, source);
        auto file = std::make_unique<TFile>(path.c_str(), "READ");
        if (file->IsZombie()) {
            throw std::runtime_error("Cannot open " + path);
        }
        TH1D *momentum = dynamic_cast<TH1D *>(file->Get("P"));
        TH1D *eta = dynamic_cast<TH1D *>(file->Get("ETA"));
        if (momentum == nullptr || eta == nullptr) {
            throw std::runtime_error("Missing PIDCalib2 sWeighted P or ETA histogram for "
                                     + source.directory + " in " + path);
        }
        if (!momentum_sources.empty()) {
            require_matching_axis(momentum_sources.front()->GetXaxis(), momentum->GetXaxis(), "P", path);
            require_matching_axis(eta_sources.front()->GetXaxis(), eta->GetXaxis(), "ETA", path);
        }
        momentum_sources.push_back(momentum);
        eta_sources.push_back(eta);
        files.push_back(std::move(file));
    }

    std::vector<std::unique_ptr<TH1D>> momentum_histograms;
    std::vector<std::unique_ptr<TH1D>> eta_histograms;
    std::vector<std::unique_ptr<TH1D>> momentum_density_histograms;
    std::vector<std::unique_ptr<TH1D>> eta_density_histograms;
    for (std::size_t index = 0; index < momentum_sources.size(); ++index) {
        momentum_histograms.push_back(normalised_histogram(
            momentum_sources.at(index), "momentum_" + study.sources.at(index).directory));
        eta_histograms.push_back(normalised_histogram(
            eta_sources.at(index), "eta_" + study.sources.at(index).directory));
        momentum_density_histograms.push_back(width_normalised_histogram(
            momentum_histograms.back().get(), 5000., "momentum_density_" + study.sources.at(index).directory));
        eta_density_histograms.push_back(width_normalised_histogram(
            eta_histograms.back().get(), 0.2, "eta_density_" + study.sources.at(index).directory));
    }

    draw_distribution(study, true, false, study.sources, momentum_histograms);
    draw_distribution(study, false, false, study.sources, eta_histograms);
    draw_distribution(study, true, true, study.sources, momentum_density_histograms);
    draw_distribution(study, false, true, study.sources, eta_density_histograms);
}
