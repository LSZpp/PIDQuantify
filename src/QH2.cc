#include "QH2.hh"

#include "TFile.h"
#include "TH3D.h"

#include <cmath>
#include <stdexcept>
#include <iostream>

std::pair<int, int> QH2::_enclosed_bins(const TAxis *axis, double lo, double hi){
    // A bin i is kept only if its whole [lowEdge, upEdge] lies within [lo, hi].
    // A small relative+absolute tolerance absorbs floating-point edge values
    // (e.g. eta edges stored as doubles, MeV momentum edges of order 1e4).
    const int n = axis->GetNbins();
    int ilo = 0, ihi = -1;   // empty by default
    const double tol_lo = 1e-6 * std::fabs(lo) + 1e-9;
    const double tol_hi = 1e-6 * std::fabs(hi) + 1e-9;
    for (int i = 1; i <= n; ++i){
        const double bl = axis->GetBinLowEdge(i);
        const double bu = axis->GetBinUpEdge(i);
        if (bl >= lo - tol_lo && bu <= hi + tol_hi){
            if (ilo == 0) ilo = i;   // first enclosed (bins are contiguous & ordered)
            ihi = i;                 // last enclosed so far
        }
    }
    if (ilo == 0) return {1, 0};     // none enclosed -> empty range (Integral == 0)
    return {ilo, ihi};
}

QH2::QH2(const std::string &batch,
         const std::string &polarity,
         const std::string &first_particle,
         const std::string &second_particle,
         const std::string &identification_type,
         const double       cut_value,
         const std::string &directory,
         const QRegion     *region,
         const QReweight   *reweight)
        :QH2(batch,
             polarity,
             first_particle,
             second_particle,
             identification_type,
             cut_value,
             QHistogramSource::legacy(directory),
             region,
             reweight){
}

QH2::QH2(const std::string &batch,
         const std::string &polarity,
         const std::string &first_particle,
         const std::string &second_particle,
         const std::string &identification_type,
         const double       cut_value,
         const QHistogramSource &source,
         const QRegion     *region,
         const QReweight   *reweight){
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

        // Per-bin kinematic reweighting (3D): multiply every bin by
        // weight = target_total / source_total before marginalising, so the
        // summed efficiency takes on the target sample's kinematic profile.
        if (reweight && reweight->first && reweight->second){
            const TH3D *src = reweight->first;   // source total (e.g. L0)
            const TH3D *tgt = reweight->second;  // target total (e.g. Lc)
            for (int i = 1; i <= total3->GetNbinsX(); ++i)
            for (int j = 1; j <= total3->GetNbinsY(); ++j)
            for (int k = 1; k <= total3->GetNbinsZ(); ++k){
                const double s = src->GetBinContent(i, j, k);
                const double w = (s != 0.) ? tgt->GetBinContent(i, j, k) / s : 0.;
                total3 ->SetBinContent(i, j, k, w * total3 ->GetBinContent(i, j, k));
                total3 ->SetBinError  (i, j, k, w * total3 ->GetBinError  (i, j, k));
                passed3->SetBinContent(i, j, k, w * passed3->GetBinContent(i, j, k));
                passed3->SetBinError  (i, j, k, w * passed3->GetBinError  (i, j, k));
            }
        }

        // nLongTracks (z): if a region pins it, use the enclosed-bin window
        // (only fully-contained bins); otherwise fall back to the source window.
        bool z_from_region = false;
        if (region){
            auto it = region->find("nLongTracks");
            if (it != region->end()){
                const std::pair<int,int> rz =
                    _enclosed_bins(total3->GetZaxis(), it->second.first, it->second.second);
                total3 ->GetZaxis()->SetRange(rz.first, rz.second);
                passed3->GetZaxis()->SetRange(rz.first, rz.second);
                z_from_region = true;
            }
        }
        if (!z_from_region){
            total3 ->GetZaxis()->SetRangeUser(source.nlongtracks_low(), source.nlongtracks_high());
            passed3->GetZaxis()->SetRangeUser(source.nlongtracks_low(), source.nlongtracks_high());
        }

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

    // Resolve the (P=x, ETA=y) enclosed-bin windows from the region, if any.
    // The nLongTracks (z) restriction was already applied above at marginalisation.
    if (region){
        _ix_lo = 1; _ix_hi = _total->GetNbinsX();
        _iy_lo = 1; _iy_hi = _total->GetNbinsY();
        auto itx = region->find("P");
        if (itx != region->end()){
            const std::pair<int,int> r = _enclosed_bins(_total->GetXaxis(), itx->second.first, itx->second.second);
            _ix_lo = r.first; _ix_hi = r.second;
        }
        auto ity = region->find("ETA");
        if (ity != region->end()){
            const std::pair<int,int> r = _enclosed_bins(_total->GetYaxis(), ity->second.first, ity->second.second);
            _iy_lo = r.first; _iy_hi = r.second;
        }
        _has_region = true;
    }
}

double QH2::sum_total () const{
    return _has_region ? _total ->Integral(_ix_lo, _ix_hi, _iy_lo, _iy_hi) : _total ->Integral();
}
double QH2::sum_passed() const{
    return _has_region ? _passed->Integral(_ix_lo, _ix_hi, _iy_lo, _iy_hi) : _passed->Integral();
}

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
