// Proton-PID separation ROCs for the 2026 calibration samples, one figure per
// (proton sample, mis-ID leg):
//   * L0 :  Lambda^0   -> p pi     (sample_set "newL0")   x  mis-ID K  /  mis-ID pi
//   * Lc :  Lambda_c^+ -> p K pi   (sample_set "Lc"  )    x  mis-ID K  /  mis-ID pi
//
// The ID leg is the proton sample; the mis-ID leg is the dedicated K or Pi
// calibration sample, so the two legs come from DIFFERENT files and the batch
// tag has to resolve in both. That is what the "s26c1"/"s26c2" tags are for:
// they name the 2026 conditions in the proton finals map AND in the K/Pi map
// (plain "26c1"/"26c2" address the older legacy-naming K/Pi histograms).
//
// Cut variable follows the particle pair: p vs K scans DLLp-DLLK>, p vs pi
// scans DLLp>. The proton files cover -50..50 in 0.5 steps and the 2026 K/Pi
// files -20..30 in 0.1 steps, so -20..30 every 0.5 is the common grid.
//
// Series and colours match perf_L0_Lc_26.cc and ROC_KPi_26c1_v_26c2.cc: both
// polarities of each 2026 batch. There is no 25c4 reference here — its proton
// and K/Pi histograms are binned on yet another momentum grid, so it cannot
// share this figure's kinematic region cleanly.
//
// Compile + run with:  ./compile_and_run.sh ROC_pK_pPi_L0_Lc_26.cc

#include "QROCCollection.hh"
#include "QHistogramSource.hh"

#include "TColor.h"
#include "TAttMarker.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace {

const std::string DIR    = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";
// 3D (P, ETA, nLongTracks) fallback: the 26c1 MagUp 2d proton jobs were killed
// on the memory limit, so that ID leg is read from the 3d histograms and
// marginalised over the full nLongTracks range back into 2d. Only the proton
// leg is affected — the K/Pi mis-ID leg has its 2d histograms.
const std::string DIR_3D = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/";

// Kinematic region applied to BOTH legs of every ROC point.
//
// Each ROC point divides a pass count by a total count integrated over the
// whole histogram, so the two legs have to cover the same kinematics or the
// ratio is meaningless. They do not by default: the proton histograms are
// binned in momentum from 9300 MeV/c and the K/Pi ones from 15800, so ~17% of
// the proton statistics come from a region the mis-ID leg cannot see.
//
// The two momentum grids only line up from 22000 onwards:
//     proton  ... 9300, 17700, 19500, [22000, 26000, 30000, ... 150000]
//     K / Pi  ...       15800, 19000, [22000, 26000, 30000, ... 150000]
// so 22000 is the lowest edge that exists in both. A looser bound does not
// help: QH2 keeps only bins lying wholly inside the region, so asking for
// 19000 would start the proton leg at 19500 and the K/Pi leg at 19000 and
// leave the same kind of mismatch. Above 22000 every edge is shared, and the
// eta axes already span 1.5-5.0 in both, so momentum is the only axis that
// needs pinning.
const QRegion REGION = {{"P", {22000., 150000.}}};

// Common cut grid (see header note).
const double LOOSEST  = -20.;
const double STRICTEST =  30.;
const double INTERVAL  =   .5;

struct Dataset{
    std::string batch;      // batch tag resolving in BOTH the proton and K/Pi maps
    std::string polarity;   // "down" or "up"
    std::string label;      // legend text == colour_map / marker_map key
    Color_t     colour;
    Style_t     marker;
    Size_t      size;
    bool        id_only_3d; // proton ID leg exists only as 3d histograms
};

// Small open circles, one size for every series: the curves are dense enough
// along the scan that a marker any larger just smears them together, and the
// ROC axes are log-y, where colour alone separates the four well.
const std::vector<Dataset> DATASETS = {
    {"s26c1", "down", "26c1 MagDown", kRed    + 2, 24, .4f, false},
    {"s26c1", "up",   "26c1 MagUp",   kAzure  + 3, 24, .4f, true },
    {"s26c2", "down", "26c2 MagDown", kTeal   - 8, 24, .4f, false},
    {"s26c2", "up",   "26c2 MagUp",   kViolet + 2, 24, .4f, false}
};

// One ROC figure: proton ID leg from sample_set, mis-ID leg from the K or Pi
// calibration sample.
void make_figure(const std::string &sample_set,   // "newL0" or "Lc"
                 const std::string &sample_tag,   // "L0" or "Lc" (file-name stub)
                 const std::string &second){      // mis-ID leg, "K" or "Pi"
    const QHistogramSource id_source    = QHistogramSource::finals(DIR, sample_set);
    const QHistogramSource id_source_3d = QHistogramSource::finals_3d(DIR_3D, sample_set);
    const QHistogramSource misid_source = QHistogramSource::finals(DIR, second);

    QROCCollection curves("P", second, LOOSEST, STRICTEST, INTERVAL,
                          id_source, misid_source, &REGION);
    std::unordered_map<std::string, Color_t> colours;
    std::unordered_map<std::string, Style_t> markers;
    std::unordered_map<std::string, Size_t>  sizes;

    for (const Dataset &d : DATASETS){
        curves.add_curve(d.batch, d.polarity, d.label,
                         d.id_only_3d ? id_source_3d : id_source, misid_source);
        colours[d.label] = d.colour;
        markers[d.label] = d.marker;
        sizes  [d.label] = d.size;
    }

    curves.create_figure("ROC_P_" + second + "_" + sample_tag + "_26",
                         &colours, &markers, {0.7, 1.005}, {1.e-3, 1.}, &sizes);
    curves.export_canvas();
}

}  // namespace

int main(){
    for (const auto &sample : {std::pair<std::string, std::string>{"newL0", "L0"},
                               std::pair<std::string, std::string>{"Lc",    "Lc"}})
        for (const std::string &second : {std::string("K"), std::string("Pi")})
            make_figure(sample.first, sample.second, second);

    return 0;
}
