#ifndef QPERFCOMBO_HH
#define QPERFCOMBO_HH


// The QPerfCombo class
// LSZ 15 Feb 26

// A class that creates, stores and prints out all possible combinations of performance figures

#include "QPerf.hh"

#include <string>
#include <unordered_map>

class QPerfCombo{
private:
    std::unordered_map<std::string, QPerf*>      _figures;   
                            // map between particle combinations and performance figures
    std::unordered_map<std::string, std::string> _figure_names; 
                            // names of the performance figures
    const std::string                            _batch;     // the batch for the performance figure
    const std::string                            _polarity;  // the magnet polarity
    const std::string                            _directory; // directory for the efficiency histograms

public:
    QPerfCombo(const std::string &batch, 
               const std::string &polarity,
               const std::string &directory,
               double             cut_value_loose  = 0.,
               double             cut_value_strict = 5.);
               // constructor

    void export_canvases();

    ~QPerfCombo();  // destructor
};

#endif
