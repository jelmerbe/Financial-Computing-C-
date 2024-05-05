#ifndef _PRACTICAL_05_EXERCISES_H__
#define _PRACTICAL_05_EXERCISES_H__

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include <functional>
namespace exercises
{



/** Computes a-b using bitmanipulation operations only
 * @param a
 * @param b
 * @return a-b
 */
unsigned int subtract(unsigned int a, unsigned int b);

/** Swaps the values of two arguments using bitmanipulation operations only, 
 * and without any additional temp variables.
 * @param a
 * @param b
 */
void swap(unsigned int & a, unsigned int & b);


typedef boost::numeric::ublas::vector<double> BVector; // boost vector of doubles
typedef boost::numeric::ublas::matrix<double> BMatrix; // boost matrix of doubles
typedef std::function<double(const BVector &)> Function; // type of test function
typedef std::vector<Function> FVector; // std vector of test functions


/** Regression computes regression coefficients
  * @param yVals observed y values
  * @param factors explanatory factors corresponding to observed y values
  * @param testFunctions vector of test functions
  * @return regression coefficients
 */
BVector Regression(const BVector & yVals, 
		   const std::vector<BVector> & factors, 
		   const FVector & testFunctions);


/** Projection computes projected value
  * @param factor 
  * @param testFunctions vector of test functions
  * @param coefficients regression coefficients
  * @return regressed value 
 */
double Projection(const BVector & factor, 
		  const FVector & testFunctions, 
		  const BVector & coefficients);


/** \class EuropeanOptionPricer
	\brief Prices European options based on simulation and regression

	*/
class EuropeanOptionPricer
{
public:
	/** EuropeanOptionPricer constructor, initialises data members
	  * @param factorsAt0 grid of factor values at time 0
	  * @param valuesAtT discounted option payoff at maturity, corresponding
	  * @param testFunctions set of test functions uded for projection
	  * @return regressed value 
	*/
  EuropeanOptionPricer(const std::vector<BVector> & factorsAt0, 
		       const BVector & valuesAtT,
		       const FVector & testFunctions){

      // initialize data members
      m_Coefficients = Regression(valuesAtT, factorsAt0, testFunctions);
      m_TestFunctions = testFunctions;
  }
	
	/** operator() option pricer
	  * @param factorsAt0 grid of factor values at time 0
	  * @param testFunctions vector of test functions
	  * @param coefficients regression coefficients
	  * @return regressed value 
	*/	
  double operator()(const BVector & factorAt0){

      double regressed_value = Projection(factorAt0, m_TestFunctions, m_Coefficients);

      return regressed_value;
  }

private:
  FVector m_TestFunctions;
  BVector m_Coefficients;
};


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
BVector MonteCarlo4(std::vector<BVector> vS0,
		    double dR,
		    double dSigma1,
		    double dSigma2,
		    double dRho,
		    double dT,
		    Function const& payoff);



}
#endif //_PRACTICAL_05_EXERCISES_H__
