#include "QHistogramSource.hh"
#include "QPerfCollection.hh"

#include "TColor.h"

#include <string>
#include <unordered_map>

namespace {

const std::string kFinals2D = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";
const std::string kBatch = "26c2";
const std::string kPolarity = "down";
const double kCut = 5.;

void make_comparison(const std::string& physics_sample,
                     const std::string& rebuilt_root,
                     const std::string& name_prefix,
                     const std::string& second_particle,
                     double p_min, double p_max,
                     double eta_min, double eta_max) {
    const QHistogramSource previous = QHistogramSource::finals(kFinals2D, physics_sample);
    const QHistogramSource rebuilt(kFinals2D + rebuilt_root, physics_sample,
                                   QHistogramSource::NamingMode::Finals,
                                   QHistogramSource::CutScheme::DLL,
                                   "P.ETA-bin_scheme_hi_stats_sim");

    QPerfCollection curves("P", second_particle, kCut);
    curves.add_perf(kBatch, kPolarity, "Previous (283 files)", previous);
    curves.add_perf(kBatch, kPolarity, "Rebuilt (286 files)", rebuilt);

    const std::unordered_map<std::string, Color_t> colours = {
        {"Previous (283 files)", kAzure + 3},
        {"Rebuilt (286 files)",  kRed + 1},
    };
    const std::unordered_map<std::string, Style_t> markers = {
        {"Previous (283 files)", 24},
        {"Rebuilt (286 files)",  20},
    };
    const std::unordered_map<std::string, Size_t> sizes = {
        {"Previous (283 files)", 1.05f},
        {"Rebuilt (286 files)",  0.85f},
    };

    curves.create_figures(name_prefix + "_P_" + second_particle + "_gt5",
                          p_min, p_max, eta_min, eta_max,
                          &colours, &markers, &sizes);
    curves.export_canvases();
}

}  // namespace

int main() {
    make_comparison("newL0", "26c2dcheck_L0", "L0_26c2d_previous_vs_rebuilt",
                    "K",  .70, 1.10, .40, 1.15);
    make_comparison("newL0", "26c2dcheck_L0", "L0_26c2d_previous_vs_rebuilt",
                    "Pi", .70, 1.10, .40, 1.15);
    make_comparison("Lc", "26c2dcheck_Lc", "Lc_26c2d_previous_vs_rebuilt",
                    "K",  .80, 1.08, .65, 1.13);
    make_comparison("Lc", "26c2dcheck_Lc", "Lc_26c2d_previous_vs_rebuilt",
                    "Pi", .80, 1.08, .65, 1.13);
}
