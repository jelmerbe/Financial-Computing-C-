//
// Created by Jelmer Bennema on 1/2/24.
//

#include <boost/numeric/ublas/lu.hpp>
#include "Practical05/Practical05Exercises.hpp"
#include <algorithm>


/** Regression computes regression coefficients
  * @param yVals observed y values
  * @param factors explanatory factors corresponding to observed y values
  * @param testFunctions vector of test functions
  * @return regression coefficients
 */

 using boost::numeric::ublas::inner_prod;
 using boost::numeric::ublas::trans;

exercises::BVector exercises::Regression(const BVector & yVals,
                   const std::vector<BVector> & factors,
                   const FVector & testFunctions){

    // create sigma matrix
    BVector::size_type i, j, n1, n2;
    n1 = factors.size();
    n2 = testFunctions.size();

    BMatrix sigma(n1, n2);

    for (i = 0; i < n1; i++){
        for (j = 0; j < n2; j++){
            sigma(i, j) = testFunctions[j](factors[i]);
        }
    }

    // find Beta values
    BMatrix sigmaT = trans(sigma);
    BMatrix A = prod(sigmaT ,  sigma);
    BVector Beta = prod(sigmaT, yVals);

    lu_factorize(A);
    lu_substitute<const BMatrix,BVector>(A,Beta);

    return Beta;
}