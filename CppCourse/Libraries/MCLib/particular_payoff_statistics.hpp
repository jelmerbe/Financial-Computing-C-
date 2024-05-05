//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PARTICULAR_PAYOFF_STATISTICS_H__
#define _PARTICULAR_PAYOFF_STATISTICS_H__


#include "MCLib/base_payoff_statistics.hpp"
#include <set>
#include <vector>

namespace pmc
{

/** \class european_calls_payoff
	\brief european_calls_payoff is a particular payoff

	european_calls_payoff is constructed from a vector of strikes and evaluates the call
	options corresponding to those strikes
*/
class european_calls_payoff : 
    public mc::payoff<mc::bvector>
{
public:
	/** constructor
	* @param bvStrikes sets the vector of strikes
	* @param ind sets the index of the underlying in the path_piece vector
	  */
  european_calls_payoff(const mc::bvector & bvStrikes, 
			unsigned int ind=0);

	/** operator()
	 * @param poArg path argument along which the payoff to be worked out
	 * @param bvOut result is written into
	 * @return reference to bvOut
	  */
  mc::bvector & operator()(path_out & poArg,
			   mc::bvector & bvOut);

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	  */
  unsigned int SizePayoff() const;

private:
  mc::bvector bvStrikes_;//!< vector of strikes
  unsigned int ind_;//!< index of the underlying in path_piece for option payoff 
};

/** \class european_puts_payoff
	\brief european_puts_payoff is a particular payoff

	european_puts_payoff is constructed from a vector of strikes and evaluates the put
	options corresponding to those strikes
*/
class european_puts_payoff : 
    public mc::payoff<mc::bvector>
{
public:
	/** constructor
	* @param bvStrikes sets the vector of strikes
	* @param ind sets the index of the underlying in the path_piece vector
	  */
  european_puts_payoff(const mc::bvector & bvStrikes,
		       unsigned int ind=0);

	/** operator()
	 * @param poArg path argument along which the payoff to be worked out
	 * @param bvOut result is written into
	 * @return reference to bvOut
	  */
  mc::bvector & operator()(path_out & poArg,
			   mc::bvector & bvOut);

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	  */
  unsigned int SizePayoff() const;

private:
  mc::bvector bvStrikes_;//!< vector of strikes
  unsigned int ind_;//!< index of the underlying in path_piece for option payoff 
};



/** \class time_dependent_call
	\brief particular time-dependent payoff, implements call payoff

	*/
class time_dependent_call : 
    public mc::time_dependent_payoff<mc::bvector>
{
public:

	/** TimeDependentCall constructor
	* @param bvArg sets the vector of strikes
	* @param index sets the index of the underlying in the path_piece vector
	  */
  time_dependent_call(const mc::bvector & bvArg,
		      mc::bvector::size_type index=0);

	/** operator()
	 * @param pFactors path argument along which the payoff to be worked out
	 * @param dTimeStep defines time(step)
	 * @param bvValue result is written into
	 * @return reference to bvValue
	  */
  mc::bvector & operator()(path_out & pFactors,
			   const mc::dyadic & dTimeStep, 
			   mc::bvector & bvValue);

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	  */
  unsigned int SizePayoff() const;

private:
  mc::bvector::size_type m_index;//!< index of the underlying in path_piece for option payoff 
  mc::bvector m_bvStrikes;//!< vector of strikes
};


/** \class time_dependent_put
	\brief particular time-dependent payoff, implements call payoff

	*/
class time_dependent_put : 
    public mc::time_dependent_payoff<mc::bvector>
{
public:

	/** TimeDependentCall constructor
	* @param bvArg sets the vector of strikes
	* @param index sets the index of the underlying in the path_piece vector
	  */
  time_dependent_put(const mc::bvector & bvArg, 
		     mc::bvector::size_type index=0);

	/** operator()
	 * @param pFactors path argument along which the payoff to be worked out
	 * @param dTimeStep defines time(step)
	 * @param bvValue result is written into
	 * @return reference to bvValue
	  */
  mc::bvector & operator()(path_out & pFactors,
			   const mc::dyadic & dTimeStep, 
			   mc::bvector & bvValue);

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	  */
  unsigned int SizePayoff() const;

private:
  mc::bvector::size_type m_index;//!< index of the underlying in path_piece for option payoff 
  mc::bvector m_bvStrikes;//!< vector of strikes
};


/** \class asian_discretely_sampled_payoff
	\brief asian_discretely_sampled_payoff is a particular payoff

	asian_discretely_sampled_payoff implements a path dependent option. The payoff
	is the max(Y_T-AvY_T,0) where AvY is the discretely sampled average of Y over time. 
	This version has a 1dim payoff, higher dim versions might be implemented
	with analogy. 
*/
class asian_discretely_sampled_payoff : 
    public mc::payoff<mc::bvector>
{
public:
	/** constructor
	* @param iSamplingAccuracy defines the scale on which the average is sampled
	* @param indY sets the index of the component to be averaged.
	*/
  asian_discretely_sampled_payoff(unsigned int iSamplingAccuracy,
				  unsigned int indY=0);
	/** operator()
	 * @param poArg path argument along which the payoff to be worked out
	 * @param bvOut result is written into
	 * @return reference to bvOut
	  */
  mc::bvector & operator()(path_out & poArg,
			   mc::bvector & bvOut);

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	 */
  unsigned int SizePayoff() const;

private:
  unsigned int iSamplingAccuracy_;//!< the average is taken over a scale of 2^{iSamplingAccuracy) steps
  unsigned int indY_;//!< the index of the component to be averaged
};

/** \class asian_continuously_sampled_payoff
	\brief asian_continuously_sampled_payoff is a particular payoff

	asian_continuously_sampled_payoff implements a path dependent option. The payoff
	is the max(Y_T-(1/T)IntY_T,0) where IntY is the (estimate) of integral Y_t dt
	assumed to be worked out by the numerical step. 
*/
class asian_continuously_sampled_payoff : 
    public mc::payoff<mc::bvector>
{
public:
	/** constructor
	* @param indY sets the index of the Y (scalar) process
	* @param indIntY sets the index of the integrated Y
	*/
  asian_continuously_sampled_payoff(unsigned int indY=0, 
				    unsigned int indIntY=0);

	/** operator()
	 * @param poArg path argument along which the payoff to be worked out
	 * @param bvOut result is written into
	 * @return reference to bvOut
	  */
  mc::bvector & operator()(path_out & poArg,
			   mc::bvector & bvOut);

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	 */
  unsigned int SizePayoff() const;
	
private:
  unsigned int indY_;//!< the index of the underlying component
  unsigned int indIntY_;//!< the index of the integral of Y
};

/** \class lookback_discretely_sampled_payoff
	\brief lookback_discretely_sampled_payoff is a particular payoff

	lookback_discretely_sampled_payoff implements a path dependent option. The payoff
	is the MaxY_T-Y_t where MaxY is the discrete-time sampled running max of Y. 
*/
class lookback_discretely_sampled_payoff : 
    public mc::payoff<mc::bvector>
{
public:
	/** constructor
	* @param iSamplingAccuracy defines the scale on which the average is sampled
	* @param indY sets the index of the component to be averaged.
	*/
  lookback_discretely_sampled_payoff(unsigned int iSamplingAccuracy,
				     unsigned int indY=0);
	/** operator()
	 * @param poArg path argument along which the payoff to be worked out
	 * @param bvOut result is written into
	 * @return reference to bvOut
	  */
  mc::bvector & operator()(path_out & poArg, 
			   mc::bvector & bvOut);

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	 */
  unsigned int SizePayoff() const;
private:
  unsigned int iSamplingAccuracy_;//!< the max is sampled over a scale of 2^{ISamplingAccuracy) steps
  unsigned int indY_;//!< the index of the component to be averaged
};


/** \class mean_variance_statistics
	\brief mean_variance_statistics is a particular class derived from statistics

	mean_variance_statistics computes running mean and variance
*/
class mean_variance_statistics : 
    public mc::statistics
{
public:
	/** constructor
	  */
  mean_variance_statistics() {}

	/** DumpOnePayoff()
	* @param bvArg the computed payoff is taken and statistics is updated
	  */
  void DumpOnePayoff(mc::bvector & bvArg);

	/** GetResults()
	  * @return the statistics computed so far
	 */
  std::vector<mc::bvector> GetStatistics();

private:
  unsigned int iNumberOfSimulations_;//!< keeps record of the number of paths simulated so far
  mc::bvector bvMean_;//!<keeps record of the running mean
  mc::bvector bvMeanOfSquares_;//!<keeps record of the running average of squares

};

}
#endif //_PARTICULAR_PAYOFF_STATISTICS_H__

