#include "QProperty.hh"

#include <unordered_map>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>

std::string QProperty::_find_probe_particle() const{
    // Finds the probe particle
    if      (_identification_type == "ID")   {return _first_particle; }
    else if (_identification_type == "misID"){return _second_particle;}
    else{
        this->print();
        throw std::runtime_error("Identification type is neither ID nor misID");
    }

    return "null_result";
}

std::string QProperty::construct_cut_string() const{
    // ProbNN scheme: the discriminator characterises the first (ID) particle,
    // so it is PROBNN_<first_particle> regardless of the second particle. The
    // cut value is stored in log space; the threshold written into the filename
    // is exp(cut_value), formatted as a plain double with 10 decimals to match
    // the job-side grid (awk "%.10f" of exp(-15 + 0.05*i)).
    if (_source.cut_scheme() == QHistogramSource::CutScheme::ProbNN){
        std::string discriminator;
        if      (_first_particle == "P" ){discriminator = "PROBNN_P" ;}
        else if (_first_particle == "K" ){discriminator = "PROBNN_K" ;}
        else if (_first_particle == "Pi"){discriminator = "PROBNN_PI";}
        else{
            this->print();
            throw std::runtime_error("ProbNN cut: first particle must be P, K, or Pi");
        }

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(10) << std::exp(_cut_value);
        return discriminator + ">" + oss.str();
    }

    // Construct the map for finding the cut string with different cases
    // Uses the first particle and the second particle to locate the cut string
    const std::unordered_map<std::string, std::string> cut_string_map = {
        {"PK"  , "DLLp-DLLK>"}, 
        {"PPi" , "DLLp>"     }, 
        {"KP"  , "DLLp-DLLK<"}, 
        {"KPi" , "DLLK>"     }, 
        {"PiP" , "DLLp<"     }, 
        {"PiK" , "DLLK<"     }
    };

    // Check if the particle combinations in are valid
    std::unordered_map<std::string, std::string>::const_iterator
            cut_string_map_iterator = cut_string_map.find(_first_particle + _second_particle);

    if (cut_string_map_iterator == cut_string_map.end()){
        this->print();
        throw std::runtime_error("Input particle combinations are not found in the list of stored batches");
    } else{
        std::string cut_variable = cut_string_map_iterator->second;
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << _cut_value;
        std::string cut_value_string = oss.str();
        std::string cut_string = cut_variable + cut_value_string;
        return cut_string;
    }

    return "null_result";
}

QProperty::QProperty(const std::string &batch,
                     const std::string &polarity,
                     const std::string &first_particle,
                     const std::string &second_particle,
                     const std::string &identification_type,
                     const double       cut_value,
                     const std::string &directory)
                    :QProperty(batch,
                               polarity,
                               first_particle,
                               second_particle,
                               identification_type,
                               cut_value,
                               QHistogramSource::legacy(directory)){
}

QProperty::QProperty(const std::string &batch,
                     const std::string &polarity,
                     const std::string &first_particle,
                     const std::string &second_particle,
                     const std::string &identification_type,
                     const double       cut_value,
                     const QHistogramSource &source)
                    :_batch              (batch),
                     _polarity           (polarity),
                     _first_particle     (first_particle),
                     _second_particle    (second_particle),
                     _identification_type(identification_type),
                     _cut_value          (cut_value),
                     _source             (source){
}

void QProperty::print() const{
    std::cerr << std::setw(30) << "batch"               << _batch               << "\n"; 
    std::cerr << std::setw(30) << "polarity"            << _polarity            << "\n"; 
    std::cerr << std::setw(30) << "first particle"      << _first_particle      << "\n"; 
    std::cerr << std::setw(30) << "second particle"     << _second_particle     << "\n"; 
    std::cerr << std::setw(30) << "identification type" << _identification_type << "\n"; 
    std::cerr << std::setw(30) << "cut_value"           << _cut_value           << "\n"; 
    std::cerr << std::setw(30) << "directory"           << _source.directory()  << "\n"; 
    std::cerr << std::setw(30) << "sample set"          << _source.sample_set() << "\n"; 
    std::cerr << std::setw(30) << "naming mode"
              << (_source.mode() == QHistogramSource::NamingMode::Legacy ? "legacy" : "finals")
              << "\n";
}

std::string QProperty::path() const{
    // Find the probe particle
    std::string probe_particle = _find_probe_particle(); 

    // Construct the cut string
    std::string cut_string = construct_cut_string();

    return _source.path(_batch, _polarity, probe_particle, cut_string);
}

QProperty::~QProperty(){}
