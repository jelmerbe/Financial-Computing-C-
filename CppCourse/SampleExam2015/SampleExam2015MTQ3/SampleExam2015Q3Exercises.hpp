#ifndef _EXAM2015_QUESTION_3_HPP__
#define _EXAM2015_QUESTION_3_HPP__
#include <functional>
#include <vector>
#include <string>

namespace exercises
{

static std::string sMyName("1079868");

typedef std::vector<double> DVector;
typedef std::vector<DVector> DMatrix;
typedef std::function<double(double)> PayoffFunction;

/** tridiSolver - implements the Thomas algorithm, solves Ax=B
	  * @param a - diagonal below the main diagonal (first entry not used)
	  * @param b - main diagonal
	  * @param c - diagonal above the main diagonal (last entry not used)
	  * @param x - B vector and the solution is written into the same vector	
	  */
void tridiSolver(const DVector & a, const DVector & b, const DVector & c, DVector & x);


/** implicitFiniteDifferenceSolver - implements the implicit scheme for the BSPDE
	  * @param dSmax - upper end of S-grid
	  * @param dT - time to maturity
	  * @param dR - riskfree interest rate
	  * @param dSigma - volatility
	  * @param n - number of S gridpoints
	  * @param m - number of time-steps
	  * @param payoff - payoff function 
	  * @returns a matrix of size n x 2, the first column is the S grid, the second column 
				 contains the estimated option prices
	  */
DMatrix implicitFiniteDifferenceSolver(double dSmax, 
				       double dT, 
				       double dR,
				       double dSigma,
				       size_t n,
				       size_t m,
				       PayoffFunction payoff);


}

#endif //_EXAM2015_QUESTION_3_HPP__
