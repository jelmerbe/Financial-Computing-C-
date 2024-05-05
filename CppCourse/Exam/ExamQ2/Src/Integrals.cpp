

#include "ExamQ2/Exam2023Q2Exercises.hpp"
#include <Utils/UtilityFunctions.hpp>
#include <boost/math/constants/constants.hpp>


// Implement constructor
exercises::GaussianIntegrals::GaussianIntegrals(double left_x_arg, double right_x_arg, double lambda_arg)
: left_x(left_x_arg), right_x(right_x_arg), lambda(lambda_arg){}



// implement operator - algorithm 1 (where argument = n)
double exercises::GaussianIntegrals::operator()(unsigned int i) {

    double f; // value to be returned

    //////////////////////// step 1 (handle lambda = 0 case)
    if (lambda == 0) {
        // Prevent duplicate entries
        if (i % 2 == 0 && i/2 < cached_results_even.size()) {
            return cached_results_even[i/2];
        }
        if (i % 2 != 0 && (i-1)/2 < cached_results_odd.size()) {
            return cached_results_odd[(i-1)/2];
        }

        // compute f(0) and append to even results - given no duplicate entries
        if (i == 0) {
            if (left_x < 0 && right_x > 0){
                f = 1;}
            else {f = 0; }

            cached_results_even.push_back(f);
            return f;
        }
        // compute f(n) and append to even/odd results
        if (i % 2 == 0){
            cached_results_even.push_back(0);
            return 0;
        }
        else {
            cached_results_odd.push_back(0);
            return 0;
        }
    }

    ////////////////////// step 2 (check if value has been computed and return)
    if(i % 2 == 0){
        if (cached_results_even.size() > i/2){
            return cached_results_even[i/2];
        }
    }
    if(i % 2 != 0){
        if (cached_results_odd.size() > (i-1)/2){
            return cached_results_odd[(i-1)/2];
        }
    }

    /////////////////////// step 3 compute f values (for ones that dont exist yet)


    double pi =  boost::math::constants::pi<double>();
    left_pdf = 1 / (sqrt(2 * pi )) * exp(- (left_x/lambda) * (left_x/lambda) / 2);
    right_pdf = 1 / (sqrt(2 * pi )) * exp(- (right_x/lambda) * (right_x/lambda) / 2);
    double right_norm, left_norm;

    if (std::isinf(right_x)){
        right_norm = 1;
    }
    else {right_norm = utils::normcf(right_x / lambda);}

    if (std::isinf(-left_norm)){
        left_norm = 0;
    }
    else{left_norm = utils::normcf(left_x / lambda); }


    // step 3 (a)
    if (i == 0 ){
        f = right_norm - left_norm;
        cached_results_even.push_back(f);
        return f;
    }

    // step 3 (b)
    if (i == 1){
        f = lambda * (left_pdf - right_pdf);
        cached_results_odd.push_back(f);
        return f;
    }

    // step 3 (c)
    if (i > 1){

        if (i % 2 == 0){ // even
            f = lambda * (pow(left_x, i -1) * left_pdf - pow(right_x, i-1) * right_pdf
                          + lambda* (i-1) * cached_results_even[(i-2)/2]);
            cached_results_even.push_back(f);
            return f;
        }

        if (i % 2 != 0){ // odd
            f = lambda * (pow(left_x, i -1) * left_pdf - pow(right_x, i-1) * right_pdf
                          + lambda* (i-1) * cached_results_odd[(i-3)/2]);
            cached_results_odd.push_back(f);
            return f;
        }
    }
}
