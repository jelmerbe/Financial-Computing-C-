//
// Created by Jelmer Bennema on 1/3/24.
//

#include <boost/numeric/ublas/lu.hpp>
#include "Practical05/Practical05Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"

/** MonteCarlo4 - given a grid of initial stock values (2D GBM), generates a set of possible corresponding payoffs
  * @param vS0 an std vector of initial factors
  * @param dR riskfree rate
  * @param dSigma1 vol of the first component
  * @param dSigma2 vol of the second component
  * @param dRho correlation of driving BM components
  * @param dT time to maturity
  * @param payoff payoff function
  * @return regressed value
 */

exercises::BVector exercises::MonteCarlo4(std::vector<BVector> vS0,
                    double dR,
                    double dSigma1,
                    double dSigma2,
                    double dRho,
                    double dT,
                    Function const& payoff){

    BVector S(2);
    BVector::size_type i, n;
    n = vS0.size();
    BVector final_payoff(n);

    // create vector of simulated stock prices
    for (i = 0; i < n; i++) {

        // construct brownian increments
        double B1 = utils::NormalDist() * sqrt(dT);
        double B2 = utils::NormalDist() * sqrt(dT);
        B2 = dRho * B1 + sqrt(1 - dRho * dRho) * B2;

        // Use geometric brownian motion
        S[0] = vS0[i][0] * exp((dR - dSigma1 * dSigma1 * 0.5)*dT + dSigma1 * B1);
        S[1] = vS0[i][1] * exp((dR - dSigma2 * dSigma2 * 0.5)*dT + dSigma2 * B2);

        //find payoff vector - and apply discount
        final_payoff[i] =  payoff(S) * exp(-dR*dT);
    }

    return final_payoff;
}