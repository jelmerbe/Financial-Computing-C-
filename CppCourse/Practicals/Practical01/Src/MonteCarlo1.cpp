//
// Created by Jelmer Bennema on 12/22/23.
//

#include "Practical01/Practical01Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <cmath>

double exercises::MonteCarlo1(double dR,
                   double dSigma,
                   double dS0,
                   double dK ,
                   double dT,
                   unsigned long int iN){

    double Total_payoff = 0.0;
    double dS;

    // generate a thousand paths
    for (int i =0; i < iN; i++){
        double Brownian = std::sqrt(dT) * utils::NormalDist();

        // Geometric Brownian Motion - stock price
        dS = dS0 * exp( (dR - (dSigma * dSigma) / 2) * dT + dSigma * Brownian);

        // compute payoff call option
        Total_payoff += exp(-dR * dT) * fmax(dS - dK, 0);
    }

    // return average payoff
    return Total_payoff/iN;

}