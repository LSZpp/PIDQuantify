#include "QPerfCollection.hh"
#include "TColor.h"
#include <unordered_map>

int main(){
    const std::string dir = "/data/lhcb/users/lins/u3_PIDQuantify/histograms_sppref/";

    const std::unordered_map<std::string, Color_t> colours = {
        {"24c1ref", kBlue+1},
        {"24b3",    kRed+1},
        {"24b8",    kOrange+7}
    };

    auto make_perf = [&](const std::string &p1, const std::string &p2, const std::string &tag){
        for (const double cut : {0., 5.}){
            QPerfCollection curves(p1, p2, cut);
            curves.add_perf("24c1ref", "up", "24c1 sppref MAGup", dir);
            curves.add_perf("24b3",    "up", "24b3 MAGup",        dir);
            curves.add_perf("24b8",    "up", "24b8 MAGup",        dir);
            const std::string name = tag + (cut == 0. ? "_gt0" : "_gt5");
            curves.create_figures(name, .4, 1.15, &colours);
            curves.export_canvases();
        }
    };

    make_perf("P",  "K",  "perf_P_sppref_b3_b8_magup_DLLp_DLLK");
    make_perf("K",  "Pi", "perf_K_sppref_b3_b8_magup_DLLK");
    make_perf("Pi", "K",  "perf_Pi_sppref_b3_b8_magup_DLLKneg");

    return 0;
}
