#include "QH2.hh"

#include "TFile.h"
#include "TH3D.h"

#include <stdexcept>
#include <iostream>

QH2::QH2(const std::string &batch,
         const std::string &polarity,
         const std::string &first_particle,
         const std::string &second_particle,
         const std::string &identification_type,
         const double       cut_value,
         const std::string &directory)
        :QH2(batch,
             polarity,
             first_particle,
             second_particle,
             identification_type,
             cut_value,
             QHistogramSource::legacy(directory)){
}

QH2::QH2(const std::string &batch,
         const std::string &polarity,
         const std::string &first_particle,
         const std::string &second_particle,
         const std::string &identification_type,
         const double       cut_value,
         const QHistogramSource &source){
    // Write the property of the histogram 
    _property = new QProperty(batch,
                              polarity,
                              first_particle,
                              second_particle,
                              identification_type,
                              cut_value,
                              source);

    // Fill the path of the histogram
    _path = _property->path();

    // Fetch the total and passed histograms
    TFile *file = new TFile(_path.c_str(), "READ");
    if (!file || file->IsZombie()) throw std::runtime_error(("Failed to open file " + _path).c_str());
    std::string passing_cut_string = "passing_" + _property->construct_cut_string();

    if (source.is_3d()){
        // 3D effhists (P, ETA, nLongTracks): restrict the nLongTracks (z) axis
        // to the requested window and marginalise into a TH2D (X=P, Y=ETA).
        TH3D *total3  = dynamic_cast<TH3D*>(file->Get("total"));
        TH3D *passed3 = dynamic_cast<TH3D*>(file->Get(passing_cut_string.c_str()));
        if (!total3 || !passed3) throw std::runtime_error(("Missing histograms in file " + _path).c_str());

        total3 ->GetZaxis()->SetRangeUser(source.nlongtracks_low(), source.nlongtracks_high());
        passed3->GetZaxis()->SetRangeUser(source.nlongtracks_low(), source.nlongtracks_high());

        TH2D *total2  = dynamic_cast<TH2D*>(total3 ->Project3D("yx"));
        TH2D *passed2 = dynamic_cast<TH2D*>(passed3->Project3D("yx"));
        if (!total2 || !passed2) throw std::runtime_error(("Failed to marginalise 3D histograms in file " + _path).c_str());
        _total  = dynamic_cast<TH2D*>(total2 ->Clone());
        _passed = dynamic_cast<TH2D*>(passed2->Clone());
    } else{
        TH2D *total  = dynamic_cast<TH2D*>(file->Get("total"));
        TH2D *passed = dynamic_cast<TH2D*>(file->Get(passing_cut_string.c_str()));
        if (!total || !passed) throw std::runtime_error(("Missing histograms in file " + _path).c_str());
        _total  = dynamic_cast<TH2D*>(total ->Clone());
        _passed = dynamic_cast<TH2D*>(passed->Clone());
    }

    // Detach _total and _passed from their current directories
    _total ->SetDirectory(nullptr);
    _passed->SetDirectory(nullptr);

    file->Close();
    delete file;
}

double QH2::sum_total () const{return _total->Integral(); }
double QH2::sum_passed() const{return _passed->Integral();}

TH2D *QH2::get_total()  const{return _total; }
TH2D *QH2::get_passed() const{return _passed;}

void QH2::add(const QH2& added_hist){
    _total ->Add(added_hist.get_total() );
    _passed->Add(added_hist.get_passed());
    delete _property;
    _property = nullptr;
    _path.clear();
}

QH2::~QH2(){
    delete _total;
    delete _passed; 
    delete _property; 
}
