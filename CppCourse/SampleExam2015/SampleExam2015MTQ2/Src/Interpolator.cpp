//
// Created by Jelmer Bennema on 1/11/24.
//

#include "SampleExam2015MTQ2/SampleExam2015Q2Exercises.hpp"

/** constructor
     * @param xVec x-values
     * @param yVec y-values
     */
exercises::polynomialInterpolator::polynomialInterpolator(const exercises::dVector &xVec,
                                                          const exercises::dVector &yVec) {
    // assert X and Y have the same size
    assert(xVec.size() == yVec.size());

    // Fill up first entry
    size_t n = xVec.size();

    // fill up remaining entries using addPoint
    for (unsigned int i = 1; i < n; i++){
        addPoint(xVec[i], yVec[i]);
    }
}

/** addPoint - adds new point to the interpolator
    * @param x new x-value
    * @param y corresponding y value
    */

void exercises::polynomialInterpolator::addPoint(double x, double y) {
    // Ensure x is not already in m_x
    for (double xi : m_x) {
        assert(x != xi);
    }

    // Append the new point
    m_x.push_back(x);

    // Calculate v and z for the new point
    size_t i = m_x.size() - 1; // Index of the new point
    double v = y;
    double z = 1;

    if (i > 0) {
        for (size_t j = 0; j < i; ++j) {
            z *= (x - m_x[j]); // Calculate z first
        }

        for (size_t j = 0; j < i; ++j) {
            // Ensure we don't divide by zero
            assert(m_x[i] != m_x[j]);
            double z_j = 1;
            for (size_t k = 0; k < i; ++k) {
                if (k != j) {
                    z_j *= (m_x[i] - m_x[k]);
                }
            }
            v -= m_v[j] * m_z[j] / z_j;
        }
    }

    m_v.push_back(v);
    m_z.push_back(z);
}

/** operator() - evaluates polynomial at x
 * @param x x-value the polynomial is to be evaluated at
 */

double exercises::polynomialInterpolator::operator()(double x) const {
    double p = 0;

    for (size_t i = 0; i < m_x.size(); ++i) {
        double w = 1;
        for (size_t j = 0; j < i; ++j) {
            w *= (x - m_x[j]) / (m_x[i] - m_x[j]);
        }
        p += w * m_v[i];
    }
    return p;
}