//
// Created by Jelmer Bennema on 12/22/23.
//

#include "Practical01/Practical01Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>

std::vector<double> exercises::MonteCarlo2(double dR,
                                double dSigma,
                                double dS0,
                                double dT,
                                unsigned long int iN,
                                Payoff call){

    std::vector<double> payoff(iN);
    double dS;

    // generate a thousand paths
    for (int i = 0; i < iN; i++){
        double Brownian = std::sqrt(dT) * utils::NormalDist();

        // Geometric Brownian Motion - stock price
        dS = dS0 * exp( (dR - (dSigma * dSigma) / 2) * dT + dSigma * Brownian);

        // compute payoff call option
        payoff[i] = exp(-dR * dT) * call(dS);
    }

    // return MC estimate and standard deviation
    double mean = std::accumulate(payoff.begin(), payoff.end(), 0.0) / iN;

    // create vector of squared differences and use to find std
    transform(payoff.begin(), payoff.end(), payoff.begin(),
              [mean](double x) { return (x - mean) * (x - mean);});

    double variance = std::accumulate(payoff.begin(), payoff.end(), 0.0) / iN;
    std::cout << variance << std::endl; 
    double std = std::sqrt(variance);

    std::vector<double> MC = {mean, std};
    return MC;
}