#include "U_utils.cc"

void E_fit_yields(std::string selection, bool dry_run = false) {
    auto selected = _selection(selection, "E");
    std::vector<PIDJob> jobs;

    for (auto particle : selected.particles) for (auto alias : selected.datasets) {
        auto sample = _sample(particle, alias);
        std::string generator = particle == "L0"
            ? "/home/lins/u1_PID_L0/7_pipeline/make_l0_yield_configs.py"
            : "/home/lins/u2_PID_Lc/7_pipeline/make_lc_yield_configs.py";
        for (auto pt : _pts(particle)) {
            auto config = _yield_config(sample, pt);
            PIDJob job;
            job.directory = _stage(sample, "y", pt);
            job.required = {generator, _shape_config(sample, pt), _stage(sample, "f", pt),
                            _stage(sample, "h", pt)};
            // Reuse the existing generator; only its input/output paths change.
            job.command = _python("pidcalib") + " " + _quote(generator)
                + " --base-config " + _quote(_shape_config(sample, pt))
                + " --fit-dir " + _quote(_stage(sample, "f", pt))
                + " --output " + _quote(config)
                + (particle == "L0" ? " --pt " + pt : "") + "\n"
                + _python("pidcalib") + " -m src.pidcalib_sweight_fits.apps.fit_THists main"
                + " --hist-dir " + _quote(_stage(sample, "h", pt))
                + " --config " + _quote(config) + " --outputdir " + _quote(job.directory) + " --batch";
            jobs.push_back(job);
        }
    }
    _launch(jobs, false, dry_run);
}
