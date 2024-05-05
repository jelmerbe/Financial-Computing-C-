#ifndef _PRACTICAL_01_EXERCISES_H__
#define _PRACTICAL_01_EXERCISES_H__

#include <vector>
#include <string>
#include <functional>


namespace exercises
{

typedef std::function<double(double)> Payoff; // Payoff is alies for function that takes double and returns double

/** Euclidean norm of a vector
	  * @param dVec vector of doubles
	  * @return Euclidean norm of dVec 
	  */
double Norm2(const std::vector<double> & dVec);

/** Inf norm of a vector
	  * @param dVec vector of doubles
	  * @return inf norm of dVec
	  */
double NormInf(const std::vector<double> & dVec);


/** Simple Monte Carlo estimation of a Call
	  * @param dR riskfree rate of return
	  * @param dSigma sigma
	  * @param dS0 initial stock price
	  * @param dK strike price
	  * @param dT time to maturity
	  * @param iN sample size
	  * @return Monte Carlo estimate
	  */
double MonteCarlo1(double dR, 
				   double dSigma, 
				   double dS0, 
				   double dK , 
				   double dT, 
				   unsigned long int iN);


/** Simple Monte Carlo estimation of a European function
	  * @param dR riskfree rate of return
	  * @param dSigma sigma
	  * @param dS0 initial stock price
	  * @param dT time to maturity
	  * @param iN sample size
	  * @param call payoff function
	  * @return a vector of two entries: Monte Carlo estimate, stdev estimate
	  */
std::vector<double> MonteCarlo2(double dR, 
				   double dSigma, 
				   double dS0, 
				   double dT, 
				   unsigned long int iN, 
				   Payoff call);


/** Particular payoff function - call with strike 1.0
	  * @param dS stock price
	  * @return call payoff with strike 1.0
	  */
double callAt1(double dS);

}

#endif //_PRACTICAL_01_EXERCISES_H__