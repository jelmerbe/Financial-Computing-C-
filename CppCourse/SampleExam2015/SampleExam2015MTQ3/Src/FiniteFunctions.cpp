//
// Created by Jelmer Bennema on 1/11/24.
//

#include "SampleExam2015MTQ3/SampleExam2015Q3Exercises.hpp"

/** tridiSolver - implements the Thomas algorithm, solves Ax=B
	  * @param a - diagonal below the main diagonal (first entry not used)
	  * @param b - main diagonal
	  * @param c - diagonal above the main diagonal (last entry not used)
	  * @param x - B vector and the solution is written into the same vector
	  */
void exercises::tridiSolver(const DVector & a, const DVector & b, const DVector & c, DVector & x){
    double n = x.size();

    // Forward Sweep
    DVector v(n);
    v[0] = c[0] / b[0];  // if i = 0
    x[0] = x[0] / b[0];  // if i = 0

    for(unsigned int i = 1; i < n; i++){
        v[i] = c[i] / (b[i] - v[i - 1]*a[i] );
        x[i] = ( x[i] - x[i-1]*a[i]) / (b[i] - v[i-1]*a[i]);
    }

    // backward substitution
    for (int j = n - 1; j >= 0; j--){
        x[j] -= x[j+1] * v[j];
    }
}

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
exercises::DMatrix exercises::implicitFiniteDifferenceSolver(double dSmax,
                                       double dT,
                                       double dR,
                                       double dSigma,
                                       size_t n,
                                       size_t m,
                                       PayoffFunction payoff){

    DMatrix V;
    DVector a(n-1), b(n-1), c(n), S(n);
    S[0] = 0.0;
    double delta_t = dT / m;
    double S_step = dSmax / n;

    // find payoffs at m
    for (unsigned int j = 0; j < n; j++){
        V[m][j] = payoff(S[j]);
        S[j+1] = S[j] + S_step;
    }

    // construct matrix A
    for (unsigned int i = 0; i < n; i++) {
        if (i < n - 1) {
            a[i] = -0.5 * (dSigma * dSigma * i - dR) * i * delta_t;
            b[i] = 1 + delta_t * (dSigma * dSigma * i * i + dR);
        }
        c[i] = -0.5 * (dSigma * dSigma * i + dR) * i * delta_t;
    }

    //solve backwards to find option value at t = 0
    for (unsigned int j = m; j > 1; j--){
        tridiSolver(a, b,c, V[j]);
    }

    // return appropriate vectors
    DMatrix return_object;

    return_object[0] = S;
    return_object[1] = V[0];

    return return_object;
}