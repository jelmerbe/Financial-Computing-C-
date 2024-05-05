//
// Created by Jelmer Bennema on 12/22/23.
//

#include "Practical01/Practical01Exercises.hpp"
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>

double exercises::Norm2(const std::vector<double> & dVec){

    // square all entries in vector
    std::vector<double> copy = dVec;
    std::transform(copy.begin(), copy.end(), copy.begin(), [](double x) { return x * x; });

    // return sqrt of sum of squared vector
    return std::sqrt(std::accumulate(copy.begin(), copy.end(), 0.0));
}


