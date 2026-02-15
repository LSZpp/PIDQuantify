#include "QH2.hh"

#include "TFile.h"

#include <stdexcept>

QH2::QH2(const std::string &batch,
         const std::string &polarity,
         const std::string &first_particle,
         const std::string &second_particle,
         const std::string &identification_type,
         const double       cut_value,
         const std::string &directory){
    // Write the property of the histogram 
    _property = new QProperty(batch,
                              polarity,
                              first_particle,
                              second_particle,
                              identification_type,
                              cut_value,
                              directory);

    // Fill the path of the histogram
    _path = _property->path();

    // Fetch the total and passed histograms
    TFile *file = new TFile(_path.c_str(), "READ");
    if (!file || file->IsZombie()) throw std::runtime_error(("Failed to open file " + _path).c_str());
    TH2D *total = dynamic_cast<TH2D*>(file->Get("total"));
    std::string passing_cut_string = "passing_" + _property->construct_cut_string();
    TH2D *passed = dynamic_cast<TH2D*>(file->Get(passing_cut_string.c_str()));
    if (!total || !passed) throw std::runtime_error(("Missing histograms in file " + _path).c_str());
    _total = dynamic_cast<TH2D*>(total->Clone());
    _passed = dynamic_cast<TH2D*>(passed->Clone());

    file->Close();
    delete file;
}

QH2::~QH2(){
    if (_total)    delete _total;
    if (_passed)   delete _passed; 
    if (_property) delete _property; 
}
