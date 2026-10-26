#include "U_utils.cc"

void B_histogramming(std::string selection, bool dry_run = false) {
    auto selected = _selection(selection, "B");
    std::vector<PIDJob> jobs;

    for (auto particle : selected.particles) for (auto alias : selected.datasets) {
        auto sample = _sample(particle, alias);
        for (auto pt : _pts(particle)) {
            auto config = _shape_config(sample, pt);
            auto cache = _stage(sample, "c", pt) + "/" + _name(sample, pt) + "_cache.root";
            // An existing cache directory can still be empty. Check every input before running B.
            if (!dry_run && gSystem->AccessPathName(cache.c_str()))
                throw std::runtime_error("Missing cached tuples: " + cache
                    + "\nRun this first, then wait for caching to finish:\nroot -l -b -q '"
                    + PID_RUN + "/A_cache.C(\"" + (particle == "L0" ? "Lambda0" : "LambdaC")
                    + ":" + sample.parent + ":b\")'");
            PIDJob job;
            job.directory = _stage(sample, "h", pt);
            job.cpus = _cores(config, "number_of_cores", 2);
            job.required = {config, cache};
            // Only histogramming here: fitting reads these reusable ROOT histograms.
            job.command = _python("pidcalib") + " -m src.pidcalib_sweight_fits.apps.histogramming"
                + " --tree DecayTree --cachedir " + _quote(_stage(sample, "c", pt))
                + " --hist-dir " + _quote(job.directory)
                + " --number-of-cores " + std::to_string(job.cpus)
                + " --config " + _quote(config) + " --batch";
            jobs.push_back(job);
        }
    }
    _launch(jobs, false, dry_run);
}
