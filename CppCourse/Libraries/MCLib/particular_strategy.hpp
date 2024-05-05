//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PARTICULAR_STRATEGY_H__
#define _PARTICULAR_STRATEGY_H__

#ifdef MSC_VER
#pragma warning(disable:4018)
#endif

#include "MCLib/base_schemes.hpp"

namespace pmc
{

namespace strat //! namespace holding particular strategy classes
{

/** \class equal_step_strategy
	\brief equal_step_strategy is a particular strategy, takes steps of predefined length

*/
template<class PPI, class PPO, class PMO = typename mc::path_piece_types<PPO>::path_map_by_right_end, 
		 class PMI = typename mc::path_piece_types<PPO>::path_map>
class equal_step_strategy : public pmc::strategy<PPI,PPO,PMO,PMI>
{
public:
    typedef PPI path_piece_in;//!<inpute noise path piece
	typedef PPO path_piece_out;//!<solution path piece
	typedef typename pmc::strategy<path_piece_in,path_piece_out,PMO,PMI>::const_iterator const_iterator;//!<solution path piece iterator
	typedef typename pmc::strategy<path_piece_in,path_piece_out,PMO,PMI>::numerical_step numerical_step;//!<numerical step
	typedef typename pmc::strategy<path_piece_in,path_piece_out,PMO,PMI>::path_in path_in;//!<input noise path
	typedef typename pmc::strategy<path_piece_in,path_piece_out,PMO,PMI>::path_out path_out;//!<solution path
	typedef typename pmc::strategy<path_piece_in,path_piece_out,PMO,PMI>::path_map_out path_map_out;//!<solution path conatiner member


	/** Constructor
	* @param iGlobalAccuracy sets the global accuracy, i.e. the accuracy of dyadics in path_map_out
	* @param iLocalStepAccuracy sets the local step's accuracy
	*/
	equal_step_strategy(unsigned int iGlobalAccuracy, unsigned int iLocalStepAccuracy)
			: iGlobalAccuracy_(iGlobalAccuracy),
			  iLocalStepAccuracy_(std::max(iGlobalAccuracy,iLocalStepAccuracy)) {}

	/** operator() - executes global scheme
	* @param nsArg local schemes is executed through this
	* @param piArg input path/driving noise
	* @param dyArg defines the interval and accuracy of the saved path_piece_out
	* @param sArg scaling factor
	* @param pmArg generated path_piece_out will be written into
	* @param ppoArg global initial condition
	*/
	virtual const_iterator operator()(numerical_step & nsArg,
				path_in & piArg,
				const mc::dyadic & dyArg,
				mc::scalar sArg,
				path_map_out & pmArg,
				const path_piece_out & ppoArg);

	/** MaxAccuracy() - returns the max available accuracy, could be INT_MAX
	*/
	unsigned int MaxAccuracy() const
	{return iGlobalAccuracy_;}

private:
	unsigned int iGlobalAccuracy_; //!< accuracy of the path_piece_out elements saved in path_map
	unsigned int iLocalStepAccuracy_;//!< accuracy of the local step

};

}

}

#include "MCLib/Inl/particular_strategy.inl"

#endif //_PARTICULAR_STRATEGY_H__
