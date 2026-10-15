#ifndef PID_PIPELINE_UTILS_CC
#define PID_PIPELINE_UTILS_CC
#include "U_utils.hh"

// These macros run in ROOT: its usual C++ and ROOT headers are already loaded.
const std::string PID_RUN = "/home/lins/u3_PIDQuantify/run";
const std::string PID_FIT = "/home/lins/u5_sw_fit";
const std::string PID_CALIB = "/home/lins/u6_PIDCalib2/src";
const std::string PID_DATA = "/data/lhcb/users/lins/";
const std::string PID_PROXY = PID_RUN + "/proxy";

std::string _quote(const std::string &value) {
    std::string result = "'";
    for (char c : value) result += c == '\'' ? "'\\''" : std::string(1, c);
    return result + "'";
}

std::vector<std::string> _split(const std::string &value, char separator) {
    if (value.empty() || value.back() == separator)
        throw std::runtime_error("Empty selection component");
    std::vector<std::string> result;
    std::istringstream stream(value);
    std::string item;
    while (std::getline(stream, item, separator)) {
        if (item.empty()) throw std::runtime_error("Empty selection component");
        result.push_back(item);
    }
    return result;
}

std::string _capture(const std::string &command) {
    int status = 0;
    std::string result = gSystem->GetFromPipe(
        ("/bin/bash -c " + _quote(command)).c_str(), &status).Data();
    if (status) throw std::runtime_error("Command failed: " + command);
    return result;
}

PIDSelection _selection(const std::string &text, const std::string &stage) {
    auto words = _split(text, ':');
    if (words.size() < 2) throw std::runtime_error("Use particle:dataset[:b][:l]");
    PIDSelection selection;
    if (words[0] == "both") selection.particles = {"L0", "Lc"};
    else if (words[0] == "Lambda0" || words[0] == "L0") selection.particles = {"L0"};
    else if (words[0] == "LambdaC" || words[0] == "Lc") selection.particles = {"Lc"};
    else throw std::runtime_error("Use Lambda0, LambdaC, or both");
    for (auto alias : _split(words[1], ',')) {
        if (std::find(selection.datasets.begin(), selection.datasets.end(), alias)
            == selection.datasets.end()) selection.datasets.push_back(alias);
        if (stage == "C" && (alias == "2024" || alias == "2025c234")) continue;
        for (auto particle : selection.particles) _sample(particle, alias);
    }
    for (size_t i = 2; i < words.size(); ++i) {
        if (words[i] == "b" && (stage == "A" || stage == "F" || stage == "J"))
            selection.batch = true;
        else if (words[i] == "l" && stage == "J") selection.local = true;
        else throw std::runtime_error("Unsupported tag for stage " + stage + ": " + words[i]);
    }
    for (auto alias : selection.datasets) {
        if (alias == "24b4p2" || alias == "24b4p3") {
            if (stage == "H") throw std::runtime_error("Partition xrdcp is forbidden: " + alias);
            if (stage == "J" && !selection.local)
                throw std::runtime_error("Partitions require local weights: J_effhists.C(\""
                                         + words[0] + ":" + words[1] + ":l"
                                         + (selection.batch ? ":b" : "") + "\")");
        }
    }
    return selection;
}

PIDSample _sample(const std::string &particle, const std::string &alias) {
    // Alias and polarity are the only per-dataset table; production names follow below.
    const std::map<std::string, std::string> polarities = {
        {"24b1","Up"}, {"24b2","Up"}, {"24b3","Up"}, {"24b4","Down"},
        {"24b5","Up"}, {"24b6","Down"}, {"24b7","Down"}, {"24b8","Up"},
        {"25c1d","Down"}, {"25c1u","Up"}, {"25c2","Down"}, {"25c3","Up"},
        {"25c4u","Up"}, {"25c4d","Down"}, {"26c1d","Down"}, {"26c1u","Up"},
        {"26c2d","Down"}, {"26c2u","Up"}, {"24b4p2","Down"}, {"24b4p3","Down"}
    };
    if (!polarities.count(alias)) throw std::runtime_error("Unknown dataset: " + alias);
    PIDSample s;
    s.particle = particle; s.alias = alias; s.parent = alias;
    s.polarity = polarities.at(alias); s.probe = "P";
    const bool l0 = particle == "L0";
    const bool partition = alias == "24b4p2" || alias == "24b4p3";
    std::string year, dataset;
    if (alias.substr(0, 2) == "24") {
        year = "2024_WithUT";
        dataset = "block" + alias.substr(3, 1);
        s.bucket = l0 ? "L0_2024_2025c1" : "Lc_2024";
        s.sample = particle + "_2024_" + dataset;
        if (alias.substr(0, 4) == "24b4") {
            // Keep the existing L0 Block-4 filenames; Lc has its own sample name.
            if (l0) s.sample = "2024_WithUT_block4";
            if (partition) {
                s.parent = "24b4";
                s.legacy = "block4_partition" + alias.substr(5, 1);
                dataset = s.legacy;
                s.sample += "_partition" + alias.substr(5, 1);
                s.cut = alias == "24b4p2" ? "(FillNumber>=9832) & (FillNumber<=9883)"
                                        : "(FillNumber>=9896) & (FillNumber<=9910)";
            }
        }
        s.dataset = "Mag" + s.polarity + "_" + year + "_" + dataset
                    + (l0 ? "_turboraw" : "_turboonly");
    } else {
        year = alias.substr(0, 2) == "25" ? "2025" : "2026";
        dataset = "s" + alias.substr(0, 4);
        s.bucket = l0 ? (alias.substr(0, 4) == "25c1" ? "L0_2024_2025c1"
                                                                     : "L0_2025c234_2026")
                      : "Lc_2025_2026";
        s.dataset = "Mag" + s.polarity + "_" + year + "_" + dataset;
        s.sample = particle + "_" + year + "_" + alias.substr(2, 2);
        if (year == "2025") s.dataset += l0 ? "_turboonly_primary" : "_turboonly_secondary";
        else {
            s.sample = year + "_" + alias.substr(2, 2) + "_v0";
            if (!l0) s.probe = "P_Lc";
        }
    }
    s.eos = "root://eoslhcb.cern.ch//eos/lhcb/wg/rta/WP4/PIDCalib2_sWeights/"
            + year + "/Mag" + s.polarity + "/" + particle + "/" + dataset + "/";
    return s;
}

std::vector<std::string> _pts(const std::string &particle) {
    return particle == "L0" ? std::vector<std::string>{"vh","h","m","l"}
                            : std::vector<std::string>{""};
}

std::string _base(const PIDSample &s) {
    return PID_DATA + (s.particle == "L0" ? "u1_PID_L0/" : "u2_PID_Lc/") + s.alias;
}

std::string _stage(const PIDSample &s, const std::string &stage, const std::string &pt) {
    auto source = s;
    if (stage == "c") source.alias = source.parent;
    return _base(source) + "/" + stage + (pt.empty() ? "" : "/" + pt);
}

std::string _cache_config(const PIDSample &s, const std::string &pt) {
    return PID_FIT + "/configs/" + s.bucket + "/"
           + (s.particle == "L0" ? "l02ppi_" + pt + "pt" : "lc2pkpi") + "_cache.json";
}

std::string _shape_config(const PIDSample &s, const std::string &pt) {
    std::string directory = PID_FIT + "/configs/" + s.bucket + "/";
    std::string name = _name(s, pt) + "_sweight.json";
    std::vector<std::string> candidates = {directory + s.alias + "_" + name};
    if (!s.legacy.empty()) candidates.push_back(directory + s.legacy + "_" + name);
    candidates.push_back(directory + s.alias.substr(0, 2) + "_" + name);
    candidates.push_back(directory + name);
    for (auto path : candidates) if (!gSystem->AccessPathName(path.c_str())) return path;
    throw std::runtime_error("Missing shape config: " + directory + name);
}

std::string _name(const PIDSample &s, const std::string &pt) {
    return s.particle == "L0" ? "l02ppi_" + pt + "pt" : "lc2pkpi";
}

std::string _tree(const PIDSample &s, const std::string &pt) {
    const std::map<std::string, std::string> trees = {
        {"vh","VeryHighPT"}, {"h","HighPT"}, {"m","MidPT"}, {"l","LowPT"}
    };
    return s.particle == "L0" ? "L0ToPPi_LL_" + trees.at(pt) + "/DecayTree"
                              : "LcToPKPi/DecayTree";
}

std::string _yield_config(const PIDSample &s, const std::string &pt) {
    return _stage(s, "y", pt) + "/" + _name(s, pt) + "_" + s.alias + "_yields.json";
}

int _cores(const std::string &config, const std::string &key, int fallback) {
    int value = std::stoi(_capture("jq -er " + _quote("." + key + " // "
                                 + std::to_string(fallback)) + " " + _quote(config)));
    if (value < 1) throw std::runtime_error("Set a positive " + key + " in " + config);
    return value;
}

std::string _environment(const std::string &which) {
    std::string setup = "set -eo pipefail\n"
        "unset PYTHONHOME PYTHONPATH ROOTSYS LD_LIBRARY_PATH CMAKE_PREFIX_PATH\n"
        "if [[ -z \"${_CONDOR_SCRATCH_DIR:-}\" ]]; then export X509_USER_PROXY=" + _quote(PID_PROXY) + "; fi\n"
        "export X509_USER_PROXY=\"${X509_USER_PROXY:-" + PID_PROXY + "}\"\n"
        "export APD_METADATA_LIFETIME=99999999\n";
    if (which == "Lc") setup +=
        "source /home/lins/.miniconda3/etc/profile.d/conda.sh\n"
        "conda activate pidcalib_Lc\n"
        "export PYTHONPATH=/home/lins/u2_PID_Lc/8_bdt\n";
    else setup += "source /cvmfs/lhcb.cern.ch/lib/LbEnv\n";
    return setup + "cd " + _quote(which == "eff" ? PID_CALIB : PID_FIT) + "\n";
}

std::string _python(const std::string &which) {
    return which == "Lc" ? "python" : "lb-conda pidcalib python";
}

std::string _python_code(const std::string &which, const std::string &code) {
    return _python(which) + " - <<'PID_PYTHON'\n" + code + "\nPID_PYTHON\n";
}

void _proxy_check() {
    std::string command = _environment("pidcalib") +
        "command -v condor_submit >/dev/null\n"
        "voms-proxy-info -file " + _quote(PID_PROXY) + " -all >/dev/null\n"
        "test \"$(voms-proxy-info -file " + _quote(PID_PROXY) + " -timeleft)\" -ge 3600\n"
        "voms-proxy-info -file " + _quote(PID_PROXY) + " -fqan | grep -q '/lhcb/'\n";
    if (gSystem->Exec(("/bin/bash -c " + _quote(command)).c_str()))
        throw std::runtime_error("Batch proxy/Condor check failed. Refresh credentials with:\n"
                                 "root -l -b -q '" + PID_RUN + "/P_proxy.C()'");
}

std::vector<std::string> _files(const PIDSample &s) {
    std::string env = s.particle == "Lc" ? "Lc" : "pidcalib";
    auto output = _capture(_environment(env) + _python_code(env,
        "from src.pidcalib_sweight_fits.common.utils import get_data_files\n"
        "for path in get_data_files(" + _quote(s.dataset) + "): print('PID_FILE=' + str(path))"));
    std::vector<std::string> files;
    std::istringstream stream(output);
    std::string line;
    while (std::getline(stream, line))
        if (line.substr(0, 9) == "PID_FILE=") files.push_back(line.substr(9));
    if (files.empty()) throw std::runtime_error("No input files for " + s.dataset);
    return files;
}

std::string _number(int index) {
    return TString::Format("%03d", index + 1).Data();
}

std::vector<std::string> _numbered_directories(const std::string &directory) {
    std::vector<std::string> result;
    void *handle = gSystem->OpenDirectory(directory.c_str());
    if (!handle) throw std::runtime_error("Missing directory: " + directory);
    while (const char *entry = gSystem->GetDirEntry(handle)) {
        std::string name = entry;
        if (name.size() >= 3 && name.find_first_not_of("0123456789") == std::string::npos)
            result.push_back(directory + "/" + name);
    }
    gSystem->FreeDirectory(handle);
    std::sort(result.begin(), result.end());
    if (result.empty()) throw std::runtime_error("No numbered file directories in " + directory);
    return result;
}

std::vector<std::string> _root_files(const std::string &directory) {
    std::vector<std::string> result;
    void *handle = gSystem->OpenDirectory(directory.c_str());
    if (!handle) throw std::runtime_error("Missing directory: " + directory);
    while (const char *entry = gSystem->GetDirEntry(handle)) {
        std::string name = entry;
        if (name.size() > 14 && name.substr(name.size() - 14) == "_sweights.root")
            result.push_back(directory + "/" + name);
    }
    gSystem->FreeDirectory(handle);
    std::sort(result.begin(), result.end());
    return result;
}

std::vector<std::string> _assigned_files(const PIDSample &s) {
    std::string directory = _base(s) + (s.particle == "L0" ? "/s/c" : "/s");
    std::vector<std::string> result;
    auto inputs = _files(s);
    auto children = _numbered_directories(directory);
    if (children.size() != inputs.size())
        throw std::runtime_error("Assignment is incomplete in " + directory);
    for (size_t i = 0; i < inputs.size(); ++i) {
        std::string child = directory + "/" + _number(i);
        auto files = _root_files(child);
        if (files.size() != 1) throw std::runtime_error("Expected one sWeight ROOT file in " + child);
        std::string expected = gSystem->BaseName(inputs[i].c_str());
        expected = expected.substr(0, expected.size() - 5) + "_sweights.root";
        if (expected != gSystem->BaseName(files[0].c_str()))
            throw std::runtime_error("Assigned filename does not match APD input in " + child);
        result.push_back(files[0]);
    }
    return result;
}

void _check_file(const std::string &path) {
    if (gSystem->AccessPathName(path.c_str())) throw std::runtime_error("Missing input: " + path);
}

void _write(const std::string &path, const std::string &contents) {
    std::ofstream file(path);
    file << contents;
    file.close();
    if (!file) throw std::runtime_error("Cannot write " + path);
}

std::string _submission(const PIDJob &job) {
    std::string text = "Executable = /bin/bash\nArguments = " + job.directory + "/run.sh\n"
        "Initialdir = " + job.directory + "\n"
        "Output = " + job.directory + "/O$(Cluster).txt\n"
        "Error = " + job.directory + "/E$(Cluster).txt\n"
        "Log = " + job.directory + "/L$(Cluster).txt\n"
        "request_cpus = " + std::to_string(job.cpus) + "\n";
    if (!job.memory.empty()) text += "request_memory = " + job.memory + "\n";
    return text + "getenv = True\nshould_transfer_files = NO\n"
        "use_x509userproxy = True\nx509userproxy = " + PID_PROXY + "\nqueue 1\n";
}

void _preflight(const std::vector<PIDJob> &jobs) {
    _proxy_check();
    std::set<std::string> checked;
    for (const auto &job : jobs) {
        for (auto path : job.required) _check_file(path);
        const std::string key = job.environment + ":" + job.dataset;
        if (!checked.insert(key).second) continue;
        std::string imports = job.environment == "eff"
            ? "import ROOT, uproot, pidcalib2.make_eff_hists, pidcalib2.pklhisto2root\n"
            : "import ROOT, src.pidcalib_sweight_fits.apps.cache, src.pidcalib_sweight_fits.apps.assign_sweights\n";
        if (job.environment == "Lc") imports +=
            "import json, pickle\n"
            "from src.pidcalib_sweight_fits.common.utils import resolve_repo_path\n"
            "cache = json.load(open(" + _quote(job.required.at(0)) + "))\n"
            "if cache.get('mva'):\n"
            "    with open(resolve_repo_path(cache['mva']['weights']), 'rb') as handle: pickle.load(handle)\n";
        if (!job.dataset.empty()) imports +=
            "import sys\nsys.path.insert(0, " + _quote(PID_FIT) + ")\n"
            "from src.pidcalib_sweight_fits.common.utils import get_data_files\n"
            "files = get_data_files(" + _quote(job.dataset) + ")\n"
            "assert files, 'Empty APD production'\n"
            "f = ROOT.TFile.Open(str(files[0]))\n"
            "assert f and not f.IsZombie(), 'Remote input access failed'\nf.Close()\n";
        if (!job.weights.empty()) imports +=
            "from pathlib import Path\nimport uproot\n"
            "weights = " + _quote(job.weights) + "\n"
            "if not weights.endswith('.root'):\n"
            "    weights = weights.rstrip('/') + '/' + Path(str(files[0])).stem + '_sweights.root'\n"
            "with uproot.open(weights) as handle: assert len(handle.keys()), 'Empty sWeight file'\n";
        _capture(_environment(job.environment) + _python_code(job.environment, imports));
    }
}

void _condor_submit(const PIDJob &job) {
    std::string command = _environment("pidcalib") + "condor_submit "
                          + _quote(job.directory + "/submission.txt");
    if (gSystem->Exec(("/bin/bash -c " + _quote(command)).c_str()))
        throw std::runtime_error("Condor submission failed in " + job.directory);
}

void _launch(const std::vector<PIDJob> &jobs, bool batch, bool dry_run, int parallel) {
    // First show the full selection. Dry-run never creates production directories.
    for (const auto &job : jobs) {
        std::cout << "\n" << job.directory << "\n" << job.command << std::endl;
        if (batch) std::cout << _submission(job) << std::endl;
    }
    if (dry_run) return;
    if (jobs.empty()) return;
    if (batch) _preflight(jobs);
    for (const auto &job : jobs) {
        for (auto path : job.required) _check_file(path);
        if (gSystem->mkdir(job.directory.c_str(), true) < 0
            && gSystem->AccessPathName(job.directory.c_str()))
            throw std::runtime_error("Cannot create " + job.directory);
        _write(job.directory + "/run.sh", "#!/bin/bash\n" + _environment(job.environment) + job.command + "\n");
        if (batch) _write(job.directory + "/submission.txt", _submission(job));
    }
    if (batch) {
        // Validate EVERY description before submitting the first job.
        for (const auto &job : jobs) {
            std::string ads = std::string(gSystem->TempDirectory()) + "/pid_submit_"
                              + std::to_string(gSystem->GetPid()) + ".ads";
            _capture(_environment("pidcalib") + "condor_submit -dry-run " + _quote(ads)
                     + " " + _quote(job.directory + "/submission.txt"));
            gSystem->Unlink(ads.c_str());
        }
        for (const auto &job : jobs) _condor_submit(job);
        std::cout << "Submitted " << jobs.size() << " single-job clusters. Wait before the next stage.\n";
        return;
    }
    // Small batches of local processes; wait for all and preserve their exit codes.
    for (size_t start = 0; start < jobs.size(); start += parallel) {
        std::string command = "failed=0\npids=()\n";
        for (size_t i = start; i < std::min(jobs.size(), start + parallel); ++i) {
            auto dir = jobs[i].directory;
            command += "(date -Is > " + _quote(dir + "/L.txt") + "\n/bin/bash "
                + _quote(dir + "/run.sh") + " > " + _quote(dir + "/O.txt")
                + " 2> " + _quote(dir + "/E.txt") + "\nstatus=$?\nprintf 'exit=%s\\n' \"$status\" >> "
                + _quote(dir + "/L.txt") + "\nexit $status) &\npids+=($!)\n";
        }
        command += "for pid in \"${pids[@]}\"; do wait \"$pid\" || failed=1; done\nexit $failed\n";
        if (gSystem->Exec(("/bin/bash -c " + _quote(command)).c_str()))
            throw std::runtime_error("Local job failed; see E.txt, O.txt, and L.txt beside its output");
    }
}

std::string _samples_command(const PIDSample &s, const std::string &output,
                             const std::string &weights) {
    // Only the sample definition is new; PIDCalib2 still performs all data processing.
    return _python_code("eff",
        "import json, sys\nfrom pathlib import Path\nsys.path.insert(0, " + _quote(PID_FIT) + ")\n"
        "from src.pidcalib_sweight_fits.common.datasets import run3_pidcalib_datasets\n"
        "production = run3_pidcalib_datasets[" + _quote(s.dataset) + "]\n"
        "cache = json.loads(Path(" + _quote(_cache_config(s, s.particle == "L0" ? "vh" : "")) + ").read_text())\n"
        "entry = dict(calib_files=production['calib_files'], probe_prefix='p',\n"
        "    sweight_dir=" + _quote(weights.back() == '/' ? weights : weights + "/") + ",\n"
        "    ordering_variables=cache['ordering_branches'],\n"
        "    tuple_names={" + _quote(s.probe) + ": "
        + (s.particle == "L0" ? "['L0ToPPi_LL_LowPT', 'L0ToPPi_LL_MidPT', 'L0ToPPi_LL_HighPT', 'L0ToPPi_LL_VeryHighPT']"
                               : "['LcToPKPi']") + "})\n"
        + (s.cut.empty() ? "" : "entry['cuts'] = [" + _quote(s.cut) + "]\n")
        + "Path(" + _quote(output) + ").write_text(json.dumps({"
        + _quote(s.sample + "-Mag" + s.polarity + "-" + s.probe) + ": entry}, indent=4) + '\\n')");
}

#endif
