// Per-batch ROC curves comparing the three proton samples (old L0, new L0, Lc),
// one figure per 2024/2025 dataset, for both discriminator pairs:
//   p vs K  (DLLp-DLLK)  and  p vs pi (DLLp).
// Each figure has three curves sharing the same mis-ID source (K or Pi).
//
// x-axis: efficiency ( p -> p )      = proton ID efficiency (id_source: oldL0/newL0/Lc, probe P)
// y-axis: efficiency ( X -> p )      = X mis-ID rate        (misid_source: K or Pi, probe X)
//
// Labels / colours match the 1D performance plots (1d_histograms/
// perf_pp_id_comparison.cc). The "Updated L0" (red) curve is drawn with an open
// square marker (25); the other two use the default filled square (21).
//
// Compile + run with ./compile_and_run.sh ROC_curves.cc

#include "QROCCollection.hh"
#include "QHistogramSource.hh"

#include "TAttMarker.h"

#include <string>
#include <vector>
#include <unordered_map>

int main(){
    const std::string DIR = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";

    // Proton ID sources (probe P).
    const QHistogramSource src_old = QHistogramSource::finals(DIR, "oldL0");
    const QHistogramSource src_new = QHistogramSource::finals(DIR, "newL0");
    const QHistogramSource src_lc  = QHistogramSource::finals(DIR, "Lc"   );
    // Mis-ID sources (probe K / Pi).
    const QHistogramSource src_k   = QHistogramSource::finals(DIR, "K" );
    const QHistogramSource src_pi  = QHistogramSource::finals(DIR, "Pi");

    // Labels and colours match the 1D performance plots. The label is BOTH the
    // legend text AND the colour_map / marker_map key.
    const std::string LABEL_OLD = "Preliminary #it{#Lambda}^{0} #rightarrow #it{p#pi}";
    const std::string LABEL_NEW = "Updated #it{#Lambda}^{0} #rightarrow #it{p#pi}";
    const std::string LABEL_LC  = "#it{#Lambda}_{#it{c}} #rightarrow #it{pK#pi}";

    const std::unordered_map<std::string, Color_t> colours = {
        {LABEL_OLD, kGray + 2},
        {LABEL_NEW, kRed  + 1},
        {LABEL_LC,  kBlue + 2},
    };

    // Updated L0 (red) drawn as an open square (25); others keep filled square (21).
    const std::unordered_map<std::string, Style_t> markers = {
        {LABEL_NEW, 25},
    };

    // The 13 batches (same tag/polarity as the per-dataset 2D maps).
    struct DS { std::string tag, pol; };
    const std::vector<DS> data = {
        {"24b1", "up"  }, {"24b2", "up"  }, {"24b3", "up"  }, {"24b5", "up"  },
        {"24b6", "down"}, {"24b7", "down"}, {"24b8", "up"  },
        {"25c1d","down"}, {"25c1u","up"  }, {"25c2", "down"},
        {"25c3", "up"  }, {"25c4u","up"  }, {"25c4d","down"},
    };

    // The two discriminator pairs: second particle + its mis-ID source + name tag.
    struct Pair { std::string second; const QHistogramSource *misid; std::string tag; };
    const std::vector<Pair> pairs = {
        {"K",  &src_k,  "P_K" },
        {"Pi", &src_pi, "P_Pi"},
    };

    for (const auto &p : pairs){
        for (const auto &d : data){
            QROCCollection curves("P", p.second, -50., 50., .5);
            curves.add_curve(d.tag, d.pol, LABEL_OLD, src_old, *p.misid);
            curves.add_curve(d.tag, d.pol, LABEL_NEW, src_new, *p.misid);
            curves.add_curve(d.tag, d.pol, LABEL_LC,  src_lc,  *p.misid);
            curves.create_figure(p.tag + "_" + d.tag + "_" + d.pol, &colours, &markers);
            curves.export_canvas();
        }
    }

    return 0;
}
