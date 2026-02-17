

// Creates a figure that compares performances between different batches
// Compile with 
// g++ -O3 script_name.cc -o executable_name $(root-config --cflags --libs) $(PIDQuantify-config)


#include "QPerfCollection.hh"

int main(){
    QPerfCollection *curves = new QPerfCollection("P",
                                                  "K",
                                                  5);

    curves->add_perf("24b8", "up",   "24b8 MAGup",   "/data/lhcb/users/lins/u1_PID_L0/26Feb/p/");
    curves->add_perf("25c1", "up",   "25c1 MAGup",   "/data/lhcb/users/lins/u1_PID_L0/26Feb/p/");
    curves->add_perf("25c2", "down", "25c2 MAGdown", "/data/lhcb/users/lins/u1_PID_L0/26Feb/p/");
    curves->add_perf("25c3", "up",   "25c3 MAGup",   "/data/lhcb/users/lins/u1_PID_L0/26Feb/p/");
    curves->add_perf("25c4", "up",   "25c4 MAGup",   "/data/lhcb/users/lins/u1_PID_L0/26Feb/p/");
    
    curves->create_figures("P_K_comparison", .7, 1.05);
    curves->export_canvases();
    delete curves;

    return 0;
}
