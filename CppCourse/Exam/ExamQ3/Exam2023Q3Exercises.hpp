#ifndef _EXAM_QUESTION_3_HPP__
#define _EXAM_QUESTION_3_HPP__

#include "MCLib/base_regression.hpp"
#include "MCLib/base_payoff_statistics.hpp"
#include "MCLib/dyadic_interval.hpp"
#include "MCLib/type_definitions.hpp"
#include "MCLib/vec_ops_setup.hpp"
#include <vector>

namespace exercises
{

/** \class reference_callable
	*/
class reference_callable : public mc::regression<mc::bvector,vecop::basis_function>
{
public:
    typedef vecop::basis_function Function;//!< type of coefficient function
    typedef typename mc::regression<mc::bvector,Function> pregression;
	typedef typename pregression::path_piece_out path_piece_out;//!<solution path components
	typedef typename pregression::factory factory;//!<particular factory
	typedef typename pregression::path_out path_out;//!<solution path
	typedef typename pregression::fvector fvector;//!<vector of test functions
	typedef typename pregression::bmatrix bmatrix;//!< boost matrix of scalars
	typedef mc::time_dependent_payoff<path_piece_out> time_dependent_payoff;//!< payoff


	/** reference_callable constructor, initialises data members
	  * @param factorsAt0 grid of factor values at time 0
	  * @param iCouponScale defines the scale of coupon
	  * @param iNumericalSDEAccuracy defines the accuracy of the numerical SDE solver
	  * @param sT time to maturity scaling factor
	  * @param sR risk-free rate
	  * @param ParticularFactory factory
	  * @param v1Payoff determines cashflow C1,
	  * @param v2Payoff determines cashflow C2,
	  * @param v3Payoff determines cashflow C3,
	  * @param v4Payoff determines cashflow C4,
	  * @param testFunctions set of test functions used for projection
	*/
    reference_callable(
            const std::vector<path_piece_out> & factorsAt0,
            unsigned int iCouponScale,
            unsigned int iNumericalSDEAccuracy,
            mc::scalar sT,
            mc::scalar sR,
            factory & ParticularFactory,
            time_dependent_payoff & v1Payoff,
            time_dependent_payoff & v2Payoff,
            time_dependent_payoff & v3Payoff,
            time_dependent_payoff & v4Payoff,
            const fvector & testFunctions);

	/** operator() option pricer
	  * @param factorAt0 initial value of trajectory
	  * @param bvOut vector the results to be written into
	  * @return reference to bvOut containing the regressed value 
	*/	
	mc::bvector & operator()(const path_piece_out & factorAt0,
		mc::bvector & bvOut);


private:
	fvector m_TestFunctions;//!< vector of test functions
	bmatrix m_Coefficients;//!< collection of regression coefficents 
};






}

#endif //_EXAM_QUESTION_3_HPP__
