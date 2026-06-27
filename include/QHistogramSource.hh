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
        ProbNNLinear  // linear ProbNN cut grid      (PROBNN_P>(cut/100),     cut = percent 0..100)
    };

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

    static std::string _with_trailing_slash(const std::string &directory);
    static bool _ends_with_path_component(const std::string &path,
                                          const std::string &component);
    static std::string _legacy_dataset(const std::string &batch,
                                       const std::string &probe_particle);
    static std::string _finals_dataset(const std::string &batch,
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
                     const double       nlongtracks_high = 0.);

    static QHistogramSource legacy(const std::string &directory);
    static QHistogramSource finals(const std::string &directory,
                                   const std::string &sample_set,
                                   const CutScheme    cut_scheme = CutScheme::DLL);
    // 3D source: histograms are TH3D and are marginalised over the nLongTracks
    // window [nlongtracks_low, nlongtracks_high] into a TH2D before use.
    static QHistogramSource finals_3d(const std::string &directory,
                                      const std::string &sample_set,
                                      const double       nlongtracks_low,
                                      const double       nlongtracks_high,
                                      const CutScheme    cut_scheme = CutScheme::DLL);

    std::string path(const std::string &batch,
                     const std::string &polarity,
                     const std::string &probe_particle,
                     const std::string &cut_string) const;

    const std::string &directory() const;
    const std::string &sample_set() const;
    NamingMode mode() const;
    CutScheme  cut_scheme() const;
    bool       is_3d() const;
    double     nlongtracks_low() const;
    double     nlongtracks_high() const;
};

#endif
