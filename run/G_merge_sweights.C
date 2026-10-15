#include "U_utils.cc"

void G_merge_sweights(std::string selection, bool dry_run = false) {
    auto selected = _selection(selection, "G");
    std::vector<PIDJob> jobs;

    for (auto particle : selected.particles) for (auto alias : selected.datasets) {
        auto sample = _sample(particle, alias);
        if (particle == "Lc") {
            std::cout << "Lc:" << alias << ": already one sWeight file per input; no merge needed.\n";
            continue;
        }
        auto directories = dry_run ? std::vector<std::string>{_base(sample) + "/s/vh/001"}
                                  : _numbered_directories(_base(sample) + "/s/vh");
        if (!dry_run && directories.size() != _files(sample).size())
            throw std::runtime_error("Assignment is incomplete for " + alias);
        if (!dry_run) for (auto pt : _pts(particle)) {
            auto others = _numbered_directories(_stage(sample, "s", pt));
            if (others.size() != directories.size())
                throw std::runtime_error("Incomplete pT assignment: " + _stage(sample, "s", pt));
        }
        for (auto directory : directories) {
            std::string number = gSystem->BaseName(directory.c_str());
            std::string inputs, basename;
            PIDJob job;
            job.directory = _base(sample) + "/s/c/" + number;
            for (auto pt : _pts(particle)) {
                std::string input = _stage(sample, "s", pt) + "/" + number;
                if (!inputs.empty()) inputs += ":";
                inputs += input;
                job.required.push_back(input);
                if (!dry_run) {
                    auto files = _root_files(input);
                    if (files.size() != 1) throw std::runtime_error("Incomplete assignment: " + input);
                    std::string name = gSystem->BaseName(files[0].c_str());
                    if (!basename.empty() && name != basename)
                        throw std::runtime_error("pT streams have different input filenames at " + number);
                    basename = name;
                }
            }
            // A fresh workspace prevents combine_sweights' UPDATE mode accumulating keys.
            job.command = "workspace=$(mktemp -d " + _quote(job.directory + "/merge.XXXXXX") + ")\n"
                + _python("pidcalib") + " -m src.pidcalib_sweight_fits.apps.combine_sweights "
                + _quote(inputs) + " \"$workspace\"\n"
                + _python("pidcalib") + " - \"$workspace\" <<'PID_MERGE_CHECK'\n"
                  "import sys, uproot\nfrom pathlib import Path\n"
                  "files = list(Path(sys.argv[1]).glob('*_sweights.root'))\n"
                  "assert len(files) == 1, 'Expected one merged ROOT file'\n"
                  "with uproot.open(files[0]) as merged:\n"
                  "    for pt in ['VeryHighPT', 'HighPT', 'MidPT', 'LowPT']:\n"
                  "        assert f'L0ToPPi_LL_{pt}/DecayTree' in merged, f'Missing {pt} tree'\n"
                  "PID_MERGE_CHECK\n"
                + "mv -f \"$workspace\"/*_sweights.root " + _quote(job.directory + "/")
                + "\nrmdir \"$workspace\"";
            jobs.push_back(job);
        }
    }
    _launch(jobs, false, dry_run);
}
