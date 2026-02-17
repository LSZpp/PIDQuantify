

// Creates a figure that compares ROC curves between different batches
// Compile with 
// g++ -O3 script_name.cc -o executable_name $(root-config --cflags --libs) $(PIDQuantify-config)


#include "QROCCollection.hh"

int main(){
    QROCCollection *curves = new QROCCollection("P",
                                                "K",
                                                -50. , 
                                                 50. ,
                                                   .5,
                                                "/data/lhcb/users/lins/u1_PID_L0/26Feb/p/");

    curves->add_curve("24b8", "up", "24b8 MAGup");
    curves->add_curve("25c1", "up", "25c1 MAGup");
    curves->add_curve("25c3", "up", "25c3 MAGup");
    curves->add_curve("25c4", "up", "25c4 MAGup");
    
    curves->create_figure("P_K_comparison");
    curves->export_canvas();
    delete curves;

    return 0;
}
