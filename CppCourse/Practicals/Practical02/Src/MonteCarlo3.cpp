//
// Created by Jelmer Bennema on 12/22/23.
//

#include "Practical02/Practical02Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <cmath>
#include <numeric>

exercises::DVector exercises::MonteCarlo3(double dS0, double dT, double dR, const exercises::Equation &equation,
                               const exercises::NumericalStep &numericalStep, unsigned long iNumberOfSteps,
                               unsigned long iNumberOfPaths, const exercises::PayoffFunction &payoffFunction) {

    double t_step = dT/iNumberOfSteps;
    DVector payoff(iNumberOfPaths);
    double time_ = t_step;
    double dVal;
    DVector res(2);


    // loop through all paths and steps
    for (unsigned long i = 0; i < iNumberOfPaths; i++){
        double dS = dS0;
        double dTime = 0.0;

        for (unsigned long j = 0; j < iNumberOfSteps; j++){
            DVector drivingNoise = {t_step, std::sqrt(t_step) * utils::NormalDist()};
            dTime += t_step;
            dS = numericalStep(dS, dTime, drivingNoise, equation);
        }

        dVal=payoffFunction(dS);
        res[0]+=dVal/iNumberOfPaths;
        res[1]+=dVal*dVal/iNumberOfPaths;
    }
    res[1]-=res[0]*res[0];
    res[1]=sqrt(res[1]/iNumberOfPaths);
    res[1]*=exp(-dR*dT);
    res[0]*=exp(-dR*dT);
    return res;
    }
