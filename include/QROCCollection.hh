#ifndef QROCCOLLECTION_HH
#define QROCCOLLECTION_HH


// The QROCCollection class 
// LSZ 17 Feb 26

// A class that stores many ROC curves with and compares them

#include "QROCCurve.hh"

#include "TCanvas.h"

#include <map>
#include <string>

class QROCCollection{
private:
    std::map<std::string, QROCCurve*> _curves; // the ROC curves
    TCanvas *_canvas = nullptr;                // the canvas for the figure

    // simple properties of QROCCollection
    const std::string _first_particle;
    const std::string _second_particle;
    const double      _loosest_cut;
    const double      _strictest_cut;
    const double      _cut_interval;
    const std::string _directory;

public:
    QROCCollection(const std::string &first_particle,
                   const std::string &second_particle,
                   const double       loosest_cut,
                   const double       strictest_cut,
                   const double       cut_interval,
                   const std::string &directory);   // constructor

    void add_curve(const std::string &batch, 
                   const std::string &polarity, 
                   const std::string &name);    // function that adds a curve to the collection

    void create_figure(const std::string &canvas_name);
                            // function that creates a figure

    void export_canvas();   // function that exports the figure canvas

    ~QROCCollection();      // destructor
};

#endif
