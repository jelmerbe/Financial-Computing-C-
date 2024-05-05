#ifndef _EXAM2015_Q1_EXERCISES_H__
#define _EXAM2015_Q1_EXERCISES_H__
#include <functional>
#include <utility>
#include <string>



namespace exercises
{

static std::string sMyName("1079868");

typedef std::function<double(double)> Payoff;
struct MCResults
{
    double mean, stdev_of_mc_estimate;
};

/** P(t,T) value of zero coupon bond at t with maturity T
 * @param r instantaneous rate at t
 * @param t time
 * @param T maturity of bond
 * @param kappa mean reversion speed
 * @param phi mean reversion level
 * @param sigma volatility of instantaneous rate
 * @return bond price at t with maturity T
 */
  double bondPrice(double r, double t, double T, double kappa, double phi, double sigma);

/** Expected value of instantaneous rate r at t
 * @param r0 initial value of r
 * @param t time
 * @param kappa mean reversion speed
 * @param phi mean reversion level
 * @return expected value of r at t
 */
  double expectedValueOfR(double r0,double t, double kappa, double phi);

/** Expected value of instantaneous rate r at t
 * @param r0 initial value of r
 * @param t time
 * @param kappa mean reversion speed
 * @param sigma volatility of instantaneous rate
 * @return standard deviation of rate at t
 */
  double standardDeviationOfR(double t, double kappa, double sigma);


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
  MCResults MonteCarloBond(double r0,
			 double kappa,
			 double phi,
			 double sigma,
			 double maturityOfBond,
			 double maturityOfOption,
			 unsigned long int sampleSize,
			 Payoff payoff);




}

#endif //_EXAM2015_Q1_EXERCISES_H__
