

// ROC curves comparing 26c1 and 25c4 (MAGdown) for all particle combinations
// Compile with:
// g++ -O3 script_name.cc -o executable_name $(root-config --cflags --libs) $(PIDQuantify-config)

#include "QROCCollection.hh"

int main(){
    const std::string dir = "/data/lhcb/users/lins/u3_PIDQuantify/histograms_26/";

    // K vs Pi
    {
        QROCCollection *curves = new QROCCollection("K", "Pi", -20., 30., .5, dir);
        curves->add_curve("26c1", "down", "26c1 MAGdown");
        curves->add_curve("25c4", "down", "25c4 MAGdown");
        curves->create_figure("ROC_26c1_v_25c4_K_Pi");
        curves->export_canvas();
        delete curves;
    }

    // P vs K
    {
        QROCCollection *curves = new QROCCollection("P", "K", -20., 30., .5, dir);
        curves->add_curve("26c1", "down", "26c1 MAGdown");
        curves->add_curve("25c4", "down", "25c4 MAGdown");
        curves->create_figure("ROC_26c1_v_25c4_P_K");
        curves->export_canvas();
        delete curves;
    }

    // P vs Pi
    {
        QROCCollection *curves = new QROCCollection("P", "Pi", -20., 30., .5, dir);
        curves->add_curve("26c1", "down", "26c1 MAGdown");
        curves->add_curve("25c4", "down", "25c4 MAGdown");
        curves->create_figure("ROC_26c1_v_25c4_P_Pi");
        curves->export_canvas();
        delete curves;
    }

    return 0;
}
