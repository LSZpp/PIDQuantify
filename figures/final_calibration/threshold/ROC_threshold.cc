// New-L0 combined p->K ROC for the three data-period groups, with and without the
// L0 turn-on momentum bin [9300,17700]. Same colour scheme as ROC_combined_comparison
// (kP8Blue per group); 25c2/3/4 drawn as a hollow box, the other two solid boxes.
//
// Compile + run:  ./compile_and_run.sh ROC_threshold.cc

#include "QROCCollection.hh"
#include "QHistogramSource.hh"
#include "QH2.hh"   // QRegion

#include <string>
#include <vector>
#include <unordered_map>

int main(){
    const std::string DIR2D = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";
    const auto id  = QHistogramSource::finals(DIR2D, "newL0");   // proton ID, probe P
    const auto mis = QHistogramSource::finals(DIR2D, "K");       // kaon mis-ID, probe K

    const QRegion no_threshold = {{"P", {17700., 150000.}}};     // drop bin 1 [9300,17700]

    const std::unordered_map<std::string, Color_t> col = {
        {"24b7/8", kP8Blue}, {"25c1", kP8Blue + 1}, {"25c2/3/4", kP8Blue + 2}};
    const std::unordered_map<std::string, Style_t> mrk = {{"25c2/3/4", 25}};  // others -> 21

    auto build = [&](const QRegion *region, const std::string &name){
        using V = std::vector<std::string>;
        QROCCollection c("P", "K", -50., 50., .5, id, mis, region);
        c.add_curve(V{"24b7", "24b8"},                 V{"down", "up"},           "24b7/8");
        c.add_curve(V{"25c1", "25c1"},                 V{"down", "up"},           "25c1");
        c.add_curve(V{"25c2", "25c3", "25c4", "25c4"}, V{"down","up","up","down"}, "25c2/3/4");
        c.create_figure(name, &col, &mrk);
        c.export_canvas();
    };

    build(&no_threshold, "P_K_newL0_no_threshold_bin");
    build(nullptr,       "P_K_newL0_with_threshold_bin");
    return 0;
}
