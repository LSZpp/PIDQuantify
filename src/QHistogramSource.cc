#include "QHistogramSource.hh"

#include <stdexcept>
#include <unordered_map>

std::string QHistogramSource::_with_trailing_slash(const std::string &directory){
    if (directory.empty() || directory.back() == '/') return directory;
    return directory + "/";
}

bool QHistogramSource::_ends_with_path_component(const std::string &path,
                                                 const std::string &component){
    if (component.empty()) return false;

    std::string trimmed_path = path;
    while (!trimmed_path.empty() && trimmed_path.back() == '/'){
        trimmed_path.pop_back();
    }

    const size_t separator_position = trimmed_path.find_last_of('/');
    const std::string last_component = (separator_position == std::string::npos)
                                     ? trimmed_path
                                     : trimmed_path.substr(separator_position + 1);
    return last_component == component;
}

std::string QHistogramSource::_legacy_dataset(const std::string &batch,
                                              const std::string &probe_particle){
    const std::unordered_map<std::string, std::string> dataset_map_proton = {
        {"24c1ref", "2024_WithUT_c1_sppref_v0"},
        {"24b1",    "2024_WithUT_block1_v2"   },
        {"24b2",    "2024_WithUT_block2_v2"   },
        {"24b3",    "2024_WithUT_block3_v2"   },
        {"24b5",    "2024_WithUT_block5_v2"   },
        {"24b6",    "2024_WithUT_block6_v2"   },
        {"24b7",    "2024_WithUT_block7_v2"   },
        {"24b8",    "2024_WithUT_block8_v2"   },
        {"25c1",    "2025_c1_v0"              },
        {"25c1d",   "2025_c1_v0"              },
        {"25c1u",   "2025_c1_v0"              },
        {"25c2",    "2025_c2_v0"              },
        {"25c3",    "2025_c3_v0"              },
        {"25c4",    "2025_c4_v0"              },
        {"25c4u",   "2025_c4_v0"              },
        {"25c4d",   "2025_c4_v0"              },
        {"26c1",    "2026_c1_v0"              },
        {"24b7_secondary", "24b7d_o"},
        {"24b8_secondary", "24b8u_o"},
        {"25c1_secondary", "2025_c1_secondary_v0"},
        {"25c2_secondary", "2025_c2_secondary_v0"},
        {"25c3_secondary", "2025_c3_secondary_v0"},
        {"25c4_secondary", "2025_c4_secondary_v0"},
    };

    const std::unordered_map<std::string, std::string> dataset_map_kaon_pion = {
        {"24c1ref", "2024_WithUT_c1_sppref_v0"},
        {"24b1",    "2024_WithUT_block1_v2"   },
        {"24b2",    "2024_WithUT_block2_v2"   },
        {"24b3",    "2024_WithUT_block3_v2"   },
        {"24b5",    "2024_WithUT_block5_v2"   },
        {"24b6",    "2024_WithUT_block6_v2"   },
        {"24b7",    "2024_WithUT_block7_v2"   },
        {"24b8",    "2024_WithUT_block8_v2"   },
        {"25c1",    "2025_c1_v0"              },
        {"25c1d",   "2025_c1_v0"              },
        {"25c1u",   "2025_c1_v0"              },
        {"25c2",    "2025_c2_v0"              },
        {"25c3",    "2025_c3_v0"              },
        {"25c4",    "2025_c4_v0"              },
        {"25c4u",   "2025_c4_v0"              },
        {"25c4d",   "2025_c4_v0"              },
        {"26c1",    "2026_c1_v0"              },
        {"24b7_secondary", "2024_WithUT_block7_v2"},
        {"24b8_secondary", "2024_WithUT_block8_v2"},
        {"25c1_secondary", "2025_c1_v0"},
        {"25c2_secondary", "2025_c2_v0"},
        {"25c3_secondary", "2025_c3_v0"},
        {"25c4_secondary", "2025_c4_v0"},
    };

    const std::unordered_map<std::string, std::string> *dataset_map = nullptr;
    if (probe_particle == "P"){
        dataset_map = &dataset_map_proton;
    } else if (probe_particle == "K" || probe_particle == "Pi"){
        dataset_map = &dataset_map_kaon_pion;
    } else{
        throw std::runtime_error("Probe particle not within P, K, or Pi");
    }

    const auto dataset_map_iterator = dataset_map->find(batch);
    if (dataset_map_iterator == dataset_map->end()){
        throw std::runtime_error("Input batch is not found in the list of stored batches");
    }

    return dataset_map_iterator->second;
}

std::string QHistogramSource::_finals_dataset(const std::string &batch,
                                              const std::string &probe_particle,
                                              const std::string &sample_set){
    const std::unordered_map<std::string, std::string> finals_batch_map = {
        {"24b1",  "2024_block1"},
        {"24b2",  "2024_block2"},
        {"24b3",  "2024_block3"},
        {"24b5",  "2024_block5"},
        {"24b6",  "2024_block6"},
        {"24b7",  "2024_block7"},
        {"24b8",  "2024_block8"},
        {"25c1",  "2025_c1"   },
        {"25c1d", "2025_c1"   },
        {"25c1u", "2025_c1"   },
        {"25c2",  "2025_c2"   },
        {"25c3",  "2025_c3"   },
        {"25c4",  "2025_c4"   },
        {"25c4u", "2025_c4"   },
        {"25c4d", "2025_c4"   },
    };

    const auto finals_batch_iterator = finals_batch_map.find(batch);
    if (finals_batch_iterator == finals_batch_map.end()){
        throw std::runtime_error("Input batch is not found in the finals batch map");
    }

    if (sample_set == "newL0"){
        if (probe_particle != "P") throw std::runtime_error("Finals newL0 histograms are proton-only");
        return "L0_" + finals_batch_iterator->second;
    }

    if (sample_set == "Lc"){
        if (probe_particle != "P") throw std::runtime_error("Finals Lc histograms are proton-only");
        return "Lc_" + finals_batch_iterator->second;
    }

    if (sample_set == "oldL0"){
        if (probe_particle != "P") throw std::runtime_error("Finals oldL0 histograms are proton-only");
        return _legacy_dataset(batch, probe_particle);
    }

    if (sample_set == "K"){
        if (probe_particle != "K") throw std::runtime_error("Finals K histograms require probe particle K");
        return _legacy_dataset(batch, probe_particle);
    }

    if (sample_set == "Pi"){
        if (probe_particle != "Pi") throw std::runtime_error("Finals Pi histograms require probe particle Pi");
        return _legacy_dataset(batch, probe_particle);
    }

    throw std::runtime_error("Unknown finals histogram sample set");
}

std::string QHistogramSource::_histogram_directory() const{
    std::string directory = _with_trailing_slash(_directory);

    if (_mode == NamingMode::Finals){
        if (_sample_set.empty()){
            throw std::runtime_error("Finals histogram source requires a sample set");
        }
        if (!_ends_with_path_component(directory, _sample_set)){
            directory += _sample_set + "/";
        }
    }

    return directory;
}

QHistogramSource::QHistogramSource()
                :_directory(""),
                 _sample_set(""),
                 _mode(NamingMode::Legacy),
                 _cut_scheme(CutScheme::DLL),
                 _binning_suffix("P.ETA"),
                 _is_3d(false),
                 _nlongtracks_low(0.),
                 _nlongtracks_high(0.),
                 _probe_particle_override(""),
                 _drop_product_close_paren_in_filename(false),
                 _dll_cut_precision(1){
}

QHistogramSource::QHistogramSource(const std::string &directory)
                :_directory(directory),
                 _sample_set(""),
                 _mode(NamingMode::Legacy),
                 _cut_scheme(CutScheme::DLL),
                 _binning_suffix("P.ETA"),
                 _is_3d(false),
                 _nlongtracks_low(0.),
                 _nlongtracks_high(0.),
                 _probe_particle_override(""),
                 _drop_product_close_paren_in_filename(false),
                 _dll_cut_precision(1){
}

QHistogramSource::QHistogramSource(const std::string &directory,
                                   const std::string &sample_set,
                                   const NamingMode   mode,
                                   const CutScheme    cut_scheme,
                                   const std::string &binning_suffix,
                                   const bool         is_3d,
                                   const double       nlongtracks_low,
                                   const double       nlongtracks_high,
                                   const std::string &probe_particle_override,
                                   const bool         drop_product_close_paren_in_filename,
                                   const int          dll_cut_precision)
                :_directory(directory),
                 _sample_set(sample_set),
                 _mode(mode),
                 _cut_scheme(cut_scheme),
                 _binning_suffix(binning_suffix),
                 _is_3d(is_3d),
                 _nlongtracks_low(nlongtracks_low),
                 _nlongtracks_high(nlongtracks_high),
                 _probe_particle_override(probe_particle_override),
                 _drop_product_close_paren_in_filename(drop_product_close_paren_in_filename),
                 _dll_cut_precision(dll_cut_precision){
}

QHistogramSource QHistogramSource::legacy(const std::string &directory){
    return QHistogramSource(directory);
}

QHistogramSource QHistogramSource::finals(const std::string &directory,
                                          const std::string &sample_set,
                                          const CutScheme    cut_scheme){
    return QHistogramSource(directory, sample_set, NamingMode::Finals,
                            cut_scheme, "P.ETA", false, 0., 0.);
}

QHistogramSource QHistogramSource::probnn_study(const std::string &directory,
                                                const std::string &probe_particle,
                                                const CutScheme    cut_scheme){
    return QHistogramSource(directory, "", NamingMode::Legacy,
                            cut_scheme, "P.ETA-binning", false, 0., 0.,
                            probe_particle, true, 2);
}

QHistogramSource QHistogramSource::finals_3d(const std::string &directory,
                                             const std::string &sample_set,
                                             const double       nlongtracks_low,
                                             const double       nlongtracks_high,
                                             const CutScheme    cut_scheme){
    return QHistogramSource(directory, sample_set, NamingMode::Finals,
                            cut_scheme, "P.ETA.nLongTracks", true,
                            nlongtracks_low, nlongtracks_high);
}

std::string QHistogramSource::path(const std::string &batch,
                                   const std::string &polarity,
                                   const std::string &probe_particle,
                                   const std::string &cut_string) const{
    const std::string dataset = (_mode == NamingMode::Legacy)
                              ? _legacy_dataset(batch, probe_particle)
                              : _finals_dataset(batch, probe_particle, _sample_set);
    const std::string filename_probe_particle = _probe_particle_override.empty()
                                              ? probe_particle
                                              : _probe_particle_override;

    return   _histogram_directory()
           + "effhists-"
           + dataset + "-"
           + polarity + "-"
           + filename_probe_particle + "-"
           + filename_cut_string(cut_string) + "-"
           + _binning_suffix + ".root";
}

std::string QHistogramSource::filename_cut_string(const std::string &cut_string) const{
    if (!_drop_product_close_paren_in_filename) return cut_string;

    std::string filename_cut = cut_string;
    const size_t greater_position = filename_cut.find('>');
    const size_t less_position    = filename_cut.find('<');
    const size_t operator_position = (greater_position == std::string::npos)
                                   ? less_position
                                   : greater_position;
    if (operator_position != std::string::npos &&
        operator_position > 0 &&
        filename_cut[operator_position - 1] == ')' &&
        filename_cut.find("*(1-PROBNN_") != std::string::npos){
        filename_cut.erase(operator_position - 1, 1);
    }
    return filename_cut;
}

const std::string &QHistogramSource::directory() const{return _directory;}
const std::string &QHistogramSource::sample_set() const{return _sample_set;}
QHistogramSource::NamingMode QHistogramSource::mode() const{return _mode;}
QHistogramSource::CutScheme QHistogramSource::cut_scheme() const{return _cut_scheme;}
bool   QHistogramSource::is_3d() const{return _is_3d;}
double QHistogramSource::nlongtracks_low()  const{return _nlongtracks_low; }
double QHistogramSource::nlongtracks_high() const{return _nlongtracks_high;}
const std::string &QHistogramSource::probe_particle_override() const{return _probe_particle_override;}
int QHistogramSource::dll_cut_precision() const{return _dll_cut_precision;}
