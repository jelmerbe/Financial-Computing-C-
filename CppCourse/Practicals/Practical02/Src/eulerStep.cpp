//
// Created by Jelmer Bennema on 12/22/23.
//

#include "Practical02/Practical02Exercises.hpp"

double exercises::eulerStep(double dVal,
                 double dTime,
                 const DVector & drivingNoise,
                 const Equation & equation){

    double step = dVal + equation[0](dTime, dVal) * drivingNoise[0] + equation[1](dTime, dVal) * drivingNoise[1];

    return step;
}