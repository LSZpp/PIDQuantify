

// Creates a figure that compares performances between combined batches
// Compile with
// g++ -O3 script_name.cc -o executable_name $(root-config --cflags --libs) $(PIDQuantify-config)


#include "QPerfCollection.hh"

int main(){
    QPerfCollection *curves = new QPerfCollection("P",
                                                  "K",
                                                  5);

    curves->add_perf(std::vector<std::string>{"24b7", "24b8"},
                     std::vector<std::string>{"down", "up"},
                     "24b7/8",
                     "/data/lhcb/users/lins/u1_PID_L0/26Feb/P/");
    curves->add_perf(std::vector<std::string>{"25c1", "25c1"},
                     std::vector<std::string>{"down", "up"},
                     "25c1",
                     "/data/lhcb/users/lins/u1_PID_L0/26Feb/P/");
    curves->add_perf(std::vector<std::string>{"25c2", "25c3", "25c4", "25c4"},
                     std::vector<std::string>{"down", "up",   "up",   "down"},
                     "25c2/3/4",
                     "/data/lhcb/users/lins/u1_PID_L0/26Feb/P/");

    curves->create_figures("P_K_comparison", .8, 1.05);
    curves->export_canvases();
    delete curves;

    return 0;
}
