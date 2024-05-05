//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _SOLUTION_PATH_GENERATOR_H__
#define _SOLUTION_PATH_GENERATOR_H__

#include "MCLib/type_definitions.hpp"
#include "MCLib/base_path.hpp"
#include "MCLib/base_path_generator.hpp"
#include "MCLib/base_schemes.hpp"

namespace pmc
{
/** \class solution_path_generator
	\brief solution_path_generator is a particular path_generator used for generating solution paths for SDEs

	path_piece is the type to be generated.

	The main idea is to separate the global scheme from the local one. strategy defines the global scheme
	and numerical_step the local numerical action.

	strategy defines on what scale to call the numerical_step 's (the scale could be of variable step-size,
	in which case strategy should take care of determining the step size, also tree-like (e.g. cubature tree)
	generation is also considered). strategy also determines what scale the solution path_pieces are generated
	(Accuracy) on e.g. for European type options, generating the end value is sufficent, however for path dependent options more information is
	required.

	Solving SDEs numerically is built up from numerical_step 's, taking dyadic, initial condition
	and an input in_path_piece, returning a solution path_piece.
*/
template<class PPI, class PPO, class PMO =  typename mc::path_piece_types<PPO>::path_map_by_right_end, class PMI =  typename mc::path_piece_types<PPO>::path_map >
class solution_path_generator : public pmc::path_generator<PPO,PMO>
{
public:

	typedef PPI path_piece_in;//!<input noise path piece
	typedef PPO path_piece_out;//!<solution path piece
	typedef PMO path_map_out;
	typedef PMI path_map_in;
	//typedef typename pmc::solution_path_generator<path_piece_in,path_piece_out>::path_map path_map;//!<path container member
	typedef typename pmc::path_generator<PPO,PMO>::const_iterator const_iterator;//!<iterator of path container member
	typedef mc::path<path_piece_in,path_map_in> path_in;//!< input noise path
	typedef sptr::shared_ptr<path_in> path_in_ptr;//!< pointer to input noise path
	typedef pmc::numerical_step<path_piece_in,path_piece_out> numerical_step;//!< numerical step
	typedef sptr::shared_ptr<numerical_step> numerical_step_ptr;//!<pointer to numerical step
	typedef pmc::strategy<path_piece_in,path_piece_out,path_map_out,path_map_in> strategy;//!<strategy
	typedef sptr::shared_ptr<strategy> strategy_ptr;//!<pointer to strategy

	/** constructor
	* @param pipArg sets the pointer to input path
	* @param stpArg sets the pointer to global strategy
	* @param nspArg sets the pointer to numerical_step
	*/
	solution_path_generator(path_in_ptr pipArg, strategy_ptr stpArg, numerical_step_ptr nspArg)
		: pipPath_(pipArg), stpStrat_(stpArg), nspNum_(nspArg){};

	/** operator() - generates path_pieces into the path_map if there is no piece
	* corresponding to dyArg.
	* @param dyArg dyadic interval
	* @param pmArg path_map, the path_pieces to be stored in
	* @param sArg time horizon, for time scaling purposes
	* @param ppArg global initial condition
	*/
	const_iterator operator()(const mc::dyadic & dyArg,
							path_map_out & pmArg,
							mc::scalar sArg,
							const path_piece_out & ppArg)
	{
		const_iterator pmIter=pmArg.find(dyArg);

		if(pmIter!=pmArg.end())
			return pmIter;
		else
		{
			return stpStrat_->operator()(*nspNum_,
										*pipPath_,
										dyArg,
										sArg,
										pmArg,
										ppArg);
		}
	}

	/** MaxAccuracy() - returns the max available accuracy, could be INT_MAX
	*/
	unsigned int MaxAccuracy() const
	{return stpStrat_->MaxAccuracy();}

private:
	path_in_ptr  pipPath_; //!< input noise, ptr, so can be shared between instances
	strategy_ptr stpStrat_; //!< strategy, ptr member
	numerical_step_ptr nspNum_;//!< numerical_step,ptr member

};






}





#endif //_SOLUTION_PATH_GENERATOR_H__
