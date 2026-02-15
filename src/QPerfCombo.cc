#include "QPerfCombo.hh"

QPerfCombo::QPerfCombo(const std::string &batch, 
                       const std::string &polarity,
                       const std::string &directory,
                       const double       cut_value_loose, 
                       const double       cut_value_strict)
                      :_batch    (batch),
                       _polarity (polarity),
                       _directory(directory){
    // Total number of particle combinations
    const unsigned short N_particle_combinations = 6;
    std::pair<std::string, std::string> particle_combinations[N_particle_combinations]{
        {"P" , "K" }, {"P" , "Pi"}, 
        {"K" , "P" }, {"K" , "Pi"}, 
        {"Pi", "P" }, {"Pi", "K" }
    };

    for (unsigned short comb = 0; comb < N_particle_combinations; comb++){
        // Loop through the different particle combinations to produce performance figures
        std::string first_particle  = (*(particle_combinations + comb)).first;
        std::string second_particle = (*(particle_combinations + comb)).second;
        std::string key = first_particle + second_particle; 
        _figures[key] = new QPerf(batch,
                                  polarity,
                                  first_particle,
                                  second_particle,
                                  directory,
                                  cut_value_loose,
                                  cut_value_strict);

        // Construct the name for the figure
        _figure_names[key] =   batch
                             + "_" + polarity
                             + "_" + first_particle
                             + "_v_" + second_particle;
    }
}

void QPerfCombo::export_canvases(){
    // Save the canvases using QPerf::export_canvases
    std::unordered_map<std::string, QPerf*>::const_iterator hist_iterator;
    for (hist_iterator  = _figures.begin();
         hist_iterator != _figures.end(); 
         hist_iterator++){
        std::string key         = hist_iterator->first;
        QPerf *perf_figure      = hist_iterator->second;
        std::string figure_name = _figure_names.at(key);
        perf_figure->export_canvases(figure_name);
    }
}

QPerfCombo::~QPerfCombo(){
    std::unordered_map<std::string, QPerf*>::const_iterator hist_iterator;
    for (hist_iterator  = _figures.begin();
         hist_iterator != _figures.end(); 
         hist_iterator++){
        delete hist_iterator->second;
    }
}
