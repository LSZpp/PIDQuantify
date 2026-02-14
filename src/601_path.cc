#include "601_path.hh"

std::string(std::string &batch, std::string &polarity, std::string &particle, std::string &cut_string){
    std::string base_directory = std::string("/data/lhcb/users/lins/u1_PID_L0/");
    std::string binning = std::string("-P.ETA.root");
    std::string file_name =   std::string("/effhists-")
                            + batch 
                            + polarity;
    std::string path = base + batch + polarity; 
}
