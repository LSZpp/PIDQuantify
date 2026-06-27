// Per-batch K vs pi ROC curve, one figure per 2024/2025 dataset. A single curve
// (kaon ID efficiency vs pion mis-ID), drawn red with the default solid square
// marker (21). Discriminator: DLLK, scanned -50 to 50 in steps of 0.5.
//
// x-axis: efficiency ( K -> K )   = kaon ID efficiency (id_source: K, probe K)
// y-axis: efficiency ( pi -> K )  = pion mis-ID rate   (misid_source: Pi, probe Pi)
//
// Compile + run with ./compile_and_run.sh ROC_curves_K_Pi.cc

#include "QROCCollection.hh"
#include "QHistogramSource.hh"

#include <string>
#include <vector>
#include <unordered_map>

int main(){
    const std::string DIR = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";

    const QHistogramSource src_k  = QHistogramSource::finals(DIR, "K" );  // kaon ID, probe K
    const QHistogramSource src_pi = QHistogramSource::finals(DIR, "Pi");  // pion mis-ID, probe Pi

    // Single curve, red. Default marker (solid square 21) so no marker_map.
    const std::string LABEL = "#it{K} #rightarrow #it{#pi}";
    const std::unordered_map<std::string, Color_t> colours = {
        {LABEL, kRed + 1},
    };

    // The 13 batches (same tag/polarity as the per-dataset 2D maps).
    struct DS { std::string tag, pol; };
    const std::vector<DS> data = {
        {"24b1", "up"  }, {"24b2", "up"  }, {"24b3", "up"  }, {"24b5", "up"  },
        {"24b6", "down"}, {"24b7", "down"}, {"24b8", "up"  },
        {"25c1d","down"}, {"25c1u","up"  }, {"25c2", "down"},
        {"25c3", "up"  }, {"25c4u","up"  }, {"25c4d","down"},
    };

    for (const auto &d : data){
        QROCCollection curves("K", "Pi", -50., 50., .5);
        curves.add_curve(d.tag, d.pol, LABEL, src_k, src_pi);
        curves.create_figure("K_Pi_" + d.tag + "_" + d.pol, &colours);
        curves.export_canvas();
    }

    return 0;
}
