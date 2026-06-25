#include "QPerfCollection.hh"

#include <string>

int main(){
    const std::string directory = "/data/lhcb/users/lins/u3_PIDQuantify/histograms_26/";

    for (const double cut : {0., 5.}){
        QPerfCollection curves("P", "K", cut);
        curves.add_perf("25c4", "down", "25c4 MAGdown", directory);
        curves.add_perf("26c1", "down", "26c1 MAGdown", directory);

        const std::string cut_label = (cut == 0.) ? "DLLp_DLLK_gt0" : "DLLp_DLLK_gt5";
        curves.create_figures("P_K_26c1_v_2025c4_magdown_" + cut_label, .5, 1.13);
        curves.export_canvases();
    }

    return 0;
}
