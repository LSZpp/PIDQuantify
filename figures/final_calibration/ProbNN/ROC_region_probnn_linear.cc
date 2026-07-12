// DLL vs LINEAR-ProbNN p->K ROC in the controlled kinematic region, 2025 c3 (up).
// Twin of ROC_region_probnn.cc, but the ProbNN curves use the LINEAR cut grid
// (PROBNN_P>cut/100, cut = 0..100 step 0.2 -> 501 pts) instead of the log grid,
// which samples the wide efficiency axis far more densely. One figure, 4 curves:
//   DLL    : Updated L0 (kRed+1) and Lc (kBlue+2), open square (25)
//   ProbNN : Updated L0 (kRed-1) and Lc (kBlue-1), open circle (24)
//
// Region (enclosed bins):
//   p[22000,26000] MeV, eta[2.45,2.59], nLongTracks[83,117].
// mis-ID y-axis floored at 1e-5.
//
// Compile + run with ./compile_and_run.sh ROC_region_probnn_linear.cc

#include "QROCCollection.hh"
#include "QHistogramSource.hh"
#include "QH2.hh"   // QRegion

#include <string>
#include <unordered_map>

int main(){
    const std::string DIR = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/";
    using CS = QHistogramSource::CutScheme;

    const QRegion region = {
        {"P",           {22000., 26000.}},
        {"ETA",         {2.45,   2.59}},
        {"nLongTracks", {83.,    117.}},
    };

    // DLL 3D sources (default cut scheme).
    const QHistogramSource new_dll = QHistogramSource::finals_3d(DIR, "newL0", 83., 117.);
    const QHistogramSource lc_dll  = QHistogramSource::finals_3d(DIR, "Lc",    83., 117.);
    const QHistogramSource k_dll   = QHistogramSource::finals_3d(DIR, "K",     83., 117.);
    // Linear-ProbNN 3D sources.
    const QHistogramSource new_pnn = QHistogramSource::finals_3d(DIR, "newL0", 83., 117., CS::ProbNNLinear);
    const QHistogramSource lc_pnn  = QHistogramSource::finals_3d(DIR, "Lc",    83., 117., CS::ProbNNLinear);
    const QHistogramSource k_pnn   = QHistogramSource::finals_3d(DIR, "K",     83., 117., CS::ProbNNLinear);

    const std::string DLL_NEW = "Updated #it{#Lambda}^{0} #rightarrow #it{p#pi}, DLL";
    const std::string DLL_LC  = "#it{#Lambda}_{#it{c}} #rightarrow #it{pK#pi}, DLL";
    const std::string PNN_NEW = "Updated #it{#Lambda}^{0} #rightarrow #it{p#pi}, ProbNN";
    const std::string PNN_LC  = "#it{#Lambda}_{#it{c}} #rightarrow #it{pK#pi}, ProbNN";

    const std::unordered_map<std::string, Color_t> colours = {
        {DLL_NEW, kRed  + 1}, {DLL_LC, kBlue + 2},
        {PNN_NEW, kRed  - 1}, {PNN_LC, kBlue - 1},
    };
    const std::unordered_map<std::string, Style_t> markers = {
        {DLL_NEW, 25}, {DLL_LC, 25},   // open square  -> DLL
        {PNN_NEW, 24}, {PNN_LC, 24},   // open circle  -> ProbNN
    };

    QROCCollection curves("P", "K", -50., 50., .5, &region);   // default grid = DLL
    curves.add_curve("25c3", "up", DLL_NEW, new_dll, k_dll);
    curves.add_curve("25c3", "up", DLL_LC,  lc_dll,  k_dll);
    curves.add_curve("25c3", "up", PNN_NEW, 0., 100., .2, new_pnn, k_pnn);
    curves.add_curve("25c3", "up", PNN_LC,  0., 100., .2, lc_pnn,  k_pnn);
    curves.create_figure("region_dll_probnn_linear_2025_c3", &colours, &markers, {0.7, 1.005}, {1.e-5, 1.});
    curves.export_canvas();

    return 0;
}
