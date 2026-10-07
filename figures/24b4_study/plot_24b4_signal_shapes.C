#include "TCanvas.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TStyle.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

namespace {

struct Sample {
    const char *directory;
    const char *label;
    Color_t colour;
};

const std::array<Sample, 3> samples = {{
    {"block4_partition2", "Block 4 partition 2", kGray + 1},
    {"block4_partition3", "Block 4 partition 3", kRed + 2},
    {"24b4",              "Block 4 combined",    kAzure + 3},
}};

double json_value(const std::string &path, const std::string &key) {
    std::ifstream input(path);
    const std::string text((std::istreambuf_iterator<char>(input)),
                           std::istreambuf_iterator<char>());
    const std::regex pattern("\\\"" + key + "\\\"\\s*:\\s*([-+0-9.eE]+)");
    std::smatch match;
    std::regex_search(text, match, pattern);
    return std::stod(match[1]);
}

double dscb(const double mass, const double mean,
            const double sigma_left, const double sigma_right,
            const double alpha_left, const double alpha_right,
            const double n_left, const double n_right) {
    const double t = (mass > mean) ? (mass - mean) / sigma_right
                                   : (mass - mean) / sigma_left;
    if (t <= -alpha_left) {
        const double a = std::pow(n_left / alpha_left, n_left)
                       * std::exp(-0.5 * alpha_left * alpha_left);
        const double b = n_left / alpha_left - alpha_left;
        return a / std::pow(b - t, n_left);
    }
    if (t >= alpha_right) {
        const double a = std::pow(n_right / alpha_right, n_right)
                       * std::exp(-0.5 * alpha_right * alpha_right);
        const double b = n_right / alpha_right - alpha_right;
        return a / std::pow(b + t, n_right);
    }
    return std::exp(-0.5 * t * t);
}

std::vector<double> signal_shape(const std::string &path,
                                 const std::vector<double> &mass) {
    const double mean = json_value(path, "mean");
    const double gauss_sigma = json_value(path, "gauss_sigma");
    const double sigma_left = gauss_sigma * json_value(path, "sigma_l_scale");
    const double sigma_right = gauss_sigma * json_value(path, "sigma_r_scale");
    const double alpha_left = json_value(path, "alpha_l");
    const double alpha_right = json_value(path, "alpha_r");
    const double n_left = json_value(path, "n_l");
    const double n_right = json_value(path, "n_r");
    const double gauss_fraction = json_value(path, "gauss_frac");

    std::vector<double> cb(mass.size()), gaussian(mass.size()), signal(mass.size());
    for (size_t index = 0; index < mass.size(); ++index) {
        cb[index] = dscb(mass[index], mean, sigma_left, sigma_right,
                         alpha_left, alpha_right, n_left, n_right);
        gaussian[index] = std::exp(-0.5 * std::pow((mass[index] - mean) / gauss_sigma, 2));
    }
    const double cb_norm = std::accumulate(cb.begin(), cb.end(), 0.);
    const double gaussian_norm = std::accumulate(gaussian.begin(), gaussian.end(), 0.);
    for (size_t index = 0; index < mass.size(); ++index)
        signal[index] = (1. - gauss_fraction) * cb[index] / cb_norm
                      + gauss_fraction * gaussian[index] / gaussian_norm;
    return signal;
}

int n_bins(const std::string &pt) {
    if (pt == "vh") return 4;
    if (pt == "h") return 10;
    if (pt == "m") return 10;
    return 6;
}

void draw_pt(const std::string &pt) {
    const int bins = n_bins(pt);
    const int columns = (bins <= 6) ? 3 : 5;
    const int rows = (bins + columns - 1) / columns;
    TCanvas *canvas = new TCanvas(("canvas_mass_shapes_" + pt).c_str(), "",
                                  330 * columns, 280 * rows);
    canvas->Divide(columns, rows, 0.001, 0.001);

    constexpr int points = 800;
    std::vector<double> mass(points);
    for (int index = 0; index < points; ++index)
        mass[index] = 1097.5 + index * (1135. - 1097.5) / (points - 1.);

    for (int bin = 0; bin < bins; ++bin) {
        canvas->cd(bin + 1);
        gPad->SetTopMargin(0.06);
        gPad->SetGridx(2);
        gPad->SetGridy(2);

        std::array<std::vector<double>, 3> shapes;
        double maximum = 0.;
        for (size_t index = 0; index < samples.size(); ++index) {
            const std::string path = "/data/lhcb/users/lins/u1_PID_L0/"
                + std::string(samples[index].directory) + "/y/" + pt
                + "/l02ppi_" + pt + "pt_bin" + std::to_string(bin) + ".json";
            shapes[index] = signal_shape(path, mass);
            maximum = std::max(maximum, *std::max_element(shapes[index].begin(), shapes[index].end()));
        }

        TH1D *frame = new TH1D(("frame_" + pt + "_" + std::to_string(bin)).c_str(), "",
                               100, 1097.5, 1135.);
        frame->SetMinimum(0.);
        frame->SetMaximum(1.22 * maximum);
        frame->GetXaxis()->SetTitle("#it{m}(#it{p}#pi) [MeV/#it{c}^{2}]");
        frame->GetYaxis()->SetTitle("Normalised signal shape");
        frame->GetXaxis()->SetTitleSize(0.055);
        frame->GetXaxis()->SetLabelSize(0.050);
        frame->GetYaxis()->SetTitleSize(0.055);
        frame->GetYaxis()->SetLabelSize(0.050);
        frame->GetYaxis()->SetTitleOffset(1.15);
        frame->Draw();

        std::array<TGraph *, 3> graphs;
        for (size_t index = 0; index < samples.size(); ++index) {
            graphs[index] = new TGraph(points, mass.data(), shapes[index].data());
            graphs[index]->SetLineColor(samples[index].colour);
            graphs[index]->SetLineWidth(3);
            graphs[index]->Draw("L SAME");
        }

        TLatex label;
        label.SetNDC();
        label.SetTextSize(0.055);
        label.DrawLatex(0.18, 0.84, (pt + " p_{T}, fit bin " + std::to_string(bin)).c_str());
        if (bin == 0) {
            label.SetTextSize(0.050);
            label.DrawLatex(0.18, 0.75, "LHCb #scale[0.8]{Work in Progress}");
            TLegend *legend = new TLegend(0.45, 0.48, 0.88, 0.73);
            legend->SetBorderSize(0);
            legend->SetFillStyle(0);
            legend->SetTextSize(0.050);
            for (size_t index = 0; index < samples.size(); ++index)
                legend->AddEntry(graphs[index], samples[index].label, "L");
            legend->Draw();
        }
    }

    const std::string stem = "mass_shapes_24b4_" + pt;
    canvas->SaveAs((stem + ".pdf").c_str());
    canvas->SaveAs((stem + ".png").c_str());
    canvas->SaveAs((stem + ".C").c_str());
}

void draw_single_bin(const std::string &pt, const int bin) {
    constexpr int points = 800;
    std::vector<double> mass(points);
    for (int index = 0; index < points; ++index)
        mass[index] = 1097.5 + index * (1135. - 1097.5) / (points - 1.);

    std::array<std::vector<double>, 3> shapes;
    double maximum = 0.;
    for (size_t index = 0; index < samples.size(); ++index) {
        const std::string path = "/data/lhcb/users/lins/u1_PID_L0/"
            + std::string(samples[index].directory) + "/y/" + pt
            + "/l02ppi_" + pt + "pt_bin" + std::to_string(bin) + ".json";
        shapes[index] = signal_shape(path, mass);
        maximum = std::max(maximum,
                           *std::max_element(shapes[index].begin(), shapes[index].end()));
    }

    const std::string stem = "mass_shapes_24b4_" + pt + "_bin" + std::to_string(bin);
    TCanvas *canvas = new TCanvas(("canvas_" + stem).c_str(), "", 800, 600);
    canvas->SetLeftMargin(0.13);
    canvas->SetRightMargin(0.05);
    canvas->SetBottomMargin(0.12);
    canvas->SetTopMargin(0.07);
    canvas->SetGridx(2);
    canvas->SetGridy(2);

    TH1D *frame = new TH1D(("frame_" + stem).c_str(), "", 100, 1097.5, 1135.);
    frame->SetMinimum(0.);
    frame->SetMaximum(1.22 * maximum);
    frame->GetXaxis()->SetTitle("#it{m}(#it{p}#pi) [MeV/#it{c}^{2}]");
    frame->GetYaxis()->SetTitle("Normalised signal shape");
    frame->GetXaxis()->SetTitleSize(0.052);
    frame->GetXaxis()->SetLabelSize(0.045);
    frame->GetYaxis()->SetTitleSize(0.052);
    frame->GetYaxis()->SetLabelSize(0.045);
    frame->GetYaxis()->SetTitleOffset(1.15);
    frame->Draw();

    std::array<TGraph *, 3> graphs;
    for (size_t index = 0; index < samples.size(); ++index) {
        graphs[index] = new TGraph(points, mass.data(), shapes[index].data());
        graphs[index]->SetLineColor(samples[index].colour);
        graphs[index]->SetLineWidth(2);
        graphs[index]->Draw("L SAME");
    }

    TLatex label;
    label.SetNDC();
    label.SetTextSize(0.045);
    label.DrawLatex(0.16, 0.88, "LHCb #scale[0.8]{Work in Progress}");
    label.DrawLatex(0.16, 0.82, "#sqrt{#it{s}} = 13.6 TeV, 2024 Block 4, MagDown");
    label.DrawLatex(0.16, 0.76, (pt + " p_{T}, fit bin " + std::to_string(bin)).c_str());

    TLegend *legend = new TLegend(0.55, 0.57, 0.91, 0.73);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(0.040);
    for (size_t index = 0; index < samples.size(); ++index)
        legend->AddEntry(graphs[index], samples[index].label, "L");
    legend->Draw();

    canvas->SaveAs((stem + ".pdf").c_str());
    canvas->SaveAs((stem + ".png").c_str());
    canvas->SaveAs((stem + ".C").c_str());
}

}  // namespace

void plot_24b4_signal_shapes(const char *pt = "all") {
    gStyle->SetOptStat(0);
    if (std::string(pt) == "all") {
        for (const std::string category : {"vh", "h", "m", "l"}) draw_pt(category);
        return;
    }
    draw_pt(pt);
}

void plot_24b4_signal_shapes_per_bin(const char *pt = "all") {
    gStyle->SetOptStat(0);
    const std::vector<std::string> categories = (std::string(pt) == "all")
        ? std::vector<std::string>{"vh", "h", "m", "l"}
        : std::vector<std::string>{pt};
    for (const std::string &category : categories)
        for (int bin = 0; bin < n_bins(category); ++bin)
            draw_single_bin(category, bin);
}
