#include "tiny-00.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

void write_stats(std::vector<double> const& data, std::ostream& out) {
    double data_min = std::numeric_limits<double>::max();
    double data_max = -std::numeric_limits<double>::max();
    double data_average = 0;

    for (auto & blob : data){
        if ( blob > data_max ) {
            data_max = blob;
        }
        if ( blob < data_min) {
            data_min = blob;
        }
        data_average += blob;
    }
    data_average /= data.size();
    out << std::fixed << std::setprecision(2) << "min: " << data_min << std::endl;
    out << std::fixed << std::setprecision(2) << "max: " << data_max << std::endl;
    out << std::fixed << std::setprecision(2) << "mean: " << data_average << std::endl;
}

// int main(){
//     std::vector<double> data { 10.1, 20.21323, 30.44 };
//     write_stats(data, std::cout);
// }