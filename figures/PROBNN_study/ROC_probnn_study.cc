#include "QROCCollection.hh"
#include "QHistogramSource.hh"
#include "QProperty.hh"

#include "TColor.h"
#include "TSystem.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace{

using CS = QHistogramSource::CutScheme;

const std::string BASE_DIR = "/data/lhcb/users/lins/u3_PIDQuantify/PROBNN_study/";
const std::string BATCH = "25c4";
const std::string POLARITY = "up";

std::string probe_particle(const std::string &particle){
    if (particle == "P")  return "P_Lc";
    if (particle == "K")  return "K";
    if (particle == "Pi") return "Pi";
    throw std::runtime_error("Unsupported particle " + particle);
}

std::string probnn_name(const std::string &particle){
    if (particle == "P")  return "PROBNN_P";
    if (particle == "K")  return "PROBNN_K";
    if (particle == "Pi") return "PROBNN_PI";
    throw std::runtime_error("Unsupported particle " + particle);
}

std::string latex(const std::string &particle){
    if (particle == "P")  return "#it{p}";
    if (particle == "K")  return "#it{K}";
    if (particle == "Pi") return "#it{#pi}";
    throw std::runtime_error("Unsupported particle " + particle);
}

QHistogramSource study_source(const std::string &particle,
                              const std::string &fiducial,
                              const CS           cut_scheme){
    const std::string probe = probe_particle(particle);
    return QHistogramSource::probnn_study(BASE_DIR + probe + "/" + fiducial + "/",
                                          probe,
                                          cut_scheme);
}

bool source_file_exists(const std::string &first_particle,
                        const std::string &second_particle,
                        const std::string &identification_type,
                        const double       cut,
                        const QHistogramSource &source){
    const QProperty property(BATCH,
                             POLARITY,
                             first_particle,
                             second_particle,
                             identification_type,
                             cut,
                             source);
    return !gSystem->AccessPathName(property.path().c_str());
}

bool common_continuous_range(const std::string &label,
                             const std::string &first_particle,
                             const std::string &second_particle,
                             const double       loosest_cut,
                             const double       requested_strictest_cut,
                             const double       cut_interval,
                             const QHistogramSource &id_source,
                             const QHistogramSource &misid_source,
                             double &strictest_cut){
    const int requested_points =
        static_cast<int>(std::lround((requested_strictest_cut - loosest_cut) / cut_interval));
    int last_good_point = -1;
    for (int point_index = 0; point_index <= requested_points; ++point_index){
        const double cut = loosest_cut + point_index * cut_interval;
        if (!source_file_exists(first_particle, second_particle, "ID", cut, id_source) ||
            !source_file_exists(first_particle, second_particle, "misID", cut, misid_source)){
            break;
        }
        last_good_point = point_index;
    }

    if (last_good_point < 1){
        std::cerr << "Skipping " << label << ": no continuous ROOT scan from cut "
                  << loosest_cut << "\n";
        return false;
    }

    strictest_cut = loosest_cut + last_good_point * cut_interval;
    if (last_good_point < requested_points){
        std::cerr << "Truncating " << label << " at cut " << strictest_cut
                  << " because the next ROOT file is missing\n";
    }
    return true;
}

void make_curve(const std::string &fiducial,
                const std::string &first_particle,
                const std::string &second_particle){
    const QHistogramSource id_dll  = study_source(first_particle,  fiducial, CS::DLL);
    const QHistogramSource mis_dll = study_source(second_particle, fiducial, CS::DLL);

    const QHistogramSource id_probnn  = study_source(first_particle,  fiducial, CS::ProbNNTanh);
    const QHistogramSource mis_probnn = study_source(second_particle, fiducial, CS::ProbNNTanh);

    const QHistogramSource id_product  = study_source(first_particle,  fiducial, CS::ProbNNTanhNotSecond);
    const QHistogramSource mis_product = study_source(second_particle, fiducial, CS::ProbNNTanhNotSecond);

    const std::string dll_label = "#Delta log #it{L} (" + latex(first_particle) + " #minus " + latex(second_particle) + ")";
    const std::string probnn_label = "#it{p}_{NN} (" + latex(first_particle) + ")";
    const std::string product_label = "#it{p}_{NN} (" + latex(first_particle) + ") (1 - #it{p}_{NN} (" + latex(second_particle) + "))";

    const std::unordered_map<std::string, Color_t> colours = {
        {dll_label,     kRed + 2},
        {probnn_label,  kTeal - 8},
        {product_label, kAzure + 3},
    };
    const std::unordered_map<std::string, Style_t> markers = {
        {dll_label,     1},
        {probnn_label,  1},
        {product_label, 1},
    };

    QROCCollection curves(first_particle, second_particle, -30., 30., .05);
    int added_curves = 0;

    double dll_strictest = 30.;
    if (common_continuous_range(dll_label, first_particle, second_particle,
                                -30., 30., .05, id_dll, mis_dll, dll_strictest)){
        curves.add_curve(BATCH, POLARITY, dll_label, -30., dll_strictest, .05, id_dll, mis_dll);
        added_curves++;
    }

    double probnn_strictest = 7.;
    if (common_continuous_range(probnn_label, first_particle, second_particle,
                                0., 7., .002, id_probnn, mis_probnn, probnn_strictest)){
        curves.add_curve(BATCH, POLARITY, probnn_label, 0., probnn_strictest, .002,
                         id_probnn, mis_probnn);
        added_curves++;
    }

    double product_strictest = 7.;
    if (common_continuous_range(product_label, first_particle, second_particle,
                                0., 7., .002, id_product, mis_product, product_strictest)){
        curves.add_curve(BATCH, POLARITY, product_label, 0., product_strictest, .002,
                         id_product, mis_product);
        added_curves++;
    }

    if (added_curves == 0){
        std::cerr << "No curves available for " << fiducial << " "
                  << first_particle << " -> " << second_particle << "\n";
        return;
    }

    const std::string canvas_name = "probnn_study_25c4_magup_" + fiducial + "_"
                                  + first_particle + "_to_" + second_particle;
    curves.create_figure(canvas_name, &colours, &markers, {0.70, 1.005}, {1.e-3, 1.});
    curves.export_canvas();
}

void usage(const char *program){
    std::cerr << "Usage:\n"
              << "  " << program << "\n"
              << "  " << program << " <positive|positive_leptonveto>\n"
              << "  " << program << " <positive|positive_leptonveto> <P|K|Pi> <P|K|Pi>\n";
}

}

int main(int argc, char **argv){
    if (argc != 1 && argc != 2 && argc != 4){
        usage(argv[0]);
        return 2;
    }

    const std::string fiducial_filter = argc >= 2 ? argv[1] : "";
    const std::string first_filter    = argc == 4 ? argv[2] : "";
    const std::string second_filter   = argc == 4 ? argv[3] : "";

    const std::vector<std::string> fiducials = {"positive", "positive_leptonveto"};
    const std::vector<std::pair<std::string, std::string>> pairs = {
        {"P", "K"},
        {"P", "Pi"},
        {"K", "Pi"}
    };

    int produced = 0;
    for (const std::string &fiducial : fiducials){
        if (!fiducial_filter.empty() && fiducial != fiducial_filter) continue;
        for (const auto &pair : pairs){
            if (!first_filter.empty() && pair.first  != first_filter)  continue;
            if (!second_filter.empty() && pair.second != second_filter) continue;
            std::cout << "Making " << fiducial << " " << pair.first << " -> " << pair.second << "\n";
            make_curve(fiducial, pair.first, pair.second);
            produced++;
        }
    }

    if (produced == 0){
        usage(argv[0]);
        return 2;
    }

    return 0;
}
