

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
                                                "/data/lhcb/users/lins/u3_PIDQuantify/histograms_modified_binning/");

    curves->add_curve(std::vector<std::string>{"24b7", "24b8"}, 
                      std::vector<std::string>{"down", "up"},
                       "24b7/8");
    curves->add_curve(std::vector<std::string>{"25c1", "25c1"}, 
                      std::vector<std::string>{"down", "up"},
                       "25c1");
    curves->add_curve(std::vector<std::string>{"25c2", "25c3", "25c4", "25c4"},
                      std::vector<std::string>{"down", "up", "up", "down"},
                      {"25c2/3/4"});

    curves->create_figure("P_K_comparison");
    curves->export_canvas();
    delete curves;

    return 0;
}
