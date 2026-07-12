// DLL vs LINEAR-ProbNN p->K ROC, 2025 c3, L0 reweighted to the Lc profile.
// Copy of ROC_region_reweight_linear.cc for the HIGH-p region p[60000,97500] MeV
// with eta [2.73,3.54] and NO nLongTracks restriction (full range), for stats.
//   DLL    : Updated L0 (kRed+1)  and Lc (kBlue+2),  open square (25)
//   ProbNN : Updated L0 (kRed-4)  and Lc (kBlue-9),  open circle (24)
// Only the L0 curves are reweighted (Lc is the target).
//
// Region (enclosed bins):
//   p[60000,97500] MeV, eta[2.73,3.54], nLongTracks unrestricted
// mis-ID y-axis floored at 1e-5.
//
// Compile + run with ./compile_and_run.sh ROC_region_reweight_linear_p60to97.cc

#include "QROCCollection.hh"
#include "QHistogramSource.hh"
#include "QH2.hh"   // QRegion, QReweight

#include "TFile.h"
#include "TH3D.h"

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

int main(){
    const std::string DIR = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/";
    using CS = QHistogramSource::CutScheme;

    const QRegion region = {
        {"P",   {60000., 97500.}},
        {"ETA", {2.73,   3.54}},
        // nLongTracks unrestricted (full range) for stats.
    };

    // Source/target "total" (sWeighted) 3D histograms for the L0->Lc reweighting.
    // "total" is cut-independent, so any cut file works; keep them alive for the
    // whole run (every L0 QH2 reads them at construction).
    auto load_total = [](const std::string &path) -> TH3D* {
        TFile *f = TFile::Open(path.c_str());
        if (!f || f->IsZombie()) throw std::runtime_error("cannot open " + path);
        TH3D *h = dynamic_cast<TH3D*>(f->Get("total"));
        if (!h) throw std::runtime_error("no total in " + path);
        h->SetDirectory(nullptr); f->Close(); delete f;
        return h;
    };
    TH3D *L0_total = load_total(DIR + "newL0/effhists-L0_2025_c3-up-P-DLLp-DLLK>0.0-P.ETA.nLongTracks.root");
    TH3D *Lc_total = load_total(DIR + "Lc/effhists-Lc_2025_c3-up-P-DLLp-DLLK>0.0-P.ETA.nLongTracks.root");
    const QReweight reweight = {L0_total, Lc_total};   // first=source(L0), second=target(Lc)

    // DLL and linear-ProbNN 3D sources (full nLongTracks z-range).
    const QHistogramSource new_dll = QHistogramSource::finals_3d(DIR, "newL0", 0., 600.);
    const QHistogramSource lc_dll  = QHistogramSource::finals_3d(DIR, "Lc",    0., 600.);
    const QHistogramSource k_dll   = QHistogramSource::finals_3d(DIR, "K",     0., 600.);
    const QHistogramSource new_pnn = QHistogramSource::finals_3d(DIR, "newL0", 0., 600., CS::ProbNNLinear);
    const QHistogramSource lc_pnn  = QHistogramSource::finals_3d(DIR, "Lc",    0., 600., CS::ProbNNLinear);
    const QHistogramSource k_pnn   = QHistogramSource::finals_3d(DIR, "K",     0., 600., CS::ProbNNLinear);

    const std::string DLL_NEW = "Updated #it{#Lambda}^{0} #rightarrow #it{p#pi}, PID";
    const std::string DLL_LC  = "#it{#Lambda}_{#it{c}} #rightarrow #it{pK#pi}, PID";
    const std::string PNN_NEW = "Updated #it{#Lambda}^{0} #rightarrow #it{p#pi}, ProbNN";
    const std::string PNN_LC  = "#it{#Lambda}_{#it{c}} #rightarrow #it{pK#pi}, ProbNN";

    const std::unordered_map<std::string, Color_t> colours = {
        {DLL_NEW, kRed  + 1}, {DLL_LC, kBlue + 2},
        {PNN_NEW, kRed  - 4}, {PNN_LC, kBlue - 9},
    };
    const std::unordered_map<std::string, Style_t> markers = {
        {DLL_NEW, 25}, {DLL_LC, 25},   // open square  -> DLL
        {PNN_NEW, 24}, {PNN_LC, 24},   // open circle  -> ProbNN
    };

    QROCCollection curves("P", "K", -50., 50., .5, &region);   // default grid = DLL
    curves.add_curve("25c3", "up", DLL_NEW, new_dll, k_dll, &reweight);   // L0: reweighted
    curves.add_curve("25c3", "up", DLL_LC,  lc_dll,  k_dll);              // Lc: target, no reweight
    curves.add_curve("25c3", "up", PNN_NEW, 0., 100., .2, new_pnn, k_pnn, &reweight);
    curves.add_curve("25c3", "up", PNN_LC,  0., 100., .2, lc_pnn,  k_pnn);
    curves.create_figure("region_reweight_dll_probnn_linear_2025_c3_p60to97", &colours, &markers,
                         {0.7, 1.}, {1.e-4, 1.});
    curves.export_canvas();

    delete L0_total;
    delete Lc_total;
    return 0;
}
