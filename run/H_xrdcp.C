#include "U_utils.cc"

void H_xrdcp(std::string selection, bool dry_run = false) {
    auto selected = _selection(selection, "H"); // Reject ALL partition selections before any copy.
    std::vector<PIDJob> jobs;

    for (auto particle : selected.particles) for (auto alias : selected.datasets) {
        auto sample = _sample(particle, alias);
        std::string source = _base(sample) + (particle == "L0" ? "/s/c" : "/s");
        auto files = dry_run ? std::vector<std::string>{source + "/001/<input>_sweights.root"}
                             : _assigned_files(sample);
        PIDJob job;
        job.directory = source;
        std::string eos_path = sample.eos.substr(std::string("root://eoslhcb.cern.ch/").size());
        job.command = "xrdfs root://eoslhcb.cern.ch mkdir -p " + _quote(eos_path) + "\n";
        // Flatten only the ROOT artifacts into EOS; never copy execution material.
        job.command += "files=(\n";
        for (auto file : files) { job.command += _quote(file) + "\n"; job.required.push_back(file); }
        job.command += ")\nxrdcp -f --parallel 8 --retry 3 \"${files[@]}\" " + _quote(sample.eos) + "\n"
            + "remote=$(xrdfs root://eoslhcb.cern.ch ls " + _quote(eos_path) + ")\n"
            + "for file in \"${files[@]}\"; do\n"
              "    printf '%s\\n' \"$remote\" | grep -Fx -- " + _quote(eos_path)
            + "\"$(basename \"$file\")\" >/dev/null\ndone";
        jobs.push_back(job);
    }
    _launch(jobs, false, dry_run);
}
