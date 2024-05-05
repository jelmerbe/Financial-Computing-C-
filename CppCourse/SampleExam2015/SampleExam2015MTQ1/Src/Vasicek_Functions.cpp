//
// Created by Jelmer Bennema on 1/11/24.
//

#include "SampleExam2015MTQ1/SampleExam2015Q1Exercises.hpp"
#include <cmath> // for exp
#include "Utils/UtilityFunctions.hpp" // for normal dist
#include <numeric> // accumulate


/** P(t,T) value of zero coupon bond at t with maturity T
 * @param r instantaneous rate at t
 * @param t time
 * @param T maturity of bond
 * @param kappa mean reversion speed
 * @param phi mean reversion level
 * @param sigma volatility of instantaneous rate
 * @return bond price at t with maturity T
 */
double exercises::bondPrice(double r, double t, double T, double kappa, double phi, double sigma){
    double Bt, At, bond_price;

    Bt = 1/kappa * (  1 - std::exp(-kappa * (T - t)));
    At = exp((phi - sigma*sigma/(2 * kappa * kappa)) * (Bt - T + t) - (sigma *sigma * Bt * Bt)/(4 * kappa));

    bond_price = At * exp(-Bt * r);
    return bond_price;

}


/** Expected value of instantaneous rate r at t
 * @param r0 initial value of r
 * @param t time
 * @param kappa mean reversion speed
 * @param phi mean reversion level
 * @return expected value of r at t
 */
double exercises::expectedValueOfR(double r0,double t, double kappa, double phi){
    double Expected_value =  r0 * exp(-kappa * t) + phi * (1 - exp(-kappa * t));

    return Expected_value;
}

/** Expected value of instantaneous rate r at t
 * @param r0 initial value of r
 * @param t time
 * @param kappa mean reversion speed
 * @param sigma volatility of instantaneous rate
 * @return standard deviation of rate at t
 */
double exercises::standardDeviationOfR(double t, double kappa, double sigma){
    double StDev;

    StDev = sqrt((sigma * sigma * (1 - exp(-2 * kappa * t)))/ (2 * kappa));
    return StDev;
}

/** Monte Carlo estimation of a European bond option
 * @param r0 instantaneous rate at time 0
 * @param kappa mean reversion speed
 * @param phi mean reversion level
 * @param sigma volatility of instantaneous rate
 * @param maturityOfBond
 * @param maturityOfOption (we assume maturityOfBond > maturityOfOption)
 * @param sampleSize number of sample items to generate
 * @param payoff payoff function
 * @return a pair with two entries: Monte Carlo estimate, stdev estimate
 */
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


exercises::MCResults exercises::MonteCarloBond(double r0,
                         double kappa,
                         double phi,
                         double sigma,
                         double maturityOfBond,
                         double maturityOfOption,
                         unsigned long int sampleSize,
                         Payoff payoff){

    MCResults Answer;
    double rT, Expected, std, Bond, P0T;
    std::vector<double> PayOff(sampleSize);

    // Loop through all samples and find discounted payoff
    for(unsigned int i = 0; i < sampleSize; i++){
        // generate sample of rT
        Expected = expectedValueOfR(r0, maturityOfOption, kappa, phi);
        std = standardDeviationOfR(maturityOfOption, kappa, sigma);

        rT = Expected + utils::NormalDist() * std;

        // compute the bond price
        Bond = bondPrice(rT, maturityOfOption, maturityOfBond, kappa, phi, sigma);
        P0T = bondPrice(r0, 0, maturityOfBond, kappa, phi, sigma);

        // find payoff
        PayOff[i] = P0T * payoff(Bond);
    }

    // find Monte Carlo Estimate + stdev
    Answer.mean = std::accumulate(PayOff.begin(), PayOff.end(), 0.0) / sampleSize;
    Answer.stdev_of_mc_estimate = calculateStdDev(PayOff);

    return Answer;
}






