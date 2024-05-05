//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _REGRESSION_UTILS_HPP__
#define _REGRESSION_UTILS_HPP__


#include "MCLib/base_factory.hpp"
#include "MCLib/base_payoff_statistics.hpp"
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <vector>


namespace mc
{

/** \class regression
	\brief Base class for least-squares regression based methods

	*/
template<typename PPI, typename F>
class regression
{
public: 
  typedef PPI path_piece_in;//!< input noise components
  typedef boost::numeric::ublas::matrix<mc::scalar> bmatrix;//!< bost matrix of scalars
  typedef F Function;//!< type of coefficient function
  typedef std::vector<Function> fvector; //!< vector of dop::Function's
  typedef typename mc::mc_factory<path_piece_in,mc::bvector> factory;//!< particular factory
  typedef typename factory::path_in_ptr path_in_ptr;//!<pointer to input noise
  typedef typename factory::path_out path_out;//!<solution path
  typedef mc::bvector path_piece_out;//!<solution path components
	

	/** destructor
	*/
  virtual ~regression(){}

	/** operator() option pricer
	  * @param factorAt0 gird of factor values at time 0 
	  * @param bvOut vector the results to be written into
	  * @return reference to bvOut containing the regressed value 
	*/	
  virtual mc::bvector & operator()(const path_piece_out & factorAt0,
				   mc::bvector & bvOut)=0;

protected:
	/** Regression computes regression coefficients
	* @param yVals observed y values, each y value is a BVector
	* @param factors explanatory factors corresponding to observed y values
	* @param testFunctions vector of test functions
	* @return regression coefficients
	*/
  bmatrix Regression(const std::vector<mc::bvector> & yVals,
		     const std::vector<path_piece_out> & factors,
		     const fvector & testFunctions);


	/** Projection computes projected value
	* @param factor 
	* @param testFunctions vector of test functions
	* @param coefficients regression coefficients
	* @param bvOut results to be written into
	* @return regressed value (reference to bvOut)
	*/
  mc::bvector & Projection(const path_piece_out & factor,
			   const fvector & testFunctions,
			   const bmatrix & coefficients,
			   mc::bvector & bvOut);

};




}

#include "MCLib/Inl/base_regression.inl"

#endif //_REGRESSION_UTILS_HPP__
