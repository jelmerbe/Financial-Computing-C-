#include "Examples_TemplateDesignPattern/Integrator.hpp"
#include <algorithm>
#include <cassert>


using namespace std;
using namespace integrator;

namespace integrator
{
    // implementation of destructor
    IntegratorBase::~IntegratorBase(){}

    // initialise ts calling the copy constructor, initialise integral by setting the size
    IntegratorBase::IntegratorBase(vector const& tsArg) : ts(tsArg), integral(ts.size())
    {}

    void IntegratorBase::initIntegral()
    {
        assert(ts.size() > 0);
        // set first entry of integral to 0
        integral[0] = 0.0;
        // loop from i = 1 (not 0!) to ts.size() -1
        for(unsigned int i = 1; i < ts.size(); i++)
        {
            // set integral[i]
            integral[i] = integral[i-1] + singleStepIntegral(i-1);
        }
    }

    double IntegratorBase::operator()(double lowerBound, double upperBound) const
    {
        vector bounds = {lowerBound, upperBound};
        vector components;
        for(double bound : bounds)
        {
            unsigned int index;
            if(bound >= ts.back())
            {
                // special case: lowerBound is larger than last element of ts
                index = ts.size()-1;
            }
            else
            {
                // general case: bound < ts.back()
                const_iterator iter = std::lower_bound(ts.cbegin(), ts.cend(), bound);
                // find the corresponding index:
                index = std::distance(ts.cbegin(), iter);
            }

            // work out lower integral
            double res = integral[index] + intermediateStepIntegral(index, bound);
            components.push_back(res);
        }
        // return upper - lower integral
        return components[1] -  components[0];
    }

    PieceWiseConstFnIntegrator::PieceWiseConstFnIntegrator(
            std::vector<double> const& tsArg,
            std::vector<double> const& ksArg)
            : IntegratorBase(tsArg), ks(ksArg)  // initialise ts, ks
    {
        assert(ts.size() == ks.size());
        // call initIntegral()
        initIntegral();
    }

    double PieceWiseConstFnIntegrator::singleStepIntegral(unsigned int i) const
    {
        // Area of rectangle
        return (ts[i+1] - ts[i]) * ks[i];
    }

    double PieceWiseConstFnIntegrator::intermediateStepIntegral(unsigned int i, double t) const
    {
        // Area of rectangle, special attention required for choosing the right k-value
        unsigned int index;
        if(t < ts[i] && i > 0)
        {
            assert(t >= ts[i-1]);
            index = i-1;
        }
        else
        {
            index = i;
            if(t >= ts[i] && i < ts.size() - 1)
            {
                assert(t < ts[i+1]);
            }
        }
        return (t - ts[i]) * ks[index];
    }

    PieceWiseLinearFnIntegrator::PieceWiseLinearFnIntegrator(
            std::vector<double> const& tsArg,
            std::vector<double> const& ksArg)
            : IntegratorBase(tsArg), ks(ksArg)  // initialise ts, ks
    {
        assert(ts.size() == ks.size());
        // call initIntegral()s
        initIntegral();
    }

    double PieceWiseLinearFnIntegrator::singleStepIntegral(unsigned int i) const
    {
        // Area of trapezoid
        return (ts[i+1] - ts[i]) * (ks[i] + ks[i+1]) * 0.5;
    }

    double PieceWiseLinearFnIntegrator::intermediateStepIntegral(unsigned int i, double t) const
    {
        double dt = (t - ts[i]);
        // handle special cases
        if(i == 0 && t < ts[i])
        {
            // area of rectangle
            return dt * ks[0];
        }
        else if (i == ts.size() - 1 && t >= ts[i])
        {
            // area of rectangle
            return dt * ks[i];
        }
        else
        {
            unsigned int idx;
            if(t < ts[i])
            {
                assert(t >= ts[i-1]);
                idx = i-1;
            }
            else
            {
                assert(t < ts[i+1]);
                idx = i;
            }
            // linearly interpolated k
            double k = (ks[idx] * (ts[idx+1] - t) + ks[idx+1] * (t - ts[idx])) / (ts[idx+1] - ts[idx]);
            // area of trapezoid
            return  dt * (ks[i] + k) * 0.5;
        }
    }

}