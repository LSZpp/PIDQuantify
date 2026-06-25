#ifndef QROCCOLLECTION_HH
#define QROCCOLLECTION_HH


// The QROCCollection class 
// LSZ 17 Feb 26

// A class that stores many ROC curves and allows the user to compare them

#include "QROCCurve.hh"
#include "QHistogramSource.hh"

#include "TCanvas.h"
#include "TColor.h"

#include <map>
#include <string>
#include <unordered_map>

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
    const QHistogramSource _id_source;
    const QHistogramSource _misid_source;
    const bool _has_default_source;

public:
    QROCCollection(const std::string &first_particle,
                   const std::string &second_particle,
                   const double       loosest_cut,
                   const double       strictest_cut,
                   const double       cut_interval);   // constructor for per-curve sources

    QROCCollection(const std::string &first_particle,
                   const std::string &second_particle,
                   const double       loosest_cut,
                   const double       strictest_cut,
                   const double       cut_interval,
                   const std::string &directory);   // constructor

    QROCCollection(const std::string &first_particle,
                   const std::string &second_particle,
                   const double       loosest_cut,
                   const double       strictest_cut,
                   const double       cut_interval,
                   const QHistogramSource &source);   // constructor overload with a shared source

    QROCCollection(const std::string &first_particle,
                   const std::string &second_particle,
                   const double       loosest_cut,
                   const double       strictest_cut,
                   const double       cut_interval,
                   const QHistogramSource &id_source,
                   const QHistogramSource &misid_source);   // constructor overload with split sources

    void add_curve(const std::string &batch, 
                   const std::string &polarity, 
                   const std::string &name);    // function that adds a curve to the collection

    void add_curve(const std::string &batch,
                   const std::string &polarity,
                   const std::string &name,
                   const QHistogramSource &source);    // overload with a shared source

    void add_curve(const std::string &batch,
                   const std::string &polarity,
                   const std::string &name,
                   const QHistogramSource &id_source,
                   const QHistogramSource &misid_source);    // overload with split sources

    void add_curve(const std::vector<std::string> &batches,
                   const std::vector<std::string> &polarities, 
                   const std::string &name);    // function that adds an curve with combined batches
                                                // to the collection

    void add_curve(const std::vector<std::string> &batches,
                   const std::vector<std::string> &polarities,
                   const std::string &name,
                   const QHistogramSource &source);    // overload with a shared source

    void add_curve(const std::vector<std::string> &batches,
                   const std::vector<std::string> &polarities,
                   const std::string &name,
                   const QHistogramSource &id_source,
                   const QHistogramSource &misid_source);    // overload with split sources

    void create_figure(const std::string &canvas_name,
                       const std::unordered_map<std::string, Color_t> *colour_map = nullptr);
                            // function that creates a figure

    void export_canvas();   // function that exports the figure canvas

    ~QROCCollection();      // destructor
};

#endif
