#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TStyle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

struct Sample {
    const char *directory;
    const char *label;
    Color_t colour;
    Style_t marker;
    double offset;
};

const std::array<Sample, 3> samples = {{
    {"block4_partition2", "Block 4 partition 2", kGray + 1, 20, -0.22},
    {"block4_partition3", "Block 4 partition 3", kRed + 2, 21, 0.00},
    {"24b4",              "Block 4 combined",    kAzure + 3, 24, 0.22},
}};

struct Parameter {
    const char *key;
    const char *axis_title;
    const char *output_name;
};

const std::array<Parameter, 9> parameters = {{
    {"mean",          "Signal mean [MeV/#it{c}^{2}]", "mean"},
    {"gauss_sigma",   "Gaussian width [MeV/#it{c}^{2}]", "gauss_sigma"},
    {"sigma_l_scale", "Left width scale", "sigma_l_scale"},
    {"sigma_r_scale", "Right width scale", "sigma_r_scale"},
    {"alpha_l",       "Left tail #alpha", "alpha_l"},
    {"alpha_r",       "Right tail #alpha", "alpha_r"},
    {"n_l",           "Left tail #it{n}", "n_l"},
    {"n_r",           "Right tail #it{n}", "n_r"},
    {"gauss_frac",    "Gaussian fraction", "gauss_frac"},
}};

std::string read_file(const std::string &path) {
    std::ifstream input(path);
    if (!input) throw std::runtime_error("Cannot open " + path);
    return std::string((std::istreambuf_iterator<char>(input)),
                       std::istreambuf_iterator<char>());
}

double json_value(const std::string &text, const std::string &key) {
    const std::regex pattern("\\\"" + key + "\\\"\\s*:\\s*([-+0-9.eE]+)");
    std::smatch match;
    if (!std::regex_search(text, match, pattern))
        throw std::runtime_error("Missing '" + key + "' in fit JSON");
    return std::stod(match[1]);
}

int n_bins(const std::string &pt) {
    if (pt == "vh") return 4;
    if (pt == "h") return 10;
    if (pt == "m") return 10;
    return 6;
}

struct Bin {
    std::string pt;
    int index;
    std::string label;
};

std::vector<Bin> all_bins() {
    std::vector<Bin> result;
    for (const std::string pt : {"vh", "h", "m", "l"})
        for (int index = 0; index < n_bins(pt); ++index)
            result.push_back({pt, index, pt + std::to_string(index)});
    return result;
}

std::string json_path(const Sample &sample, const Bin &bin) {
    return "/data/lhcb/users/lins/u1_PID_L0/" + std::string(sample.directory)
        + "/y/" + bin.pt + "/l02ppi_" + bin.pt + "pt_bin"
        + std::to_string(bin.index) + ".json";
}

void draw_parameter(const Parameter &parameter, const std::vector<Bin> &bins) {
    const int nbins = static_cast<int>(bins.size());
    const std::string stem = "fit_parameters_24b4_" + std::string(parameter.output_name);
    TCanvas *canvas = new TCanvas(("canvas_" + stem).c_str(), "", 1500, 700);
    canvas->SetLeftMargin(0.10);
    canvas->SetRightMargin(0.035);
    canvas->SetBottomMargin(0.19);
    canvas->SetTopMargin(0.075);

    std::array<std::vector<double>, 3> values;
    std::array<std::vector<double>, 3> errors;
    double minimum = 0.;
    double maximum = 0.;
    bool first = true;
    for (size_t sample_index = 0; sample_index < samples.size(); ++sample_index) {
        values[sample_index].reserve(nbins);
        errors[sample_index].reserve(nbins);
        for (const Bin &bin : bins) {
            const std::string text = read_file(json_path(samples[sample_index], bin));
            const double value = json_value(text, parameter.key);
            const double error = json_value(text, std::string(parameter.key) + "_error");
            values[sample_index].push_back(value);
            errors[sample_index].push_back(error);
            if (first) {
                minimum = value - error;
                maximum = value + error;
                first = false;
            } else {
                minimum = std::min(minimum, value - error);
                maximum = std::max(maximum, value + error);
            }
        }
    }
    const double span = std::max(maximum - minimum, 1.e-6);
    minimum -= 0.10 * span;
    maximum += 0.18 * span;

    TH1D *frame = new TH1D(("frame_" + stem).c_str(), "", nbins, -0.5, nbins - 0.5);
    frame->SetMinimum(minimum);
    frame->SetMaximum(maximum);
    frame->GetYaxis()->SetTitle(parameter.axis_title);
    frame->GetXaxis()->SetTitle("Fit bin");
    frame->GetYaxis()->SetTitleSize(0.050);
    frame->GetYaxis()->SetLabelSize(0.043);
    frame->GetYaxis()->SetTitleOffset(0.90);
    frame->GetXaxis()->SetTitleSize(0.047);
    frame->GetXaxis()->SetTitleOffset(1.55);
    frame->GetXaxis()->SetLabelSize(0.032);
    for (int index = 0; index < nbins; ++index)
        frame->GetXaxis()->SetBinLabel(index + 1, bins[index].label.c_str());
    frame->Draw();

    for (int boundary = 1; boundary < nbins; ++boundary) {
        TLine *line = new TLine(boundary - 0.5, minimum, boundary - 0.5, maximum);
        line->SetLineColor(kGray + 1);
        line->SetLineStyle(3);
        line->Draw();
    }

    std::array<TGraphErrors *, 3> graphs;
    for (size_t sample_index = 0; sample_index < samples.size(); ++sample_index) {
        std::vector<double> x(nbins), ex(nbins, 0.);
        for (int index = 0; index < nbins; ++index) x[index] = index + samples[sample_index].offset;
        graphs[sample_index] = new TGraphErrors(nbins, x.data(), values[sample_index].data(),
                                                ex.data(), errors[sample_index].data());
        graphs[sample_index]->SetMarkerColor(samples[sample_index].colour);
        graphs[sample_index]->SetLineColor(samples[sample_index].colour);
        graphs[sample_index]->SetMarkerStyle(samples[sample_index].marker);
        graphs[sample_index]->SetMarkerSize(0.85);
        graphs[sample_index]->SetLineWidth(1);
        graphs[sample_index]->Draw("PZ SAME");
    }

    TLegend *legend = new TLegend(0.70, 0.76, 0.96, 0.92);
    legend->SetBorderSize(0);
    legend->SetFillStyle(1001);
    legend->SetFillColor(kWhite);
    legend->SetTextSize(0.034);
    for (size_t sample_index = 0; sample_index < samples.size(); ++sample_index)
        legend->AddEntry(graphs[sample_index], samples[sample_index].label, "P");
    legend->Draw();

    canvas->SaveAs((stem + ".pdf").c_str());
    canvas->SaveAs((stem + ".png").c_str());
    canvas->SaveAs((stem + ".C").c_str());
}

}  // namespace

void plot_24b4_fit_parameters() {
    gStyle->SetOptStat(0);
    const std::vector<Bin> bins = all_bins();
    for (const Parameter &parameter : parameters) draw_parameter(parameter, bins);
}
