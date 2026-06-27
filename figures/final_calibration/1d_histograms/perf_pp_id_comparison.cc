// Final-calibration cross-check: proton -> proton ID efficiency curves,
// comparing the three proton calibration samples (new L0, old L0, Lc) for every
// batch in the skills file, at fixed DLL working points.
//
// For each (batch, discriminator, cut) it overlays the p->p ID efficiency vs
// momentum and vs pseudorapidity for the three samples on one canvas, using the
// "finals" effhists in finals_hists/2d/<set>/ (2D P.ETA, read directly by QH2).
//
// Compile with:
//   g++ -O3 perf_pp_id_comparison.cc -o exe $(root-config --cflags --libs) $(PIDQuantify-config)
// or just ./compile_and_run.sh

#include "QPerfCollection.hh"
#include "QHistogramSource.hh"

#include "TColor.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

int main(){
    const std::string DIR = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";

    // All batches in the skills file, with their fixed polarity (one entry per
    // (batch, polarity) dataset). tag is used in the output figure names.
    struct Dataset { std::string batch, polarity, tag; };
    const std::vector<Dataset> datasets = {
        {"24b1", "up",   "24b1"          },
        {"24b2", "up",   "24b2"          },
        {"24b3", "up",   "24b3"          },
        {"24b5", "up",   "24b5"          },
        {"24b6", "down", "24b6"          },
        {"24b7", "down", "24b7"          },
        {"24b8", "up",   "24b8"          },
        {"25c1", "down", "25c1_magdown"  },
        {"25c1", "up",   "25c1_magup"    },
        {"25c2", "down", "25c2_magdown"  },
        {"25c3", "up",   "25c3_magup"    },
        {"25c4", "up",   "25c4_magup"    },
        {"25c4", "down", "25c4_magdown"  },
    };

    // Proton-ID discriminators: vs kaon -> DLLp-DLLK>cut ; vs pion -> DLLp>cut.
    struct Discriminator { std::string second_particle, tag; };
    const std::vector<Discriminator> discriminators = {
        {"K",  "pK" },
        {"Pi", "pPi"},
    };

    // Working points to draw.
    const std::vector<double> cuts = {5.};

    // The three proton calibration samples, resolved via the finals naming.
    const QHistogramSource newL0_source = QHistogramSource::finals(DIR, "newL0");
    const QHistogramSource oldL0_source = QHistogramSource::finals(DIR, "oldL0");
    const QHistogramSource Lc_source    = QHistogramSource::finals(DIR, "Lc"   );

    // Legend labels: these strings are BOTH the legend text AND the colour_map /
    // add_perf key, so the same constant must be used in both places (otherwise
    // the colour lookup misses and ROOT falls back to default colours).
    const std::string LABEL_OLD = "Preliminary #it{#Lambda}^{0} #rightarrow #it{p#pi}";
    const std::string LABEL_NEW = "Updated #it{#Lambda}^{0} #rightarrow #it{p#pi}";
    const std::string LABEL_LC  = "#it{#Lambda}_{#it{c}} #rightarrow #it{pK#pi}";

    // Fixed colour per sample (curves are drawn / legended in add order below).
    const std::unordered_map<std::string, Color_t> colour_map = {
        {LABEL_OLD, kGray + 2},
        {LABEL_NEW, kRed  + 1},
        {LABEL_LC,  kBlue + 2},
    };

    unsigned int made = 0, skipped = 0;
    for (const Dataset &d : datasets){
        for (const Discriminator &disc : discriminators){
            for (const double cut : cuts){
                const std::string cut_int = (cut == 0.) ? "0" : "5";
                const std::string name = "pp_id_" + d.tag + "_"
                                       + disc.tag + "_gt" + cut_int;
                try{
                    QPerfCollection curves("P", disc.second_particle, cut);
                    curves.add_perf(d.batch, d.polarity, LABEL_OLD, oldL0_source);
                    curves.add_perf(d.batch, d.polarity, LABEL_NEW, newL0_source);
                    curves.add_perf(d.batch, d.polarity, LABEL_LC,  Lc_source   );
                    curves.create_figures(name, .7, 1.1, &colour_map);
                    curves.export_canvases();
                    ++made;
                } catch (const std::exception &e){
                    // A sample/batch whose histograms are not on disk yet (e.g. a
                    // still-running finals job) is skipped rather than aborting.
                    std::cerr << "[skip] " << name << " : " << e.what() << "\n";
                    ++skipped;
                }
            }
        }
    }

    std::cout << "Made " << made << " comparison figures, skipped "
              << skipped << " (missing histograms).\n";
    return 0;
}
