#include "U_utils.cc"

void D_fit_data(std::string selection, bool dry_run = false) {
    auto selected = _selection(selection, "D");
    std::vector<PIDJob> jobs;

    for (auto particle : selected.particles) for (auto alias : selected.datasets) {
        auto sample = _sample(particle, alias);
        for (auto pt : _pts(particle)) {
            auto config = _shape_config(sample, pt);
            PIDJob job;
            job.directory = _stage(sample, "f", pt);
            job.required = {config, _stage(sample, "h", pt)};
            // fit_THists launches its existing charge/bin workers and combines their tables.
            job.command = _python("pidcalib") + " -m src.pidcalib_sweight_fits.apps.fit_THists main"
                + " --hist-dir " + _quote(_stage(sample, "h", pt))
                + " --config " + _quote(config) + " --outputdir " + _quote(job.directory) + " --batch";
            jobs.push_back(job);
        }
    }
    _launch(jobs, false, dry_run);
}
