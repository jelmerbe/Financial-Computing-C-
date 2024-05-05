
#ifndef _UTILS_FUNCTIONS_H__
#define _UTILS_FUNCTIONS_H__

#include <vector>
#include <iostream>
#include <fstream>

namespace utils {
    void NormalDist(std::vector<double> &vArg);

    double NormalDist();

    void ResetGenerator();

    double normcf(double dArg);

/** Black-Scholes option price
	  * @param dS0 initial stock price
	  * @param dK strike
	  * @param dT time to maturity
	  * @param dR riskfree rate
	  * @param dSigma sigma
	  * @param isCall true if call, false if put
	  * @return inf norm of dVec
	  */
    double BSOptionPrice(double dS0,
                         double dK,
                         double dT,
                         double dR,
                         double dSigma,
                         bool isCall = true);

    double BSDelta(double dS0,
                   double dK,
                   double dT,
                   double dR,
                   double dSigma,
                   bool isCall=true);

    double BSGamma(double dS0,
                   double dK,
                   double dT,
                   double dR,
                   double dSigma,
                   bool isCall=true);

    double d1_fn(double s0, double k, double t, double r, double sigma);

    double d2_fn(double s0, double k, double t, double r, double sigma);

    struct MyStream
    {
        MyStream(std::fstream & myfile_) : myfile(myfile_) {}
        std::fstream & myfile;
    };


    template<class T>
    MyStream & operator<<(MyStream & stream, T const& arg)
    {
        std::cout << arg;
        stream.myfile << arg;
        return stream;
    }
}
#endif //_UTILS_FUNCTIONS_H__
