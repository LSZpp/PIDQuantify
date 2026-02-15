#include "QProperty.hh"

#include <unordered_map>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <sstream>

std::string QProperty::_find_dataset() const{
    // Build a map for the batch to find the correct name for the efficiency histogram
    const std::unordered_map<std::string, std::string> dataset_map = {
        {"24b7", "2024_WithUT_block7_v2"},
        {"24b8", "2024_WithUT_block8_v2"},
        {"25c1", "2025_c1_v0"},
        {"25c2", "2025_c2_v0"}, {"25c3", "2025_c3_v0"},
        {"25c4", "2025_c4_v0"} };

    // Check if the batch in the QHistogramProperty is valid
    std::unordered_map<std::string, std::string>::const_iterator
            dataset_map_iterator = dataset_map.find(_batch);
    if (dataset_map_iterator == dataset_map.end()){
        this->print();
        throw std::runtime_error("Input batch is not found in the list of stored batches");
    } else{
        std::string dataset = dataset_map_iterator->second;
        return dataset;
    }

    return "null_result";
}

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
                    :_batch              (batch),
                     _polarity           (polarity),
                     _first_particle     (first_particle),
                     _second_particle    (second_particle),
                     _identification_type(identification_type),
                     _cut_value          (cut_value),
                     _directory          (directory){
}

void QProperty::print() const{
    std::cerr << std::setw(30) << "batch"               << _batch               << "\n"; 
    std::cerr << std::setw(30) << "polarity"            << _polarity            << "\n"; 
    std::cerr << std::setw(30) << "first particle"      << _first_particle      << "\n"; 
    std::cerr << std::setw(30) << "second particle"     << _second_particle     << "\n"; 
    std::cerr << std::setw(30) << "identification type" << _identification_type << "\n"; 
    std::cerr << std::setw(30) << "cut_value"           << _cut_value           << "\n"; 
    std::cerr << std::setw(30) << "directory"           << _directory           << "\n"; 
}

std::string QProperty::path() const{
    // Find the dataset
    std::string dataset = _find_dataset();

    // Find the probe particle
    std::string probe_particle = _find_probe_particle(); 

    // Construct the cut string
    std::string cut_string = construct_cut_string();

    // Builds the path to the efficiency histogram
    std::string path; 
    path =   _directory
           + "effhists-"
           + dataset + "-"
           + _polarity + "-" 
           + probe_particle + "-"
           + cut_string + "-P.ETA.root"; 

    // Ownership of the pointer on heap is transferred
    return path;
}

QProperty::~QProperty(){}
