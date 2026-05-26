

// Creates a figure that compares performances between different batches
// Compile with 
// g++ -O3 script_name.cc -o executable_name $(root-config --cflags --libs) $(PIDQuantify-config)


#include "QPerfCollection.hh"

int main(){
    std::string ref_particles[2] = {"K", "Pi"};
    for (unsigned short r = 0; r < 2; r++){
        QPerfCollection *curves = new QPerfCollection("P",
                                                      ref_particles[r],
                                                      5);

        curves->add_perf("25c2",
                         "down",
                         "25c2 MAGdown",
                         "/data/lhcb/users/lins/u1_PID_L0/26Feb/p/");
        curves->add_perf("25c2",
                         "down",
                         "25c2 MAGdown refit",
                         "/data/lhcb/users/lins/u1_PID_L0/26Feb/P/");
       
        curves->create_figures("P_" + ref_particles[r] + "_comparison_magup_c2");
        curves->export_canvases();
        delete curves;
    }

    return 0;
}
