//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PARTICULAR_REGRESSIONS_HPP__
#define _PARTICULAR_REGRESSIONS_HPP__



#include "MCLib/base_regression.hpp"
#include <algorithm>



namespace pmc
{


/** \class european_option_pricer
	\brief Prices European options based on simulation and regression

	*/
template<typename PPI, typename F>
class european_option_pricer : public mc::regression<PPI,F>
{
public:
	typedef typename mc::regression<PPI,F>::path_piece_out path_piece_out;//!<input noise components
	typedef typename mc::regression<PPI,F>::Function Function;//!< type of coefficient function
	typedef typename mc::regression<PPI,F>::factory factory;//!<particular factory
	typedef typename mc::regression<PPI,F>::path_out path_out;//!<solution path
	typedef typename mc::regression<PPI,F>::fvector fvector;//!<vector of test functions
	typedef typename mc::regression<PPI,F>::bmatrix bmatrix;//!< boost matrix of scalars
	typedef mc::payoff<path_piece_out> payoff;//!< payoff

	/** european_option_pricer constructor, initialises data members
	  * @param factorsAt0 gird of factor values at time 0 
	  * @param iAccuracy accuracy of numerical SDE solver
	  * @param sT time to maturaty, rescaling factor
	  * @param sR risk-free interest rate
	  * @param ParticularFactory factory
	  * @param ParticularPayoff payoff function object
	  * @param testFunctions set of test functions uded for projection
	  */
	european_option_pricer(const std::vector<path_piece_out> & factorsAt0,
						   unsigned int iAccuracy,
						   mc::scalar sT,
						   mc::scalar sR,
						   factory & ParticularFactory,
						   payoff & ParticularPayoff,
						   const fvector & testFunctions);
	
	/** operator() option pricer
	  * @param factorAt0 gird of factor values at time 0 
	  * @param bvOut vector the results to be written into
	  * @return reference to bvOut containing the regressed value 
	*/	
	mc::bvector & operator()(const path_piece_out & factorAt0, mc::bvector & bvOut);

private:
	fvector m_TestFunctions;//!< vector of test functions
	bmatrix m_Coefficients;//!< matrix of regression coefficients

};


/** \class bermudan_option_pricer
	\brief Least-squares regression based Bermudan option pricer

	*/
template<typename PPI,typename F> 
class bermudan_option_pricer : public mc::regression<PPI,F>
{
public:
	typedef typename mc::regression<PPI,F>::path_piece_out path_piece_out;//!<input noise components
	typedef F Function;//!< type of coefficient function
	typedef typename mc::regression<PPI,F>::factory factory;//!<particular factory
	typedef typename mc::regression<PPI,F>::path_out path_out;//!<solution path
	typedef typename mc::regression<PPI,F>::fvector fvector;//!<vector of test functions
	typedef typename mc::regression<PPI,F>::bmatrix bmatrix;//!< boost matrix of scalars
	typedef mc::time_dependent_payoff<path_piece_out> time_dependent_payoff;//!<time dependent payoff

	/** BermudanOptionPricer constructor, initialises data members
	  * @param factorsAt0 gird of factor values at time 0 
	  * @param iNumericalSDEAccuracy defines the accuracy of the numerical SDE solver
	  * @param iBermudanScaleAccuracy defines the accuracy of the Bermudan pricer (log_2 of number of exercise dates)
	  * @param sT time to maturity scaling factor
	  * @param sR risk-free rate
	  * @param ParticularFactory factory
	  * @param ParticularTimedependentPayoff defines payoff
	  * @param testFunctions set of test functions uded for projection
	  * @return regressed value 
	*/
	bermudan_option_pricer(const std::vector<path_piece_out> & factorsAt0,
			       unsigned int iNumericalSDEAccuracy,
			       unsigned int iBermudanScaleAccuracy,
			       mc::scalar sT,
			       mc::scalar sR,
			       factory & ParticularFactory,
			       time_dependent_payoff & ParticularTimedependentPayoff,
			       const fvector & testFunctions);
	
	/** operator() option pricer
	  * @param factorAt0 gird of factor values at time 0 
	  * @param bvOut vector the results to be written into
	  * @return reference to bvOut containing the regressed value 
	*/	
	mc::bvector & operator()(const path_piece_out & factorAt0, mc::bvector & bvOut);


private:
	fvector m_TestFunctions;//!< vector of test fucntions
	bmatrix m_Coefficients;//!< matrix of regression coefficients (corresponding to initial time)

};


}

#include "MCLib/Inl/particular_regressions.inl"

#endif //_PARTICULAR_REGRESSIONS_HPP__
