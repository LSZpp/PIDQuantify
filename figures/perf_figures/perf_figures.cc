

// Creates performance figures for a particular batch
// Compile with 
// g++ -O3 script_name.cc -o executable_name $(root-config --cflags --libs) $(PIDQuantify-config)


#include "QPerfCombo.hh"

int main(){
    QPerfCombo *perf_combo = new QPerfCombo("25c1",
                                            "up",
                                            "/data/lhcb/users/lins/u1_PID_L0/26Feb/p/");
    perf_combo->export_canvases();
    delete perf_combo;

    return 0;
}
