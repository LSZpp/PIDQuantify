#ifndef G601
#define G601

// The storage space for all paths
// LSZ 14 Feb 25

// A function that returns the histogram path after specifying the settings

#include <string>

std::string(std::string &batch, std::string &polarity, std::string &particle, std::string &cut_string);
    // batch: for example "25c2"
    // polarity: for example "u" for "up", "d" for "down"
    // particle: for example "P", "Pi", "K"
    // cut string: for example "DLLP-DLLK>5"
    
