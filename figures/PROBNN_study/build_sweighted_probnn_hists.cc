#include "ROOT/TThreadExecutor.hxx"
#include "TFile.h"
#include "TH1D.h"
#include "TNamed.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace {

constexpr int kMomentumBins = 24;  // 5 GeV bins from 0 to 120 GeV.
constexpr double kMomentumMaximum = 120000.;
constexpr int kEtaBins = 25;       // 0.2 bins from 0 to 5.
constexpr double kEtaMaximum = 5.;

enum HistogramIndex { kPProton, kEtaProton, kPKaon, kEtaKaon, kPPion, kEtaPion };

struct Entry {
    std::string particle;
    std::string tuple_file;
    std::string sweight_file;
};

struct Job {
    std::string tuple_file;
    std::optional<Entry> proton;
    std::optional<Entry> kaon;
    std::optional<Entry> pion;
};

struct SortKey {
    double mass = 0.;
    double mass_difference = 0.;
    float momentum = 0.f;
    float eta = 0.f;
    UInt_t fill = 0;
    UInt_t run = 0;

    bool operator<(const SortKey &other) const {
        return std::tie(mass, mass_difference, momentum, eta, fill, run)
             < std::tie(other.mass, other.mass_difference, other.momentum, other.eta,
                        other.fill, other.run);
    }

    bool operator==(const SortKey &other) const {
        return mass == other.mass && mass_difference == other.mass_difference
            && momentum == other.momentum && eta == other.eta
            && fill == other.fill && run == other.run;
    }
};

struct Candidate {
    SortKey key;
    float momentum = 0.f;
    float eta = 0.f;
    Int_t charge = 0;
};

struct Weight {
    Int_t order_index = 0;
    double sweight = 0.;

    bool operator<(const Weight &other) const { return order_index < other.order_index; }
};

// Progress reporting shared by the worker threads.
std::mutex g_report_mutex;
std::atomic<std::size_t> g_jobs_done{0};
std::size_t g_jobs_total = 0;

struct FillReport {
    std::size_t candidates = 0;   // rows in the tuple
    std::size_t missing = 0;      // rows whose sWeight is NaN (outside the fit range)
    std::size_t filled = 0;       // rows entering the histograms (positive charge, finite sWeight)
    double sum_of_weights = 0.;
};

void report(const std::string &label, const FillReport &fill) {
    std::lock_guard<std::mutex> lock(g_report_mutex);
    std::cout << "[" << g_jobs_done.load() << "/" << g_jobs_total << "] " << label
              << ": sWeights applied to " << fill.filled << " of " << fill.candidates
              << " candidates (" << fill.missing << " NaN sWeights dropped), sum of weights "
              << std::fixed << std::setprecision(1) << fill.sum_of_weights
              << std::defaultfloat << std::endl;
}

std::string short_name(const std::string &path) {
    const std::size_t slash = path.find_last_of('/');
    return slash == std::string::npos ? path : path.substr(slash + 1);
}

struct FileResult {
    std::array<std::unique_ptr<TH1D>, 6> histograms;
    std::vector<std::pair<std::string, FillReport>> reports;
    std::string error;

    FileResult() {
        const std::array<const char *, 6> names = {
            "p_P", "p_ETA", "K_P", "K_ETA", "pi_P", "pi_ETA"};
        for (int index = 0; index < 6; ++index) {
            const bool momentum = index % 2 == 0;
            histograms.at(index) = std::make_unique<TH1D>(
                names.at(index), names.at(index), momentum ? kMomentumBins : kEtaBins,
                0., momentum ? kMomentumMaximum : kEtaMaximum);
            histograms.at(index)->SetDirectory(nullptr);
            histograms.at(index)->Sumw2();
        }
    }
};

std::unique_ptr<TFile> open_file(const std::string &path) {
    auto file = std::unique_ptr<TFile>(TFile::Open(path.c_str(), "READ"));
    if (file == nullptr || file->IsZombie()) {
        throw std::runtime_error("Cannot open " + path);
    }
    return file;
}

TTree *get_tree(TFile *file, const std::string &path, const std::string &file_path) {
    auto *tree = dynamic_cast<TTree *>(file->Get(path.c_str()));
    if (tree == nullptr) {
        throw std::runtime_error("Missing tree " + path + " in " + file_path);
    }
    return tree;
}

std::vector<Weight> read_weights(const Entry &entry, const std::string &tree_path) {
    auto file = open_file(entry.sweight_file);
    TTree *tree = get_tree(file.get(), tree_path, entry.sweight_file);
    TTreeReader reader(tree);
    TTreeReaderValue<Double_t> sweight(reader, "sweight");
    TTreeReaderValue<Int_t> order_index(reader, "order_index");

    std::vector<Weight> weights;
    weights.reserve(tree->GetEntries());
    while (reader.Next()) {
        weights.push_back({*order_index, *sweight});
    }
    std::sort(weights.begin(), weights.end());
    return weights;
}

void check_matching(const std::vector<Candidate> &candidates,
                    const std::vector<Weight> &weights, const std::string &label) {
    if (candidates.size() != weights.size()) {
        throw std::runtime_error(label + ": tuple/sWeight entry counts differ ("
                                 + std::to_string(candidates.size()) + " versus "
                                 + std::to_string(weights.size()) + ")");
    }
    for (std::size_t index = 1; index < candidates.size(); ++index) {
        if (candidates.at(index - 1).key == candidates.at(index).key) {
            throw std::runtime_error(label + ": non-unique ordering key; refusing ambiguous "
                                     "sWeight assignment");
        }
    }
}

FillReport fill_histograms(std::vector<Candidate> candidates, const std::vector<Weight> &weights,
                           TH1D *momentum_histogram, TH1D *eta_histogram,
                           const std::string &label) {
    std::stable_sort(candidates.begin(), candidates.end(),
                     [](const Candidate &left, const Candidate &right) {
                         return left.key < right.key;
                     });
    check_matching(candidates, weights, label);
    FillReport fill;
    fill.candidates = candidates.size();
    for (std::size_t index = 0; index < candidates.size(); ++index) {
        const Candidate &candidate = candidates.at(index);
        const double weight = weights.at(index).sweight;
        // Candidates outside the range of the sWeight fit carry a NaN sWeight;
        // PIDCalib2 drops them, and a single NaN Fill would turn a whole bin
        // (content and Sumw2) into NaN.
        if (!std::isfinite(weight)) {
            ++fill.missing;
            continue;
        }
        if (candidate.charge != 1) {
            continue;
        }
        momentum_histogram->Fill(candidate.momentum, weight);
        eta_histogram->Fill(candidate.eta, weight);
        ++fill.filled;
        fill.sum_of_weights += weight;
    }
    return fill;
}

void process_protons(const Entry &entry, FileResult &result) {
    constexpr const char *kTreePath = "LcToPKPi/DecayTree";
    auto file = open_file(entry.tuple_file);
    TTree *tree = get_tree(file.get(), kTreePath, entry.tuple_file);
    TTreeReader reader(tree);
    TTreeReaderValue<Double_t> mass(reader, "Lc_M");
    TTreeReaderValue<Float_t> momentum(reader, "p_P");
    TTreeReaderValue<Float_t> eta(reader, "p_ETA");
    TTreeReaderValue<Int_t> charge(reader, "p_CHARGE");
    TTreeReaderValue<UInt_t> fill(reader, "FillNumber");
    TTreeReaderValue<UInt_t> run(reader, "RUNNUMBER");

    std::vector<Candidate> candidates;
    candidates.reserve(tree->GetEntries());
    while (reader.Next()) {
        candidates.push_back({{*mass, 0., *momentum, *eta, *fill, *run},
                              *momentum, *eta, *charge});
    }
    const auto weights = read_weights(entry, kTreePath);
    const auto proton_fill = fill_histograms(std::move(candidates), weights,
                                             result.histograms.at(kPProton).get(),
                                             result.histograms.at(kEtaProton).get(),
                                             "p: " + entry.tuple_file);
    result.reports.emplace_back("p  " + short_name(entry.tuple_file), proton_fill);
}

void process_dstar(const Entry &kaon, const Entry &pion, FileResult &result) {
    constexpr const char *kTreePath = "DstToD0Pi_D0ToKPi/DecayTree";
    if (kaon.tuple_file != pion.tuple_file) {
        throw std::runtime_error("K and pi manifest entries do not share a tuple file");
    }
    auto file = open_file(kaon.tuple_file);
    TTree *tree = get_tree(file.get(), kTreePath, kaon.tuple_file);
    TTreeReader reader(tree);
    TTreeReaderValue<Double_t> d_mass(reader, "D_M");
    TTreeReaderValue<Double_t> dst_mass(reader, "Dst_M");
    TTreeReaderValue<Float_t> kaon_momentum(reader, "K_P");
    TTreeReaderValue<Float_t> kaon_eta(reader, "K_ETA");
    TTreeReaderValue<Int_t> kaon_charge(reader, "K_CHARGE");
    TTreeReaderValue<Float_t> pion_momentum(reader, "pi_P");
    TTreeReaderValue<Float_t> pion_eta(reader, "pi_ETA");
    TTreeReaderValue<Int_t> pion_charge(reader, "pi_CHARGE");
    TTreeReaderValue<UInt_t> fill(reader, "FillNumber");
    TTreeReaderValue<UInt_t> run(reader, "RUNNUMBER");

    std::vector<Candidate> kaons;
    std::vector<Candidate> pions;
    kaons.reserve(tree->GetEntries());
    pions.reserve(tree->GetEntries());
    while (reader.Next()) {
        const double delta_mass = *dst_mass - *d_mass;
        kaons.push_back({{*d_mass, delta_mass, *kaon_momentum, *kaon_eta, *fill, *run},
                         *kaon_momentum, *kaon_eta, *kaon_charge});
        pions.push_back({{*d_mass, delta_mass, *pion_momentum, *pion_eta, *fill, *run},
                         *pion_momentum, *pion_eta, *pion_charge});
    }
    const auto kaon_weights = read_weights(kaon, kTreePath);
    const auto pion_weights = read_weights(pion, kTreePath);
    const auto kaon_fill = fill_histograms(std::move(kaons), kaon_weights,
                                           result.histograms.at(kPKaon).get(),
                                           result.histograms.at(kEtaKaon).get(),
                                           "K: " + kaon.tuple_file);
    result.reports.emplace_back("K  " + short_name(kaon.tuple_file), kaon_fill);
    const auto pion_fill = fill_histograms(std::move(pions), pion_weights,
                                           result.histograms.at(kPPion).get(),
                                           result.histograms.at(kEtaPion).get(),
                                           "pi: " + pion.tuple_file);
    result.reports.emplace_back("pi " + short_name(pion.tuple_file), pion_fill);
}

std::shared_ptr<FileResult> process_job(const Job &job) {
    auto result = std::make_shared<FileResult>();
    try {
        if (job.proton.has_value()) {
            process_protons(*job.proton, *result);
        }
        if (job.kaon.has_value() || job.pion.has_value()) {
            if (!job.kaon.has_value() || !job.pion.has_value()) {
                throw std::runtime_error("Incomplete K/pi pair for " + job.tuple_file);
            }
            process_dstar(*job.kaon, *job.pion, *result);
        }
    } catch (const std::exception &error) {
        result->error = error.what();
    }
    ++g_jobs_done;
    if (result->error.empty()) {
        for (const auto &item : result->reports) {
            report(item.first, item.second);
        }
    } else {
        std::lock_guard<std::mutex> lock(g_report_mutex);
        std::cerr << "[" << g_jobs_done.load() << "/" << g_jobs_total << "] FAILED "
                  << short_name(job.tuple_file) << ": " << result->error << std::endl;
    }
    return result;
}

std::vector<Job> read_manifest(const std::string &path) {
    std::ifstream input(path);
    if (!input) {
        throw std::runtime_error("Cannot open manifest " + path);
    }
    std::map<std::string, Job> jobs;
    std::string line;
    while (std::getline(input, line)) {
        if (line.empty() || line.front() == '#') {
            continue;
        }
        std::istringstream fields(line);
        Entry entry;
        if (!std::getline(fields, entry.particle, '\t')
            || !std::getline(fields, entry.tuple_file, '\t')
            || !std::getline(fields, entry.sweight_file, '\t')) {
            throw std::runtime_error("Malformed manifest row: " + line);
        }
        Job &job = jobs[entry.tuple_file];
        job.tuple_file = entry.tuple_file;
        if (entry.particle == "P_Lc") {
            job.proton = entry;
        } else if (entry.particle == "K") {
            job.kaon = entry;
        } else if (entry.particle == "Pi") {
            job.pion = entry;
        } else {
            throw std::runtime_error("Unknown manifest particle " + entry.particle);
        }
    }
    std::vector<Job> output;
    output.reserve(jobs.size());
    for (auto &item : jobs) {
        output.push_back(std::move(item.second));
    }
    return output;
}

void write_histograms(const std::vector<std::shared_ptr<FileResult>> &results,
                      const std::string &output_path) {
    const std::string temporary_path = output_path + ".tmp";
    std::unique_ptr<TFile> output(TFile::Open(temporary_path.c_str(), "RECREATE"));
    if (output == nullptr || output->IsZombie()) {
        throw std::runtime_error("Cannot create " + temporary_path);
    }

    const std::array<const char *, 6> names = {
        "p_P", "p_ETA", "K_P", "K_ETA", "pi_P", "pi_ETA"};
    std::array<std::unique_ptr<TH1D>, 6> totals;
    for (int index = 0; index < 6; ++index) {
        const bool momentum = index % 2 == 0;
        totals.at(index) = std::make_unique<TH1D>(
            names.at(index), names.at(index), momentum ? kMomentumBins : kEtaBins,
            0., momentum ? kMomentumMaximum : kEtaMaximum);
        totals.at(index)->Sumw2();
    }
    for (const auto &result : results) {
        for (int index = 0; index < 6; ++index) {
            totals.at(index)->Add(result->histograms.at(index).get());
        }
    }
    const std::array<const char *, 6> titles = {
        "proton P", "proton ETA", "kaon P", "kaon ETA", "pion P", "pion ETA"};
    std::cout << "Merged histograms:" << std::endl;
    for (int index = 0; index < 6; ++index) {
        TH1D *histogram = totals.at(index).get();
        if (!std::isfinite(histogram->Integral())) {
            throw std::runtime_error(std::string("Non-finite bin content in ")
                                     + names.at(index));
        }
        std::cout << "  " << std::setw(10) << titles.at(index) << ": in-range sum of sWeights "
                  << std::fixed << std::setprecision(1)
                  << histogram->Integral(1, histogram->GetNbinsX()) << ", overflow "
                  << histogram->GetBinContent(histogram->GetNbinsX() + 1) << ", underflow "
                  << histogram->GetBinContent(0) << std::defaultfloat << std::endl;
        histogram->Write();
    }
    TNamed selection("selection", "p_CHARGE==1; K_CHARGE==1; pi_CHARGE==1");
    selection.Write();
    TNamed matching("sweight_matching",
                    "tuple sorted by the notebook ordering variables; sWeights sorted by order_index");
    matching.Write();
    output->Close();
    if (gSystem->Rename(temporary_path.c_str(), output_path.c_str()) != 0) {
        throw std::runtime_error("Cannot rename " + temporary_path + " to " + output_path);
    }
}

}  // namespace

int main(int argc, char **argv) try {
    std::string manifest;
    std::string output = "sweighted_probnn_kinematics_25c4_magup_positive.root";
    unsigned long threads = 64;
    for (int argument = 1; argument < argc; ++argument) {
        const std::string option(argv[argument]);
        if (option == "--manifest" && argument + 1 < argc) {
            manifest = argv[++argument];
        } else if (option == "--output" && argument + 1 < argc) {
            output = argv[++argument];
        } else if (option == "--threads" && argument + 1 < argc) {
            const std::string value(argv[++argument]);
            try {
                threads = std::stoul(value);
            } catch (const std::exception &) {
                throw std::runtime_error("--threads expects a positive integer, got '"
                                         + value + "'");
            }
        } else {
            throw std::runtime_error("Usage: build_sweighted_probnn_hists --manifest FILE "
                                     "[--output FILE] [--threads N]");
        }
    }
    if (manifest.empty() || threads == 0) {
        throw std::runtime_error("A manifest and a positive thread count are required");
    }

    ROOT::EnableThreadSafety();
    // Worker-local temporary histograms share their six descriptive names.
    // Never register them in ROOT's global directory, otherwise parallel
    // construction produces "Replacing existing TH1" ownership warnings.
    TH1::AddDirectory(false);
    const auto jobs = read_manifest(manifest);
    if (jobs.empty()) {
        throw std::runtime_error("The manifest " + manifest + " contains no records");
    }
    g_jobs_total = jobs.size();
    std::cout << "Processing " << jobs.size() << " tuple files with " << threads
              << " workers." << std::endl;
    ROOT::TThreadExecutor executor(static_cast<unsigned int>(threads));
    const auto results = executor.Map(process_job, jobs);

    std::size_t failures = 0;
    std::string first_error;
    FillReport grand_total;
    for (const auto &result : results) {
        if (!result->error.empty()) {
            ++failures;
            if (first_error.empty()) {
                first_error = result->error;
            }
            continue;
        }
        for (const auto &item : result->reports) {
            grand_total.candidates += item.second.candidates;
            grand_total.missing += item.second.missing;
            grand_total.filled += item.second.filled;
            grand_total.sum_of_weights += item.second.sum_of_weights;
        }
    }
    if (failures != 0) {
        throw std::runtime_error(std::to_string(failures) + " of " + std::to_string(jobs.size())
                                 + " tuple files failed; first error: " + first_error);
    }

    std::cout << "\nAll " << jobs.size() << " tuple files done: sWeights applied to "
              << grand_total.filled << " of " << grand_total.candidates
              << " candidates (" << grand_total.missing
              << " NaN sWeights dropped, remainder negative charge)." << std::endl;
    write_histograms(results, output);
    std::cout << "Wrote intermediate TH1Ds to " << output << std::endl;
    return 0;
} catch (const std::exception &error) {
    std::cerr << "build_sweighted_probnn_hists: " << error.what() << std::endl;
    return 1;
}
