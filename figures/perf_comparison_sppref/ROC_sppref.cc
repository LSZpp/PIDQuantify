#include "QROCCollection.hh"
#include <unordered_map>

int main(){
    const std::string dir = "/data/lhcb/users/lins/u3_PIDQuantify/histograms_sppref/";

    const std::unordered_map<std::string, Color_t> colours = {
        {"24c1 sppref MAGup", kBlue+1},
        {"24b1 MAGup",        kRed+1}
    };

    auto make_roc = [&](const std::string &p1, const std::string &p2,
                        const std::string &canvas_name){
        QROCCollection *curves = new QROCCollection(p1, p2, -20., 30., .1, dir);
        curves->add_curve("24c1ref", "up", "24c1 sppref MAGup");
        curves->add_curve("24b1",    "up", "24b1 MAGup");
        curves->create_figure(canvas_name, &colours);
        curves->export_canvas();
        delete curves;
    };

    make_roc("P", "K",  "ROC_sppref_P_K" );
    make_roc("P", "Pi", "ROC_sppref_P_Pi");
    make_roc("K", "Pi", "ROC_sppref_K_Pi");

    return 0;
}
