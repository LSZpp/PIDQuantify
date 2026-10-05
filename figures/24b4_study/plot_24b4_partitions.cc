#include "QHistogramSource.hh"
#include "QPerfCollection.hh"

#include "TColor.h"

#include <string>
#include <unordered_map>

namespace {

const std::string finals_2d = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";
const std::string finals_3d = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/";

void make_plot(const bool use_3d) {
    const QHistogramSource source = use_3d
        ? QHistogramSource(finals_3d, "newL0",
                            QHistogramSource::NamingMode::Finals,
                            QHistogramSource::CutScheme::DLL,
                            "P.ETA.nLongTracks-bin_scheme_hi_stats_sim", true)
        : QHistogramSource(finals_2d, "newL0",
                            QHistogramSource::NamingMode::Finals,
                            QHistogramSource::CutScheme::DLL,
                            "P.ETA-bin_scheme_hi_stats_sim");

    QPerfCollection curves("P", "K", 5.);
    curves.add_perf("24b4p2", "down", "Block 4 partition 2", source);
    curves.add_perf("24b4p3", "down", "Block 4 partition 3", source);
    curves.add_perf("24b4",   "down", "Block 4 combined",    source);

    const std::unordered_map<std::string, Color_t> colours = {
        {"Block 4 partition 2", kGray + 1},
        {"Block 4 partition 3", kRed + 2},
        {"Block 4 combined",    kAzure + 3},
    };
    const std::unordered_map<std::string, Style_t> markers = {
        {"Block 4 partition 2", 20},
        {"Block 4 partition 3", 21},
        {"Block 4 combined",    24},
    };
    const std::unordered_map<std::string, Size_t> sizes = {
        {"Block 4 partition 2", 1.1f},
        {"Block 4 partition 3", 1.1f},
        {"Block 4 combined",    1.1f},
    };

    const std::string dimension = use_3d ? "3d" : "2d";
    curves.create_figures("L0_24b4_partitions_" + dimension + "_P_K_gt5",
                          .70, 1.10, .40, 1.15,
                          &colours, &markers, &sizes);
    curves.export_canvases();
}

}  // namespace

int main() {
    make_plot(false);
    make_plot(true);
}
