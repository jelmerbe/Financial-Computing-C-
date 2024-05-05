
#ifndef _INTEGRATOR_HPP__
#define _INTEGRATOR_HPP__

#include <vector>

namespace integrator
{

    class IntegratorBase
    {
    public:
        typedef std::vector<double> vector;
        typedef vector::const_iterator const_iterator;

        /**
         * Destructor
         */
        virtual ~IntegratorBase();

        /**
         * Constructor, initialises ts
         * @param tsArg non-empty vector of t_i's
         */
        IntegratorBase(vector const& tsArg);

        /**
         * Function operator
         * @param lowerBound
         * @param upperBound
         * @return Integral between lowerBound and upperBound
         */
        double operator()(double lowerBound, double upperBound) const;

    protected:

        /**
         * Sets value to its integral member using singleStepIntegral()
         */
        void initIntegral();

        /**
         * Pure virtual method.
         * @param i index, expected to be less than ts.size()
         * @return Integral between t_i and t_{i+1}
         */
        virtual double singleStepIntegral(unsigned int i) const=0;
        /**
         * Pure virtual method.
         * @param i index, expected to be less than ts.size()
         * @param t t
         * @return Integral between t and t_i
         */
        virtual double intermediateStepIntegral(unsigned int i, double t) const=0;

        vector ts, integral;
    };

    class PieceWiseConstFnIntegrator : public IntegratorBase
    {
    public:

        /** Constructor
         * initialises data members
         * @param tsArg vector of t_i's
         * @param ksArg vector of k_i's
         */
        PieceWiseConstFnIntegrator(
                std::vector<double> const& tsArg,
                std::vector<double> const& ksArg);

    protected:
        double singleStepIntegral(unsigned int i) const;

        double intermediateStepIntegral(unsigned int i, double t) const;

    private:
        std::vector<double> ks;
    };

    class PieceWiseLinearFnIntegrator : public IntegratorBase
    {
    public:

        /** Constructor
         * initialises data members
         * @param tsArg vector of t_i's
         * @param ksArg vector of k_i's
         */
        PieceWiseLinearFnIntegrator(
                std::vector<double> const& tsArg,
                std::vector<double> const& ksArg);

    protected:
        double singleStepIntegral(unsigned int i) const;

        double intermediateStepIntegral(unsigned int i, double t) const;

    private:
        std::vector<double> ks;
    };

  
}

#endif //_INTEGRATOR_HPP__
