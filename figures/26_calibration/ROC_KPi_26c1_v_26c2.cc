// K/pi separation (DLLK > x scan) for the 2026 K & Pi calibration samples,
// comparing s26c1 against s26c2 (bovill's effhists, binning_scheme_George).
//
// Both batches are on disk for both polarities
// (2026_s26c{1,2}_beta_fixed-{up,down}), so all four curves are drawn and the
// batch comparison is polarity-matched: batch is read off the marker shape
// (square = 26c1, circle = 26c2) and polarity off the fill (filled = MagDown,
// open = MagUp).
//
// Compile + run with:  ./compile_and_run.sh ROC_KPi_26c1_v_26c2.cc

#include "QROCCollection.hh"
#include "QHistogramSource.hh"

#include "TColor.h"

#include <string>
#include <unordered_map>

int main(){
    const std::string dir = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";

    // ID leg: K sample; mis-ID leg: Pi sample. Files provide DLLK> from -20 to
    // +30 in 0.1 steps; scan every 0.5 to keep the marker density readable.
    const QHistogramSource id_source    = QHistogramSource::finals(dir, "K");
    const QHistogramSource misid_source = QHistogramSource::finals(dir, "Pi");

    // Same kinematic region as ROC_pK_pPi_L0_Lc_26.cc, so the two sets of ROCs
    // are quoted over identical kinematics. Unlike there, it is not needed to
    // fix a mismatch: both legs here are K/Pi samples and already share one
    // momentum grid (15800 ... 150000). 22000 is the lowest edge that grid has
    // in common with the proton grid used by the other figure.
    const QRegion region = {{"P", {22000., 150000.}}};

    QROCCollection curves("K", "Pi", -20., 30., .5, id_source, misid_source, &region);
    curves.add_curve("s26c1", "down", "26c1 MagDown");
    curves.add_curve("s26c1", "up",   "26c1 MagUp");
    curves.add_curve("s26c2", "down", "26c2 MagDown");
    curves.add_curve("s26c2", "up",   "26c2 MagUp");

    // House palette, in order, skipping the leading kGray+1.
    const std::unordered_map<std::string, Color_t> colours = {
        {"26c1 MagDown", kRed    + 2},
        {"26c1 MagUp",   kAzure  + 3},
        {"26c2 MagDown", kTeal   - 8},
        {"26c2 MagUp",   kViolet + 2},
    };
    // Small open circles, one size for every series: the curves are dense enough
    // along the scan that a marker any larger just smears them together, and the
    // ROC axes are log-y, where colour alone separates the four well.
    const std::unordered_map<std::string, Style_t> markers = {
        {"26c1 MagDown", 24},
        {"26c1 MagUp",   24},
        {"26c2 MagDown", 24},
        {"26c2 MagUp",   24},
    };
    const std::unordered_map<std::string, Size_t> sizes = {
        {"26c1 MagDown", .4f},
        {"26c1 MagUp",   .4f},
        {"26c2 MagDown", .4f},
        {"26c2 MagUp",   .4f},
    };

    curves.create_figure("ROC_KPi_26c1_v_26c2", &colours, &markers,
                         {0.7, 1.005}, {1.e-3, 1.}, &sizes);
    curves.export_canvas();

    return 0;
}
