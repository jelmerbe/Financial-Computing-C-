//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PAYOFF_STATISTICS_H__
#define _PAYOFF_STATISTICS_H__

#include "MCLib/type_definitions.hpp"
#include "MCLib/base_path.hpp"
#include <vector>

namespace mc
{

/** \class payoff
	\brief payoff is the base class for particular payoffs

	The key member is the operator(), taking a path and returning a vector.
*/
template<class path_piece_out, class PM 
= typename mc::path_piece_types<path_piece_out>::path_map_by_right_end
>
class payoff
{
public:
  typedef typename mc::path<path_piece_out, PM> path_out;//!<solution path

	/** destructor declared to be virtual
	  */
  virtual ~payoff(){}

	/** operator()
	* @param poArg path argument along which the payoff to be worked out
	* @param bvOut result is written into
	* @return reference to bvOut
	  */
  virtual mc::bvector & operator()(path_out & poArg, 
				   mc::bvector & bvOut)=0;

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	  */
  virtual unsigned int SizePayoff() const=0;
};


/** \class time_dependent_payoff
	\brief Abstract base class for time dependent payoffs, templated with path_piece

	*/
template<typename path_piece_out, class PM 
= typename mc::path_piece_types<path_piece_out>::path_map_by_right_end
>
class time_dependent_payoff
{
public:
  typedef mc::path<path_piece_out,PM> path_out;//!<solution path

	/** destructor
	*/
  virtual ~time_dependent_payoff(){}

	/** operator() option pricer
	  * @param pFactors (solution)path trajectory
	  * @param dTimeStep determines time dependence
	  * @param bvValue results to be written into
	  * @return reference to bvValue
	*/
  virtual mc::bvector & operator()(path_out & pFactors, 
				   const mc::dyadic & dTimeStep,
				   mc::bvector & bvValue)=0;

	/** SizePayoff()
	 * @return the size of the evaluated payoff vector
	  */
  virtual unsigned int SizePayoff() const=0;
};


/** \class statistics
	\brief statistics is the base class for particular statistics

	The class is used to compute and store statistics of MC runs (e.g. (running) mean
	 (running) variance, etc). The idea is taken
	from Mark Joshi's C++ book.
*/
class statistics
{
public:
	typedef std::vector<mc::bvector> result_type;//!<result type

	/** destructor declared to be virtual
	  */
	virtual ~statistics(){}

	/** DumpOnePayoff()
	* @param bvArg the computed payoff is taken and statistics is updated
	  */
	virtual void DumpOnePayoff(mc::bvector & bvArg)=0;

	/** GetResults()
	  * returns statistics computed so far
	 */
	virtual std::vector<mc::bvector> GetStatistics()=0;

};



}

#endif //_PAYOFF_STATISTICS_H__
