#ifndef PID_PIPELINE_UTILS_HH
#define PID_PIPELINE_UTILS_HH

// Shared settings and small launch tools; implementations are in U_utils.cc.
extern const std::string PID_RUN, PID_FIT, PID_CALIB, PID_DATA, PID_PROXY;

struct PIDSelection {
    std::vector<std::string> particles, datasets;
    bool batch = false, local = false;
};

struct PIDSample {
    std::string particle, alias, parent, polarity, dataset, bucket;
    std::string sample, probe, eos, cut, legacy;
};

struct PIDJob {
    std::string directory, command, environment = "pidcalib";
    int cpus = 1;
    std::string memory, dataset, weights;
    std::vector<std::string> required;
};

std::string _quote(const std::string &value);
std::vector<std::string> _split(const std::string &value, char separator);
std::string _capture(const std::string &command);
PIDSelection _selection(const std::string &text, const std::string &stage);
PIDSample _sample(const std::string &particle, const std::string &alias);
std::vector<std::string> _pts(const std::string &particle);
std::string _base(const PIDSample &sample);
std::string _stage(const PIDSample &sample, const std::string &stage,
                   const std::string &pt = "");
std::string _cache_config(const PIDSample &sample, const std::string &pt);
std::string _shape_config(const PIDSample &sample, const std::string &pt);
std::string _name(const PIDSample &sample, const std::string &pt);
std::string _tree(const PIDSample &sample, const std::string &pt);
std::string _yield_config(const PIDSample &sample, const std::string &pt);
int _cores(const std::string &config, const std::string &key, int fallback);
std::string _environment(const std::string &which);
std::string _python(const std::string &which);
std::string _python_code(const std::string &which, const std::string &code);
void _proxy_check();
std::vector<std::string> _files(const PIDSample &sample);
std::string _number(int index);
std::vector<std::string> _numbered_directories(const std::string &directory);
std::vector<std::string> _root_files(const std::string &directory);
std::vector<std::string> _assigned_files(const PIDSample &sample);
void _check_file(const std::string &path);
void _write(const std::string &path, const std::string &contents);
std::string _submission(const PIDJob &job);
void _preflight(const std::vector<PIDJob> &jobs);
void _condor_submit(const PIDJob &job);
void _launch(const std::vector<PIDJob> &jobs, bool batch, bool dry_run,
             int parallel = 1);
std::string _samples_command(const PIDSample &sample, const std::string &output,
                             const std::string &weights);

#endif
