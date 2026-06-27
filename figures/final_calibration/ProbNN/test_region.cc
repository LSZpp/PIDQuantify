// Sanity check that the QH2 region restriction actually changes the numbers.
// For newL0 (L0_2025_c2) and Lc (Lc_2025_c2), magnet down, at DLLp-DLLK cuts
// {-20, 0, 20}, print sum_total / sum_passed / efficiency:
//   (a) WITH the controlled region applied (enclosed bins)
//   (b) WITH NOTHING applied (full 3D phase space, nLongTracks 0-600, region=null)
// The WITH-region numbers should reproduce the independent uproot region_stats.py
// results exactly (total 7,151,783 newL0 / 105,304 Lc; eff@+20 0.9366 / 0.9541).
//
// Compile + run with ./compile_and_run.sh test_region.cc

#include "QH2.hh"
#include "QHistogramSource.hh"

#include <cstdio>
#include <string>
#include <vector>

int main(){
    const std::string DIR = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/";

    const QRegion region = {
        {"P",           {22000., 26000.}},
        {"ETA",         {2.45,   2.59}},
        {"nLongTracks", {83.,    117.}},
    };

    // 3D source pinned to the region's nLongTracks window for the WITH-region run,
    // and a full-range 3D source (0-600) for the NOTHING-applied run.
    struct S { std::string label, set, ds; };
    const std::vector<S> samples = {
        {"new L0", "newL0", "25c2"},
        {"Lc",     "Lc",    "25c2"},
    };
    const std::vector<double> cuts = {-20., 0., 20.};

    for (const auto &s : samples){
        const QHistogramSource src_full = QHistogramSource::finals_3d(DIR, s.set, 0.,   600.);
        const QHistogramSource src_reg  = QHistogramSource::finals_3d(DIR, s.set, 83.,  117.);
        printf("================ %s (%s, down) ================\n", s.label.c_str(), s.ds.c_str());
        for (double c : cuts){
            QH2 reg (s.ds, "down", "P", "K", "ID", c, src_reg,  &region);
            QH2 full(s.ds, "down", "P", "K", "ID", c, src_full, nullptr);
            double tr = reg.sum_total(),  pr = reg.sum_passed();
            double tf = full.sum_total(), pf = full.sum_passed();
            printf("  DLLp-DLLK > %+5.0f\n", c);
            printf("     region : total=%12.1f  passed=%12.1f  eff=%.4f\n", tr, pr, tr ? pr/tr : 0.);
            printf("     full   : total=%12.1f  passed=%12.1f  eff=%.4f\n", tf, pf, tf ? pf/tf : 0.);
        }
    }
    return 0;
}
