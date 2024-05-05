#ifndef _EXAM2023_Q2_EXERCISES_H__
#define _EXAM2023_Q2_EXERCISES_H__

#include <vector>
#include <string>
#include <limits> // required for std::numerical_limits<T>::infinity

namespace exercises
{

    class GaussianIntegrals
    {
    public:

        /** Constructor.
         * @param left_x_arg lower end of the interval [a,b]
         * @param right_x_arg upper end of the interval [a,b]
         * @param lambda_arg multiplicative coefficient lambda
         */
        GaussianIntegrals(double left_x_arg, double right_x_arg, double lambda_arg);

        /**
         *
         * @param i
         * @return E[(lambda * z)^i \indicator{a < lambda * z < b}]
         */
        double operator()(unsigned int i);

    private:

        double left_x, right_x, left_pdf, right_pdf, lambda;
        std::vector<double> cached_results_even;
        std::vector<double> cached_results_odd;
    };



}

#endif //_EXAM2023_Q2_EXERCISES_H__
