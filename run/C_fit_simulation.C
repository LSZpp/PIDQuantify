#include "U_utils.cc"

void C_fit_simulation(std::string selection, bool dry_run = false) {
    auto selected = _selection(selection, "C");
    std::vector<PIDJob> jobs;
    std::set<std::string> fitted;

    for (auto particle : selected.particles) for (auto alias : selected.datasets) {
        std::string bucket = alias;
        if (alias != "2024" && alias != "2025c234") {
            auto sample = _sample(particle, alias);
            bucket = sample.bucket == "L0_2024_2025c1" || sample.bucket == "Lc_2024"
                     ? "2024" : "2025c234";
        }
        if (!fitted.insert(particle + ":" + bucket).second) continue;
        bool l0 = particle == "L0";
        std::string input_base = l0
            ? PID_DATA + "u1_PID_L0/sim/May26/analysis/combined_truthmatched_split3"
            : PID_DATA + "u2_PID_Lc/sim/combined/split3";
        std::string work = l0 ? PID_DATA + "u1_PID_L0/sim/May26/analysis/sweight_sim"
                              : PID_DATA + "u2_PID_Lc/sim/sweight_sim";

        for (auto pt : _pts(particle)) {
            auto sample = _sample(particle, "24b4"); // Only used to resolve the tree name.
            std::string name = l0 ? "l02ppi_" + pt + "pt" : "lc2pkpi";
            std::string input = input_base + (bucket == "2024" ? "/total_2024" : "/total_2025_c234")
                                + (l0 ? "_" + pt + "pt" : "") + ".root";
            std::string config = PID_FIT + "/configs/" + particle + "_" + bucket + "MC/"
                                 + name + "_sweight.json";
            std::string cachedir = work + "/input/" + bucket + (l0 ? "/" + pt + "pt" : "");
            PIDJob job;
            job.directory = work + "/fit/" + bucket + (l0 ? "/" + pt + "pt" : "");
            job.environment = l0 ? "pidcalib" : "Lc";
            job.cpus = _cores(config, "number_of_cores", 8);
            job.required = {input, config};
            // The small MC sample retains the original combined histogram + fit path.
            job.command = "mkdir -p " + _quote(cachedir) + "\nln -sfn " + _quote(input)
                + " " + _quote(cachedir + "/input.root") + "\n"
                + _python(job.environment) + " -m src.pidcalib_sweight_fits.apps.sweight"
                + " --tree " + _quote(_tree(sample, pt)) + " --cachedir " + _quote(cachedir)
                + " --outputdir " + _quote(job.directory) + " --config " + _quote(config)
                + " --batch --number-of-cores " + std::to_string(job.cpus);
            jobs.push_back(job);
        }
    }
    _launch(jobs, false, dry_run);
}
