
#include "ExamQ1/Exam2023Q1Exercises.hpp"
#include <cmath>
#include <Utils/UtilityFunctions.hpp> // for NormalDist
#include <numeric> // for accumulate

std::pair<double, double> exercises::MeanStdevRate(const exercises::RateParameters &rateParameters, double T) {

    // find statistics using parameters beta, sigma, discountfunction
    std::pair<double, double> statistics;

    double delta = std::pow(10, -5);
    double Tplus = T + delta;
    double Tminus = T - delta;
    if (Tminus < 0){ Tminus = 0; }

    // compute expected value
    statistics.first = - (log(rateParameters.discountFunction(Tplus)) - log(rateParameters.discountFunction(Tminus))) /
            (Tplus - Tminus);

    // compute stddev
    if (rateParameters.beta == 0){
        statistics.second = rateParameters.sigma * sqrt(T);
    }
    else { statistics.second = sqrt( (rateParameters.sigma * rateParameters.sigma * ( 1 - exp(-2 * rateParameters.beta * T))) /
                          (2 * rateParameters.beta)); }

    return statistics;
}


double exercises::BondPrice(double r, const exercises::BondParameters &bondParameters,
                            const exercises::RateParameters &rateParameters) {

    double T1 = bondParameters.T1;
    double T2 = bondParameters.T2;
    double sigma = rateParameters.sigma;
    double beta = rateParameters.beta;
    double B, A, Fm;

    // compute B(T1, T2)
    if(beta == 0){
        B = T2 - T1;
    }
    else {
        B = 1/beta * (1 - exp(-beta * (T2 - T1)));
    }

    // Compute A(T1, T2)
    Fm = MeanStdevRate(rateParameters, T1).first;
    if(beta ==0){
        A = rateParameters.discountFunction(T2)/ rateParameters.discountFunction(T1)
                * exp((T2 - T1) * Fm - (sigma*sigma * T1)/2 * (T2 - T1) * (T2 - T1));
    }
    else {
        A = rateParameters.discountFunction(T2) / rateParameters.discountFunction(T1)
            * exp(B * Fm - sigma * sigma / (4 * beta) * (1 - exp(-2 * beta * T1)) * B * B);
    }

    // compute and return bondprice P(T1, T2, r)
    return  A * exp(-B * r);
}

// function taken from homework - to compute standard deviation of a payoff vector
double calculateStdDev(const std::vector<double>& data) {
    if (data.empty()) {
        return 0.0;
    }

    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    double sq_sum = std::accumulate(data.begin(), data.end(), 0.0,
                                    [mean](double acc, double value) {
                                        return acc + std::pow(value - mean, 2);
                                    });
    return std::sqrt(sq_sum / data.size());
}

// monte carlo bond option pricing
std::pair<double, double> exercises::BondOptionMonteCarlo(const exercises::RateParameters &rateParameters,
                                                          const exercises::BondParameters &bondParameters,
                                                          const exercises::Payoff &payoff, unsigned int sampleSize) {


    double T1 = bondParameters.T1;
    double T2 = bondParameters.T2;
    double rT, F, P;
    std::vector<double> PayOff(sampleSize);
    std::pair<double, double> MC;

    for(unsigned int i = 0; i < sampleSize; i++){

        // generate rT
        std::pair<double, double> dist = MeanStdevRate(rateParameters, T1);
        rT = dist.first + utils::NormalDist() * dist.second;

        // compute payoff
        P = BondPrice(rT, bondParameters, rateParameters);
        F = payoff(P);

        // find discounted payoff
        PayOff[i] =  rateParameters.discountFunction(T1) * F;
    }

    // return MC statistics
    MC.first = std::accumulate(PayOff.begin(), PayOff.end(), 0.0) / sampleSize;
    MC.second = calculateStdDev(PayOff);

    return MC;
}