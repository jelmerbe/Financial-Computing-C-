//
// Created by Jelmer Bennema on 12/22/23.
//

#include "Practical01/Practical01Exercises.hpp"
#include <cmath>

double exercises::callAt1(double dS){

    //return payoff for strike = 1
    return fmax(dS - 1, 0);
}