#include "Utils/UtilityFunctions.hpp"
#include <boost/math/constants/constants.hpp>
#include <cmath>
#include <limits>

using namespace std;

namespace utils {

    double normcf(double dArg)
    {
        if(isinf(dArg))
        {
            if(dArg < 0.0)
            {
                return -1.0;
            }
            return 1.0;
        }
        return 0.5 * (1 + erf(dArg / sqrt(2.0)));
    }

    double BSOptionPrice(double dS0,
                         double dK,
                         double dT,
                         double dR,
                         double dSigma,
                         bool isCall)
    {
        if (dK < 1.0e-14)
            return dS0;

        double d1 = d1_fn(dS0, dK, dT, dR, dSigma);
        double d2 = d2_fn(dS0, dK, dT, dR, dSigma);
        double pv;
        if (isCall) {
            pv = dS0 * normcf(d1) - exp(-dR * dT) * dK * normcf(d2);
        } else {
            pv = exp(-dR * dT) * dK * (1 - normcf(d2)) - dS0 * (1 - normcf(d1));
        }
        return pv;
    }

    double BSDelta(double dS0,
                 double dK,
                 double dT,
                 double dR,
                 double dSigma,
                 bool isCall){
        double d1=d1_fn(dS0,dK,dT,dR,dSigma);
        if(isCall)
            return normcf(d1);
        else
            return normcf(d1)-1.0;
    }

    double BSGamma(double dS0,
                 double dK,
                 double dT,
                 double dR,
                 double dSigma,
                 bool isCall){
        double d1=d1_fn(dS0,dK,dT,dR,dSigma);
        double dPi = boost::math::constants::pi<double>();
        return exp(-d1*d1*0.5)/(sqrt(2.0*dPi)*dS0*sqrt(dT)*dSigma);
    }


    double d1_limit(double dS0, double dK, double dT, double dR)
    {
        double diff = dS0 - dK * exp(- dR * dT);
        if(diff < 0.0)
        {
            return -numeric_limits<double>::infinity();
        }
        else if(diff > 0.0)
        {
            return numeric_limits<double>::infinity();
        }
        else
        {
            return 0.0;
        }
    }

    double d1_gen(double dS0, double dK, double dT, double dR, double dSigma, double sigmaSqrtT)
    {
        return (log(dS0 / dK) + (dR + dSigma * dSigma * 0.5) * dT) / sigmaSqrtT;
    }

    double d1_fn(double dS0, double dK, double dT, double dR, double dSigma)
    {
        double sigmaSqrtT = dSigma * sqrt(dT);
        if(sigmaSqrtT < 1.0e-14){
            return d1_limit(dS0, dK, dT, dR);
        }
        else
        {
            return d1_gen(dS0, dK, dT, dR, dSigma, sigmaSqrtT);
        }
    }

    double d2_fn(double dS0, double dK, double dT, double dR, double dSigma)
    {
        double sigmaSqrtT = dSigma * sqrt(dT);
        if(sigmaSqrtT < 1.0e-14){
            return d1_limit(dS0, dK, dT, dR);
        }
        else
        {
            return d1_gen(dS0, dK, dT, dR, dSigma, sigmaSqrtT) - dSigma * sqrt(dT);
        }
    }
}
