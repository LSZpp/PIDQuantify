#include "U_utils.cc"

void J_effhists(std::string selection, bool dry_run = false) {
    auto selected = _selection(selection, "J");

    // Edit these few settings for an additional scan. DLL is the normal production.
    std::vector<std::string> dimensions = {"2d", "3d"};
    std::vector<std::string> grids = {"DLL"}; // Also: "ProbNNLog", "ProbNNLinear".
    std::string binning = PID_CALIB + "/bin_scheme_hi_stats_sim.json";
    std::vector<PIDJob> copies, jobs;
    if (selected.batch && !dry_run) _proxy_check();

    for (auto particle : selected.particles) for (auto alias : selected.datasets) {
        auto sample = _sample(particle, alias);
        std::string weights = sample.eos;
        std::string probe_weights = weights;
        if (selected.local) {
            weights = _base(sample) + "/s/local_sweights/";
            auto files = dry_run
                ? std::vector<std::string>{_base(sample) + (particle == "L0" ? "/s/c" : "/s")
                                          + "/001/<input>_sweights.root"}
                : _assigned_files(sample);
            probe_weights = files[0];
            PIDJob copy;
            copy.directory = _base(sample) + "/s";
            copy.environment = "eff";
            // Materialize once BEFORE the two dimension jobs; they can then read concurrently.
            std::string code = "import shutil, tempfile\nfrom pathlib import Path\n"
                "destination = Path(" + _quote(weights) + ")\n"
                "temporary = Path(tempfile.mkdtemp(prefix='local_sweights.', dir=destination.parent))\n"
                "files = [\n";
            for (auto file : files) {
                code += "    " + _quote(file) + ",\n";
                copy.required.push_back(file);
            }
            code += "]\nfor source in files:\n    shutil.copy2(source, temporary / Path(source).name)\n"
                "if destination.exists(): shutil.rmtree(destination)\n"
                "temporary.rename(destination)\n";
            copy.command = _python_code("eff", code);
            copies.push_back(copy);
        }

        for (auto dimension : dimensions) for (auto grid : grids) {
            PIDJob job;
            job.environment = "eff";
            job.cpus = 1;
            job.memory = "8GB";
            job.dataset = sample.dataset;
            job.weights = probe_weights;
            job.directory = PID_DATA + "u3_PIDQuantify/"
                + (selected.local ? "finals_hists_local/" : "finals_hists/")
                + dimension + "/" + (particle == "L0" ? "newL0/" : "Lc/") + alias;
            // Each optional grid is a separate job, so its submission/logs need their own directory.
            if (grid != "DLL") job.directory += "/" + grid;
            std::string samples = job.directory + "/samples.json";
            job.required = {binning, _cache_config(sample, particle == "L0" ? "vh" : "")};

            std::string cuts;
            if (grid == "DLL") {
                bool block4 = sample.parent == "24b4";
                cuts = "for i in range(" + std::string(block4 ? "501" : "201") + "):\n"
                    "    threshold = " + std::string(block4 ? "-20 + i / 10" : "-50 + i / 2") + "\n"
                    "    for label in ['DLLp>', 'DLLp-DLLK>', 'DLLp<', 'DLLp-DLLK<']:\n"
                    "        print(f'{label}{threshold:.1f}')\n";
            } else if (grid == "ProbNNLog" || grid == "ProbNNLinear") {
                cuts = "import math\nfor i in range(" + std::string(grid == "ProbNNLog" ? "301" : "501")
                    + "):\n    threshold = "
                    + (grid == "ProbNNLog" ? "math.exp(-15 + i * 0.05)" : "(i * 0.2) / 100")
                    + "\n    for label in ['PROBNN_P>', 'PROBNN_K>', 'PROBNN_PI>']:\n"
                      "        print(f'{label}{threshold:.10f}')\n";
            } else throw std::runtime_error("Unknown efficiency grid: " + grid);

            std::string magnet = sample.polarity == "Up" ? "up" : "down";
            std::string variables = dimension == "2d" ? "P.ETA" : "P.ETA.nLongTracks";
            std::string prefix = "effhists-" + sample.sample + "-" + magnet + "-" + sample.probe + "-";
            job.command = _samples_command(sample, samples, weights)
                + "mapfile -t cuts < <(\n" + _python_code("eff", cuts) + ")\n"
                + "test \"${#cuts[@]}\" -gt 0\n"
                  "cut_args=()\nfor cut in \"${cuts[@]}\"; do cut_args+=(-i \"$cut\"); done\n"
                + _python("eff") + " -m pidcalib2.make_eff_hists"
                + " -s " + _quote(sample.sample) + " -m " + magnet + " -p " + sample.probe
                + " --samples-file " + _quote(samples) + " -g " + _quote(binning)
                + " -b P -b ETA" + (dimension == "3d" ? " -b nLongTracks" : "")
                + " -o " + _quote(job.directory) + " \"${cut_args[@]}\"\n";
            // Reuse the converter in one Python process; avoid restarting lb-conda for every cut.
            job.command += _python("eff") + " - \"${cuts[@]}\" <<'PID_CONVERT'\n"
                "import sys\nfrom pathlib import Path\n"
                "from pidcalib2.pklhisto2root import convert_pklfile_to_rootfile\n"
                "directory = Path(" + _quote(job.directory) + ")\n"
                "for cut in sys.argv[1:]:\n"
                "    path = directory / (" + _quote(prefix) + " + cut + "
                + _quote("-" + variables + "-bin_scheme_hi_stats_sim.pkl") + ")\n"
                "    convert_pklfile_to_rootfile(str(path))\nPID_CONVERT\n";
            jobs.push_back(job);
        }
    }
    // Make physical copies once; batch preflight then checks the inputs before submission.
    _launch(copies, false, dry_run);
    _launch(jobs, selected.batch, dry_run);
}
