// 2026 PID performance overlays for the calibration samples:
//   * L0 :  Lambda^0   -> p pi     (sample_set "newL0")  proton ID
//   * Lc :  Lambda_c^+ -> p K pi   (sample_set "Lc"  )   proton ID
//   * K  :  D*+        -> D0 pi    (sample_set "K"   )   kaon ID, K/pi separation
//
// ONE figure per (sample, mis-ID leg), with EVERY dataset overlaid on it:
// 2025_c4 MagDown as the reference, then 2026_c1 and 2026_c2 in both polarities.
// Colour encodes the batch, the marker fill encodes the polarity (filled =
// MagDown, open = MagUp). QPerfCollection then splits each figure into a
// momentum (_p) and a pseudorapidity (_eta) projection.
//
// Only the strict DLL( first - second ) > 5 working point is drawn.
//
// Compile + run with:  ./compile_and_run.sh perf_L0_Lc_26.cc

#include "QPerfCollection.hh"
#include "QHistogramSource.hh"

#include "TColor.h"
#include "TAttMarker.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace {

// Finals efficiency histograms (2D, P vs ETA) for the L0 / Lc / K samples.
const std::string DIR    = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";
// 3D (P, ETA, nLongTracks) fallback: the 26c1 MagUp 2d jobs were killed on the
// memory limit for both proton samples, but the 3d histograms survived, so that
// series is read from here and marginalised over the full nLongTracks range
// into 2d. The K sample is unaffected and keeps its 2d histograms.
const std::string DIR_3D = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/";

// The DLL working point: DLL( first - second ) > 5.
const double CUT = 5.;

// Kinematic region for the K/pi figure only (see sample_region below).
//
// The eta profile averages the efficiency over the whole momentum axis, so it
// only compares like with like if every series covers the same momenta. The
// proton samples need no help there: every proton series, 25c4 and 2026 alike,
// is binned on the same 20-bin grid 9300 ... 150000, so they already integrate
// identical momenta. The K/Pi histograms use a different grid (19 bins from
// 15800), and 22000 is the lowest edge the two share:
//     proton      ... 9300, 17700, 19500, [22000, 26000, ... 150000]
//     K / Pi 2026 ...       15800, 19000, [22000, 26000, ... 150000]
//
// It is deliberately NOT applied to the proton figures. Pseudorapidity 1.5-1.9
// is the large-angle edge of the acceptance, where the momentum spectrum is
// soft: cutting at 22000 throws away ~76% of that bin and leaves a hard-tail
// remnant that is ~100% efficient and statistically thin, so the first point
// lands at or above 1 with a collapsed error bar (QH2Perf zeroes the binomial
// error once the efficiency reaches 1). The unrestricted profile is the honest
// one for those samples.
const QRegion REGION = {{"P", {22000., 150000.}}};

// The region applies to the K/pi figure only. There it is for consistency with
// the ROC macros rather than to repair a mismatch: 25c4 is no longer drawn on
// that figure, so its remaining series already share one momentum grid.
const QRegion *sample_region(const std::string &sample_set){
    return (sample_set == "K") ? &REGION : nullptr;
}

// Every series drawn on each figure: 25c4 as the MagDown-only grey reference
// (Lc figures only), then both polarities of each 2026 batch. Colours follow
// the house order
// (grey, then red / azure / teal / violet) and match ROC_KPi_26c1_v_26c2.cc, so
// a series keeps its colour across the ROC and performance figures.
//
// The markers are chosen so that no series hides another: the curves agree to
// well within the marker size, and a filled marker simply paints over whatever
// is underneath it. Every series is therefore the same open circle (style 24),
// which is an outline with nothing inside it, and the sizes descend in draw
// order so each circle sits inside the one before it and stays legible.
// Colour, not shape, separates the series.
struct Dataset{
    std::string batch;     // batch tag understood by QHistogramSource
    std::string polarity;  // "down" or "up"
    std::string label;     // legend text == colour / style / size map key
    Color_t     colour;
    Style_t     marker;
    Size_t      size;
    bool        only_3d;   // no 2d histograms for the proton samples: read from
                           // the 3d source instead (marginalised back to 2d)
    bool        lc_only;   // draw on the Lc figures only (see note below)
};

// 25c4 is drawn on Lc only. Its K histograms (2025_c4_v0) are binned in
// momentum from 9300 MeV/c whereas every 2026 K/Pi histogram starts at 15800,
// and the eta profile integrates over the whole momentum axis — so that extra
// low-momentum population (17% of the sample, at 99% kaon efficiency) lifts the
// whole 25c4 eta curve and fakes a ~2% excess over 2026. The same comparison
// restricted to p > 22 GeV/c, where the grids coincide, puts 25c4 slightly
// BELOW 2026. The L0 figures are dropped for the same reason: there the eta
// profile is pulled the other way by a softer 2026 momentum spectrum, so
// neither figure compares like with like.
const std::vector<Dataset> DATASETS = {
    {"25c4", "down", "25c4 MagDown", kGray   + 1, 24, 1.30f, false, true },
    {"26c1", "down", "26c1 MagDown", kRed    + 2, 24, 1.10f, false, false},
    {"26c1", "up",   "26c1 MagUp",   kAzure  + 3, 24, 0.90f, true , false},
    {"26c2", "down", "26c2 MagDown", kTeal   - 8, 24, 0.70f, false, false},
    {"26c2", "up",   "26c2 MagUp",   kViolet + 2, 24, 0.50f, false, false}
};

// The proton samples use the batch tags above; the K/pi figure reads the K
// sample, whose 2026 histograms are keyed by the "s" tags (same conditions).
std::string sample_batch(const std::string &sample_set, const std::string &batch){
    if (sample_set != "K") return batch;
    if (batch == "26c1") return "s26c1";
    if (batch == "26c2") return "s26c2";
    return batch;   // 25c4 is spelled the same way in the K/Pi dataset map
}

// Vertical range of the two projections, chosen per figure: the p and the eta
// projection of the same efficiency rarely span the same range.
struct Range{
    double p_min, p_max;
    double eta_min, eta_max;
};

// One overlay figure (a _p and an _eta canvas) with all datasets on it.
void make_figure(const std::string &sample_set,   // "newL0", "Lc" or "K"
                 const std::string &name_stub,    // file-name stub
                 const std::string &first,        // ID leg,      "P" or "K"
                 const std::string &second,       // mis-ID leg,  "K" or "Pi"
                 const Range       &range){
    const QHistogramSource source    = QHistogramSource::finals(DIR, sample_set);
    // Full-range marginalisation: no nLongTracks window (defaults 0., 0.), so
    // the 3d pass/total counts are summed over every nLongTracks slice — the
    // same 2d (P, ETA) efficiency the missing 2d histograms would have given.
    const QHistogramSource source_3d = QHistogramSource::finals_3d(DIR_3D, sample_set);

    QPerfCollection curves(first, second, CUT, sample_region(sample_set));
    std::unordered_map<std::string, Color_t> colours;
    std::unordered_map<std::string, Style_t> markers;
    std::unordered_map<std::string, Size_t>  sizes;

    for (const Dataset &d : DATASETS){
        if (d.lc_only && (sample_set != "Lc")) continue;
        // Only the proton samples lost their 2d histograms for that series.
        const bool use_3d = d.only_3d && (sample_set != "K");
        curves.add_perf(sample_batch(sample_set, d.batch),
                        d.polarity,
                        d.label,
                        use_3d ? source_3d : source);
        colours[d.label] = d.colour;
        markers[d.label] = d.marker;
        sizes  [d.label] = d.size;
    }

    const std::string name = "perf_" + name_stub + "_26_gt5";
    curves.create_figures(name,
                          range.p_min,   range.p_max,
                          range.eta_min, range.eta_max,
                          &colours, &markers, &sizes);
    curves.export_canvases();
}

}  // namespace

int main(){
    // Proton ID from the two proton samples, against both mis-ID legs.
    const Range L0_RANGE{.7,  1.10, .4,  1.15};
    const Range LC_RANGE{.8,  1.08, .65, 1.13};
    for (const std::string &second : {std::string("K"), std::string("Pi")}){
        make_figure("newL0", "L0_P_" + second, "P", second, L0_RANGE);
        make_figure("Lc",    "Lc_P_" + second, "P", second, LC_RANGE);
    }

    // K/pi separation: kaon ID efficiency under DLLK > 5 from the K sample.
    const Range K_RANGE{.0, 1.30, .4, 1.20};
    make_figure("K", "KPi", "K", "Pi", K_RANGE);

    return 0;
}
