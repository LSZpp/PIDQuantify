#include "U_utils.cc"

void F_assign(std::string selection, bool dry_run = false) {
    auto selected = _selection(selection, "F");
    std::vector<PIDJob> jobs;
    if (selected.batch && !dry_run) _proxy_check();

    for (auto particle : selected.particles) for (auto alias : selected.datasets) {
        auto sample = _sample(particle, alias);
        // Dry-run shows one template per stream; actual file counts come from APD, not a stale array.
        std::vector<std::string> files = dry_run ? std::vector<std::string>{"<APD file>"} : _files(sample);
        std::cout << particle << ":" << alias << (dry_run ? ": one job per APD file\n" :
            ": " + std::to_string(files.size()) + " files per stream\n");
        for (auto pt : _pts(particle)) for (size_t i = 0; i < files.size(); ++i) {
            std::string env = particle == "Lc" ? "Lc" : "pidcalib";
            PIDJob job;
            job.directory = _stage(sample, "s", pt) + "/" + _number(i);
            job.environment = env;
            job.cpus = particle == "Lc" ? 2 : 1;
            job.dataset = sample.dataset;
            job.required = {_cache_config(sample, pt), _yield_config(sample, pt),
                            _stage(sample, "y", pt) + "/" + _name(sample, pt) + "_sweights.root"};
            job.command = _python(env) + " -m src.pidcalib_sweight_fits.apps.assign_sweights"
                + " --dataset " + _quote(sample.dataset) + " --tree " + _quote(_tree(sample, pt))
                + " --sweights-file " + _quote(job.required[2])
                + " --output-dir " + _quote(job.directory)
                + " --config-cache " + _quote(job.required[0])
                + " --config-sweight " + _quote(job.required[1])
                + " --starting-index " + std::to_string(i) + " --max-files 1"
                + " --num-threads " + std::to_string(job.cpus)
                + (particle == "Lc" ? " --disable-jit True" : "");
            job.command = "# Input file: " + files[i] + "\n" + job.command;
            jobs.push_back(job);
        }
    }
    _launch(jobs, selected.batch, dry_run, 4);
}
