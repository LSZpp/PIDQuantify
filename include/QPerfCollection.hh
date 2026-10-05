#ifndef QPERFCOLLECTION_HH
#define QPERFCOLLECTION_HH


// The QPerfCollection class
// LSZ 17 Feb 26

// A class that allows the user to compare one-dimensional performance figures

#include "QH2Perf.hh" 
#include "QHistogramSource.hh"

#include "TCanvas.h"
#include "TStyle.h"
#include "TColor.h"

#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <utility>

class QPerfCollection{
private:
    // insertion-ordered list of performance figures (name, figure); the draw and
    // legend order follow the order in which add_perf() was called
    std::vector<std::pair<std::string, QH2Perf*>> _perf_figures;

    // the canvas for the figures for the p and eta projections
    TCanvas *_canvas_p   = nullptr;
    TCanvas *_canvas_eta = nullptr;
    
    // simple properties of QPerfCollection
    const std::string _first_particle;
    const std::string _second_particle;
    const double      _cut;
    const QRegion    *_region = nullptr;  // optional phase-space restriction applied
                                          // to every figure in the collection

public:
    QPerfCollection(const std::string &first_particle,
                    const std::string &second_particle, 
                    const double       cut,
                    const QRegion     *region = nullptr);
                                                 // constructor. A region restricts every
                                                 // figure's projections: the eta profile
                                                 // is built only from the momentum bins
                                                 // inside it (and the p profile only from
                                                 // the eta bins inside it), so samples
                                                 // whose histograms cover different
                                                 // momentum ranges stay comparable

    void add_perf(const std::string &batch,
                  const std::string &polarity,
                  const std::string &name,
                  const std::string &directory); // function that adds a performance fig. to the collection

    void add_perf(const std::string &batch,
                  const std::string &polarity,
                  const std::string &name,
                  const QHistogramSource &source); // overload with a histogram source resolver

    void add_perf(const std::vector<std::string> &batches,
                  const std::vector<std::string> &polarities,
                  const std::string &name,
                  const std::string &directory); // function that adds a performance fig. with combined batches
                                                 // to the collection

    void add_perf(const std::vector<std::string> &batches,
                  const std::vector<std::string> &polarities,
                  const std::string &name,
                  const QHistogramSource &source); // overload with a histogram source resolver

    void create_figures(const std::string &canvas_name, 
                        const double min_efficiency_range =  .8,
                        const double max_efficiency_range = 1.05,
                        const std::unordered_map<std::string, Color_t> *colour_map = nullptr,
                        const std::unordered_map<std::string, Style_t> *style_map  = nullptr,
                        const std::unordered_map<std::string, Size_t>  *size_map   = nullptr);
                            // function that creates the figures for p and eta

    void create_figures(const std::string &canvas_name,
                        const double min_efficiency_range_p,
                        const double max_efficiency_range_p,
                        const double min_efficiency_range_eta,
                        const double max_efficiency_range_eta,
                        const std::unordered_map<std::string, Color_t> *colour_map = nullptr,
                        const std::unordered_map<std::string, Style_t> *style_map  = nullptr,
                        const std::unordered_map<std::string, Size_t>  *size_map   = nullptr);
                            // overload giving the p and the eta canvas their own
                            // vertical range: the two projections rarely cover the
                            // same efficiencies, so a single shared range wastes
                            // the axis on whichever projection is the flatter one

    void export_canvases();
                    // function that exports the canvases

    ~QPerfCollection();  // destructor
};


#endif
