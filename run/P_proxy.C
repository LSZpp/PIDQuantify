#include "U_utils.cc"

void P_proxy(bool dry_run = false) {
    // The L0 submission wrapper's clean PEM is also accepted by worker-node VOMS tools.
    std::string command = "set -eo pipefail\n"
        "unset PYTHONHOME PYTHONPATH ROOTSYS LD_LIBRARY_PATH CMAKE_PREFIX_PATH\n"
        "source /cvmfs/lhcb.cern.ch/lib/LbEnv\n"
        "export X509_USER_PROXY=\"/tmp/x509up_u$(id -u)\"\n"
        "kinit shaoze@CERN.CH\nlhcb-proxy-init --valid 167:59\n"
        "clean_proxy=$(mktemp /tmp/pid_proxy.XXXXXX)\n"
        "trap 'rm -f \"$clean_proxy\"' EXIT\n"
        "sed '/-----BEGIN DIRACX-----/,/-----END DIRACX-----/d' \"$X509_USER_PROXY\" > \"$clean_proxy\"\n"
        "chmod 600 \"$clean_proxy\"\nvoms-proxy-info -file \"$clean_proxy\" -all\n"
        "test \"$(voms-proxy-info -file \"$clean_proxy\" -timeleft)\" -ge 3600\n"
        "voms-proxy-info -file \"$clean_proxy\" -fqan | grep -q '/lhcb/'\n"
        "install -m 600 \"$clean_proxy\" " + _quote(PID_PROXY);
    std::cout << command << std::endl;
    if (!dry_run && gSystem->Exec(("/bin/bash -c " + _quote(command)).c_str()))
        throw std::runtime_error("Proxy creation failed; see the authentication output above");
}
