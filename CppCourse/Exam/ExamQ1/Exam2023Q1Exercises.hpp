#ifndef _EXAM2023_Q1_EXERCISES_H__
#define _EXAM2023_Q1_EXERCISES_H__

#include <functional>
#include <utility>


namespace exercises
{

    class RateParameters
    {
    public:
        typedef std::function<double (double)> DiscountFunction;
        double beta;
        double sigma;
        DiscountFunction discountFunction;
    };

    std::pair<double, double> MeanStdevRate(
            const RateParameters& rateParameters,
            double T
            );

    class BondParameters
    {
    public:
        double T1, T2;
    };

    double BondPrice(
        double r,
        const BondParameters& bondParameters,
        const RateParameters& rateParameters);

    typedef std::function<double (double)> Payoff;

    std::pair<double, double> BondOptionMonteCarlo(
            const RateParameters & rateParameters,
            const BondParameters & bondParameters,
            const Payoff & payoff,
            unsigned int sampleSize
            );

}

#endif //_EXAM2023_Q1_EXERCISES_H__
