

// Creates a figure that compares performances between different batches
// Compile with 
// g++ -O3 script_name.cc -o executable_name $(root-config --cflags --libs) $(PIDQuantify-config)


#include "QPerfCollection.hh"

int main(){
    std::string ref_particles[2] = {"K", "Pi"};
    std::string magnet[2] = {"up", "down"};
    for (unsigned short r = 0; r < 2; r++){
        for (unsigned short m = 0; m < 2; m++){
            QPerfCollection *curves = new QPerfCollection("P",
                                                          ref_particles[r],
                                                          5);

            curves->add_perf("25c1",
                             magnet[m],
                             "25c1 MAG" + magnet[m],
                             "/data/lhcb/users/lins/u1_PID_L0/26Feb/p/");
            curves->add_perf("25c1",
                             magnet[m],
                             "25c1 MAG" + magnet[m] + "new",
                             "/data/lhcb/users/lins/u1_PID_L0/26Feb/P/");
            curves->add_perf("25c4",
                             magnet[m],
                             "25c4 MAG" + magnet[m],
                             "/data/lhcb/users/lins/u1_PID_L0/26Feb/p/");
            curves->add_perf("25c4",
                             magnet[m],
                             "25c4 MAG" + magnet[m] + "new",
                             "/data/lhcb/users/lins/u1_PID_L0/26Feb/P/");
            
            curves->create_figures("P_" + ref_particles[r] + "_comparison_mag" + magnet[m]);
            curves->export_canvases();
            delete curves;
        }
    }

    return 0;
}
