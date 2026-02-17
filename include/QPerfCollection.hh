#ifndef QPERFCOLLECTION_HH
#define QPERFCOLLECTION_HH


// The QPerfCollection class
// LSZ 17 Feb 26

// A class that allows the user to compare one-dimensional performance figures

#include "QH2Perf.hh" 

#include "TCanvas.h"

#include <map>
#include <string> 

class QPerfCollection{
private:
    std::map<std::string, QH2Perf*> _perf_figures;  // the performance figures

    // the canvas for the figures for the p and eta projections
    TCanvas *_canvas_p   = nullptr;
    TCanvas *_canvas_eta = nullptr;
    
    // simple properties of QPerfCollection
    const std::string _first_particle;
    const std::string _second_particle;
    const double      _cut;

public:
    QPerfCollection(const std::string &first_particle,
                    const std::string &second_particle, 
                    const double       cut);
                                                 // constructor

    void add_perf(const std::string &batch,
                  const std::string &polarity, 
                  const std::string &name,
                  const std::string &directory); // function that adds a performance fig. to the collection

    void create_figures(const std::string &canvas_name, 
                        const double min_efficiency_range =  .8,
                        const double max_efficiency_range = 1.05);
                            // function that creates the figures for p and eta

    void export_canvases();
                    // function that exports the canvases

    ~QPerfCollection();  // destructor
};


#endif
