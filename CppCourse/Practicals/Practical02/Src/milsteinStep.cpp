//
// Created by Jelmer Bennema on 12/22/23.
//

#include "Practical02/Practical02Exercises.hpp"

/* euler and milstein step simulate paths of the stock price by taking small steps based on an SDE. These paths can
 * then be used to compute payoff values for Asian options for instance. */


double exercises::milsteinStep(double dVal, double dTime, const exercises::DVector &drivingNoise,
                               const exercises::Equation &equation) {

    double step = dVal + equation[0](dTime, dVal) * drivingNoise[0] + equation[1](dTime, dVal) * drivingNoise[1] +
                  0.5 * equation[1](dTime, dVal) * equation[2](dTime, dVal) *
                  (drivingNoise[1] * drivingNoise[1] - drivingNoise[0]);

    return step;
}
