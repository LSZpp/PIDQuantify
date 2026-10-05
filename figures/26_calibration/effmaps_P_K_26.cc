// 2D (P, ETA) efficiency maps, one figure per batch and per calibration sample:
//   * L0 :  proton efficiency, DLLp-DLLK > 0, from Lambda^0   -> p pi
//   * Lc :  proton efficiency, DLLp-DLLK > 0, from Lambda_c^+ -> p K pi
//   * K  :  kaon   efficiency, DLLK      > 0, from the K sample
// so the two proton samples can be compared bin by bin against each other and
// against the kaons, for every batch.
//
// Batches follow the other 2026 figures: 25c4 MagDown as the reference, then
// both polarities of 26c1 and 26c2. The "s26c1"/"s26c2" tags name the 2026
// conditions in both the proton and the K/Pi dataset maps, so one tag drives
// every sample here.
//
// The z scale is pinned to [0, 1] on every map: the point is to compare batches
// against each other, which an auto-scaled palette would defeat.
//
// House-style note: on a COLZ map the top-left of the frame is painted, so the
// LHCb tag and the annotations sit in the top margin just above the frame,
// where they stay legible, rather than at the usual y = 0.86 inside it.
//
// Compile + run with:  ./compile_and_run.sh effmaps_P_K_26.cc

#include "QH2.hh"
#include "QHistogramSource.hh"

#include "TCanvas.h"
#include "TColor.h"
#include "TH2D.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TStyle.h"

#include <string>
#include <vector>

namespace {

const std::string DIR    = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";
// 3d fallback for the 26c1 MagUp proton legs, whose 2d jobs were killed on the
// memory limit: marginalising over the full nLongTracks range recovers the same
// 2d (P, ETA) efficiency.
const std::string DIR_3D = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/";

struct Series{
    std::string batch;      // batch tag resolving in the proton AND K/Pi maps
    std::string polarity;   // "down" or "up"
    std::string tag;        // file-name stub
    std::string label;      // annotation text
    bool        proton_only_3d;  // proton legs exist only as 3d histograms
};

const std::vector<Series> SERIES = {
    {"25c4",  "down", "25c4_MagDown", "25c4 MagDown", false},
    {"s26c1", "down", "26c1_MagDown", "26c1 MagDown", false},
    {"s26c1", "up",   "26c1_MagUp",   "26c1 MagUp",   true },
    {"s26c2", "down", "26c2_MagDown", "26c2 MagDown", false},
    {"s26c2", "up",   "26c2_MagUp",   "26c2 MagUp",   false}
};

// One efficiency map. first/second set the DLL cut variable exactly as they do
// for the ROC curves: (P, K) -> DLLp-DLLK>, (K, Pi) -> DLLK>.
void draw_map(const QHistogramSource &source,
              const Series      &series,
              const std::string &first,      // ID particle
              const std::string &second,     // the other leg of the DLL
              const double       cut,
              const std::string &sample_tag, // "L0", "Lc" or "K" (file-name stub)
              const std::string &cut_latex){
    const std::string name = "effmap_" + sample_tag + "_" + series.tag;

    QH2 hist(series.batch, series.polarity, first, second, "ID", cut, source);

    // Binomial errors: passed is a subset of total, so option "B" is the correct
    // per-bin uncertainty (and the only one that does not overestimate it).
    TH2D *efficiency = static_cast<TH2D*>(hist.get_passed()->Clone(name.c_str()));
    efficiency->SetDirectory(0);   // survive the input TFile closing
    efficiency->Divide(hist.get_passed(), hist.get_total(), 1., 1., "B");

    TCanvas *canvas = new TCanvas(("canvas_" + name).c_str(),
                                  ("canvas_" + name).c_str(), 820, 720);
    canvas->cd();
    gPad->SetRightMargin(.19);
    gPad->SetTopMargin  (.14);   // room for the two annotation lines above the frame

    efficiency->SetTitle("");
    efficiency->GetXaxis()->SetTitle("Momentum (MeV/#it{c})");
    efficiency->GetXaxis()->SetTitleSize  (.042);
    efficiency->GetXaxis()->SetLabelSize  (.042);
    efficiency->GetYaxis()->SetTitle("#it{#eta}");
    efficiency->GetYaxis()->SetTitleSize  (.042);
    efficiency->GetYaxis()->SetLabelSize  (.042);
    efficiency->GetZaxis()->SetTitle("Efficiency");
    efficiency->GetZaxis()->SetTitleSize  (.042);
    efficiency->GetZaxis()->SetLabelSize  (.042);
    efficiency->GetZaxis()->SetTitleOffset(1.25);
    efficiency->GetZaxis()->SetRangeUser  (0., 1.);
    efficiency->Draw("COLZ");

    TLatex latex;
    latex.SetNDC();
    latex.SetTextSize(.05);
    latex.DrawLatex(.11, .945, "LHCb #scale[0.8]{Work in Progress}");
    latex.SetTextSize(.04);
    latex.DrawLatex(.11, .885, (series.label + ",  " + cut_latex).c_str());

    canvas->SaveAs(("macro_"      + name + ".C"  ).c_str());
    canvas->SaveAs(("pdf_figure_" + name + ".pdf").c_str());
}

}  // namespace

int main(){
    gStyle->SetOptStat (0);
    gStyle->SetOptTitle(0);
    gStyle->SetPalette (kRainbow);
    gStyle->SetNumberContours(256);
    // The x-axis "x10^3" exponent lands on the palette at the default offset.
    TGaxis::SetExponentOffset(-.035, .005, "x");

    const std::string proton_cut_latex = "#DeltaLL( #it{p} - #it{K} ) > 0";
    const std::string kaon_cut_latex   = "#DeltaLL( #it{K} - #it{#pi} ) > 0";

    const QHistogramSource l0_source    = QHistogramSource::finals   (DIR,    "newL0");
    const QHistogramSource l0_source_3d = QHistogramSource::finals_3d(DIR_3D, "newL0");
    const QHistogramSource lc_source    = QHistogramSource::finals   (DIR,    "Lc"   );
    const QHistogramSource lc_source_3d = QHistogramSource::finals_3d(DIR_3D, "Lc"   );
    const QHistogramSource k_source     = QHistogramSource::finals   (DIR,    "K"    );

    for (const Series &series : SERIES){
        // Protons: the same cut on both calibration samples, drawn separately.
        draw_map(series.proton_only_3d ? l0_source_3d : l0_source,
                 series, "P", "K", 0., "L0", proton_cut_latex);
        draw_map(series.proton_only_3d ? lc_source_3d : lc_source,
                 series, "P", "K", 0., "Lc", proton_cut_latex);

        // Kaons: the K sample has its 2d histograms for every batch here.
        draw_map(k_source, series, "K", "Pi", 0., "K", kaon_cut_latex);
    }

    return 0;
}
