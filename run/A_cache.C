#include "U_utils.cc"

void A_cache(std::string selection, bool dry_run = false) {
    auto selected = _selection(selection, "A");
    std::vector<PIDJob> jobs;
    std::set<std::string> cached;

    for (auto particle : selected.particles) for (auto alias : selected.datasets) {
        auto sample = _sample(particle, alias);
        sample = _sample(particle, sample.parent); // Partitions share the full Block-4 cache.
        if (!cached.insert(particle + ":" + sample.alias).second) continue;

        for (auto pt : _pts(particle)) {
            auto config = _cache_config(sample, pt);
            std::string env = particle == "Lc" ? "Lc" : "pidcalib";
            PIDJob job;
            job.directory = _stage(sample, "c", pt);
            job.environment = env;
            job.cpus = _cores(config, "num_threads", 1);
            job.memory = "128GB";
            job.dataset = sample.dataset;
            job.required = {config};
            job.command = _python(env) + " -m src.pidcalib_sweight_fits.apps.cache"
                + " --dataset " + _quote(sample.dataset)
                + " --cachedir " + _quote(job.directory)
                + " --config " + _quote(config);
            jobs.push_back(job);
        }
    }
    _launch(jobs, selected.batch, dry_run, 4);
}
