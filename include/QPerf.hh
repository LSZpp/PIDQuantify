#ifndef QPERF_HH
#define QPERF_HH


// The QPerf class 
// LSZ 15 Feb 25

// A class that contains everything that is needed for a performance histogram

#include "QH2Perf.hh"

#include "TCanvas.h"

#include <string>

class QPerf{
private:
    QH2Perf *_perf_hist_loose_ID     = nullptr;   //    ID histogram for loose cut
    QH2Perf *_perf_hist_strict_ID    = nullptr;   //    ID histogram for strict cut
    QH2Perf *_perf_hist_loose_misID  = nullptr;   // misID histogram for loose cut
    QH2Perf *_perf_hist_strict_misID = nullptr;   // misID histogram for strict cut

    const std::string _batch;               // the batch for the particular performance figure
    const std::string _polarity;            // the magnet polarity
    const std::string _first_particle;      // the particle demonstrated by the performance figure
    const std::string _second_particle;     // the secondary particle used to construct the cut
    const std::string _directory;           // the directory of the efficiency histograms
    
    TCanvas *_canvas_p   = nullptr;  // performance histograms binned in momentum
    TCanvas *_canvas_eta = nullptr;  // performance histograms binned in pseudorapidity

    TCanvas *_create_figure(const std::string &canvas_name,
                            const std::string &projection_direction); // creates a performance figure

public:
    QPerf(const std::string &batch,
          const std::string &polarity,
          const std::string &first_particle,
          const std::string &second_particle,
          const std::string &directory,
          const double       cut_value_loose  = 0.,
          const double       cut_value_strict = 5.);
          // constructor

    void export_canvases(const std::string &name);
                // exports the canvases to .C macros and .pdf files

    ~QPerf();   // destructor
};

#endif
