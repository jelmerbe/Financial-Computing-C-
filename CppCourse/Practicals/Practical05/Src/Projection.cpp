//
// Created by Jelmer Bennema on 1/3/24.
//

#include <boost/numeric/ublas/lu.hpp>
#include "Practical05/Practical05Exercises.hpp"

/** Projection computes projected value
  * @param factor
  * @param testFunctions vector of test functions
  * @param coefficients regression coefficients
  * @return regressed value
 */
double exercises::Projection(const BVector & factor,
                  const FVector & testFunctions,
                  const BVector & coefficients){

    double value = 0.0;
    BVector::size_type i, n;
    n = std::min(coefficients.size(), testFunctions.size());

    for (i = 0; i < n; i++){
        value += testFunctions[i](factor) * coefficients[i];
    }

    return value;
}