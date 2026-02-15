#ifndef QPROPERTY_HH
#define QPROPERTY_HH

// The QProperty class 
// LSZ 15 Feb 25

// A class storing the property of a particular efficiency histogram

#include <string>

class QProperty{
private:
    const std::string _batch;               // batch of the cut, for example 24b7, 25c1
    const std::string _polarity;            // magnet polarity: "up" or "down"
                                            // the batch and the magnet polarity uniquely specifies a dataset

    const std::string _first_particle;      // the particle presented in the histogram
    const std::string _second_particle;     // the second particle forming the difference of the "DLL"
                                            // particles can be one of: "P", "K", "Pi"

    const std::string _identification_type; // can be "ID" or "misID"
                                            // ID = first particle identified into itself via
                                            // DLL(first particle - second particle) > cut 
                                            // misID = second particle identified into the first particle via
                                            // DLL(second particle - first particle) < cut
        
    const double _cut_value;                // the numerical value of the cut

    const std::string _directory;           // the directory of the histogram

    std::string _find_dataset() const;
                    // finds the dataset from the batch

    std::string _find_probe_particle() const;
                    // finds the probe particle

public:
    std::string construct_cut_string() const;
                    // constructs the cut string using the property of the efficiency histogram

    QProperty(const std::string &batch,
              const std::string &polarity,
              const std::string &first_particle,
              const std::string &second_particle,
              const std::string &identification_type,
              const double       cut_value,
              const std::string &directory);
                    // constructor

    void print() const;
                    // prints the contents of the property

    std::string path() const; 
                    // finds the path of the corresponding histogram

    ~QProperty();   // destructor
};

#endif
