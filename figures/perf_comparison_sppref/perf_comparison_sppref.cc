#include "QPerfCollection.hh"

#include <string>

int main(){
    const std::string directory = "/data/lhcb/users/lins/u3_PIDQuantify/histograms_sppref/";

    for (const double cut : {0., 5.}){
        QPerfCollection curves("P", "K", cut);
        curves.add_perf("24c1ref", "up", "24c1 ref MAGup", directory);
        curves.add_perf("24b1", "up", "24b1 MAGup", directory);
        curves.add_perf("24b8", "up", "24b8 MAGup", directory);

        const std::string cut_label = (cut == 0.) ? "DLLp_DLLK_gt0" : "DLLp_DLLK_gt5";
        curves.create_figures("P_K_24b8_v_24c1_ref_magup_" + cut_label, .7, 1.1);
        curves.export_canvases();
    }

    return 0;
}
