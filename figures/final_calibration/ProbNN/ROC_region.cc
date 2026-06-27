// Region-restricted p->K ROC curves comparing new L0 vs Lc, one figure per
// combined batch group. The region is the kinematically-controlled corner where
// L0 and Lc kinematics barely differ:
//     p           in [22000, 26000] MeV
//     eta         in [2.45, 2.59]
//     nLongTracks in [83, 117]
// (only fully-enclosed 3D bins are kept, via the new QROCCollection region option).
//
// Built on the 3D effhists (P x ETA x nLongTracks). Two curves per figure:
//   Updated L0 (red, open square 25) and Lc (blue, filled square 21) -- same
//   colour scheme as the 1D / ROC_curves comparison plots. If kinematics are the
//   only difference, the two curves should lie on top of each other.
//
// Compile + run with ./compile_and_run.sh ROC_region.cc

#include "QROCCollection.hh"
#include "QHistogramSource.hh"
#include "QH2.hh"            // for QRegion

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <unordered_map>

int main(){
    const std::string DIR = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/";

    // Phase-space region (physical units). Only fully-enclosed bins are kept.
    const QRegion region = {
        {"P",           {22000., 26000.}},
        {"ETA",         {2.45,   2.59}},
        {"nLongTracks", {83.,    117.}},
    };

    // 3D sources (probe P for the proton ID legs, K for the mis-ID leg).
    const QHistogramSource src_new = QHistogramSource::finals_3d(DIR, "newL0", 83., 117.);
    const QHistogramSource src_lc  = QHistogramSource::finals_3d(DIR, "Lc",    83., 117.);
    const QHistogramSource src_k   = QHistogramSource::finals_3d(DIR, "K",     83., 117.);

    // Labels / colours / markers match the 1D + ROC_curves comparison plots.
    const std::string LABEL_NEW = "Updated #it{#Lambda}^{0} #rightarrow #it{p#pi}";
    const std::string LABEL_LC  = "#it{#Lambda}_{#it{c}} #rightarrow #it{pK#pi}";
    const std::unordered_map<std::string, Color_t> colours = {
        {LABEL_NEW, kRed  + 1},
        {LABEL_LC,  kBlue + 2},
    };
    const std::unordered_map<std::string, Style_t> markers = {
        {LABEL_NEW, 25},   // Updated L0 as open square; Lc keeps filled square (21)
    };

    // Combined batch groups (batch keys resolve in both the proton and K maps).
    // NOTE: 2025 c234 omits c4-magup because its 3D kaon histograms do not exist.
    struct Group { std::string name; std::vector<std::string> batches, pols; };
    const std::vector<Group> groups = {
        {"2024_b12356", {"24b1","24b2","24b3","24b5","24b6"}, {"up","up","up","up","down"}},
        {"2024_b78",    {"24b7","24b8"},                       {"down","up"}},
        {"2025_c1",     {"25c1","25c1"},                       {"down","up"}},
        {"2025_c234",   {"25c2","25c3","25c4"},                {"down","up","down"}},
    };

    for (const auto &g : groups){
        QROCCollection curves("P", "K", -50., 50., .5, &region);
        curves.add_curve(g.batches, g.pols, LABEL_NEW, src_new, src_k);
        curves.add_curve(g.batches, g.pols, LABEL_LC,  src_lc,  src_k);
        curves.create_figure("region_P_K_" + g.name, &colours, &markers, {0.7, 1.005}, {1.e-5, 1.});
        curves.export_canvas();
    }

    return 0;
}
