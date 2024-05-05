//
// Created by Jelmer Bennema on 12/22/23.
//

#include "Practical01/Practical01Exercises.hpp"

double exercises::NormInf(const std::vector<double> & dVec){

    double max = 0.0;

    // loop through vector and find maximum
    for (auto value : dVec){

        if (std::abs(value) > max){
            max = std::abs(value);
        }
    }

    return max;

}