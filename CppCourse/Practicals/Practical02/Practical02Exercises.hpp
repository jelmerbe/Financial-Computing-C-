#ifndef _PRACTICAL_02_EXERCISES_H__
#define _PRACTICAL_02_EXERCISES_H__

#include <vector>
#include <string>
#include <functional>


namespace exercises
{

typedef std::function<double(double,double)> CoefficientFunction;
typedef std::vector<CoefficientFunction> Equation;
typedef std::vector<double> DVector;
typedef std::function<double(double, double, const DVector &, const Equation &)> NumericalStep;
typedef std::function<double(double)> PayoffFunction;

/** EulerStep - corresponding to the scalar SDE
		dS(t)=a(t,S(t))dt+b(t,S(t))dB(t)
	  * @param dVal initial stockprice
	  * @param dTime time 
	  * @param drivingNoise contains (Dt,DB)
	  * @param equation contains the coefficient functions (a,b)
	  * @return result of Euler step
	  */
double eulerStep(double dVal, 
		 double dTime, 
		 const DVector & drivingNoise, 
		 const Equation & equation);

/** milsteinStep - corresponding to the scalar SDE
		dS(t)=a(t,S(t))dt+b(t,S(t))dB(t)
	  * @param dVal initial stockprice
	  * @param dTime time
	  * @param drivingNoise contains (Dt,DB)
	  * @param equation contains the coefficient functions (a,b,b')
	  * @return result of Milstein step
	  */
double milsteinStep(double dVal, 
		    double dTime,
		    const DVector & drivingNoise,
		    const Equation & equation);

/** MonteCarlo3 - corresponding to the scalar SDE
		dS(t)=a(t,S(t))dt+b(t,S(t))dB(t)
	  * @param dS0 initial stock price
	  * @param dT time to maturity
	  * @param dR riskfree interest rate
	  * @param equation contains the coefficient functions e.g. (a,b) or (a,b,b')
	  * @param numericalStep defines the numerical scheme e.g. eulerstep or milsteinStep
	  * @param iNumberOfSteps number of steps (of equal length) taken by the method
	  * @param iNumberOfPaths number of trajectories generated
	  * @param payoffFunction defines the payoff
	  * @return a vector with two entries, the first is the Monte Carlo estimate of the price, 
	            the second is the estimated stdev of the MC estimate
	  */
DVector MonteCarlo3(double dS0,
		    double dT,
		    double dR,
		    Equation const& equation,
		    NumericalStep const& numericalStep,
		    unsigned long int iNumberOfSteps,
		    unsigned long int iNumberOfPaths,
		    PayoffFunction const& payoffFunction);
				   

}

#endif //_PRACTICAL_02_EXERCISES_H__
