#ifndef QHISTOGRAMSOURCE_HH
#define QHISTOGRAMSOURCE_HH

// Describes where PIDCalib2 efficiency histograms live and how their filenames
// are constructed.

#include <string>

class QHistogramSource{
public:
    enum class NamingMode{
        Legacy,
        Finals
    };

    enum class CutScheme{
        DLL,          // linear DLL cut grid (e.g. DLLp>, DLLp-DLLK>)
        ProbNN,       // log-space ProbNN cut grid   (PROBNN_P>exp(cut),      cut = log_e threshold)
        ProbNNLinear, // linear ProbNN cut grid      (PROBNN_P>(cut/100),     cut = percent 0..100)
        ProbNNTanh,   // atanh-space ProbNN grid     (PROBNN_P>tanh(cut),     cut = u)
        ProbNNTanhNotSecond // atanh-space grid      (PROBNN_P*(1-PROBNN_K)>tanh(cut))
    };

    // The atanh grid p = tanh(u), u = 0..7, is dense as p -> 1 but steps by 2e-3
    // as p -> 0, so a ">" scan alone leaves the high-ID-efficiency end of a ROC
    // curve very sparse. The job side also writes the complementary cuts
    // "< (1 - tanh(u))", whose thresholds are dense exactly where the ">" grid is
    // starved. A complement source addresses those files. Because
    //     eff(X > s) == 1 - eff(X < s)     for continuous X, i.e. P(X == s) = 0,
    // the efficiency read from one must be complemented before it can be used as
    // a ">"-cut ROC point; QROCCurve does that via probnn_complement().
    //
    // The identity does fail at s == 0 exactly, where ProbNN has a genuine spike
    // of probability mass. That point belongs to the ">" grid (u = 0) and so is
    // unaffected by any of this.

private:
    std::string _directory;
    std::string _sample_set;
    NamingMode  _mode;
    CutScheme   _cut_scheme;      // which cut-string convention the files use
    std::string _binning_suffix;  // filename binning tag: "P.ETA" (2D) or
                                   // "P.ETA.nLongTracks" (3D)
    bool        _is_3d;           // true => files are TH3D, marginalise to TH2D
    double      _nlongtracks_low; // nLongTracks window used when marginalising a
    double      _nlongtracks_high;// 3D histogram into a TH2D (inclusive range)
    std::string _probe_particle_override; // filename probe particle, if it differs
                                           // from the logical physics particle
    bool        _drop_product_close_paren_in_filename; // PROBNN study ROOT files only
    int         _dll_cut_precision; // decimal places used in DLL cut filenames
    bool        _probnn_complement; // address the "< (1 - tanh(u))" files instead
                                     // of the "> tanh(u)" ones (see note above)

    static std::string _with_trailing_slash(const std::string &directory);
    static bool _ends_with_path_component(const std::string &path,
                                          const std::string &component);
    static std::string _legacy_dataset(const std::string &batch,
                                       const std::string &probe_particle);
    static std::string _finals_dataset(const std::string &batch,
                                       const std::string &probe_particle,
                                       const std::string &sample_set);
    static bool _is_2026_batch(const std::string &batch);
    static std::string _finals_probe_particle(const std::string &batch,
                                              const std::string &probe_particle,
                                              const std::string &sample_set);
    std::string _histogram_directory() const;

public:
    QHistogramSource();
    explicit QHistogramSource(const std::string &directory);
    QHistogramSource(const std::string &directory,
                     const std::string &sample_set,
                     const NamingMode   mode,
                     const CutScheme    cut_scheme      = CutScheme::DLL,
                     const std::string &binning_suffix  = "P.ETA",
                     const bool         is_3d           = false,
                     const double       nlongtracks_low  = 0.,
                     const double       nlongtracks_high = 0.,
                     const std::string &probe_particle_override = "",
                     const bool         drop_product_close_paren_in_filename = false,
                     const int          dll_cut_precision = 1,
                     const bool         probnn_complement = false);

    static QHistogramSource legacy(const std::string &directory);
    static QHistogramSource finals(const std::string &directory,
                                   const std::string &sample_set,
                                   const CutScheme    cut_scheme = CutScheme::DLL);
    static QHistogramSource probnn_study(const std::string &directory,
                                         const std::string &probe_particle,
                                         const CutScheme    cut_scheme = CutScheme::ProbNNTanh,
                                         const bool         probnn_complement = false);
    // 3D source: histograms are TH3D and are marginalised over the nLongTracks
    // window [nlongtracks_low, nlongtracks_high] into a TH2D before use. A
    // degenerate window (high <= low, e.g. the defaults 0., 0.) marginalises
    // over the FULL nLongTracks range, recovering the plain 2d (P, ETA)
    // efficiency — useful when only the 3d histograms exist for a dataset.
    static QHistogramSource finals_3d(const std::string &directory,
                                      const std::string &sample_set,
                                      const double       nlongtracks_low  = 0.,
                                      const double       nlongtracks_high = 0.,
                                      const CutScheme    cut_scheme = CutScheme::DLL);

    std::string path(const std::string &batch,
                     const std::string &polarity,
                     const std::string &probe_particle,
                     const std::string &cut_string) const;
    std::string filename_cut_string(const std::string &cut_string) const;

    const std::string &directory() const;
    const std::string &sample_set() const;
    NamingMode mode() const;
    CutScheme  cut_scheme() const;
    bool       is_3d() const;
    double     nlongtracks_low() const;
    double     nlongtracks_high() const;
    const std::string &probe_particle_override() const;
    int        dll_cut_precision() const;
    bool       probnn_complement() const;
};

#endif
