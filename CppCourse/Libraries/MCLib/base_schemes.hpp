//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved. 
#ifndef _SCHEMES_H__
#define _SCHEMES_H__

#include "MCLib/type_definitions.hpp"
#include "MCLib/dyadic_interval.hpp"
#include "MCLib/base_path.hpp"


namespace pmc
{


/** \class numerical_step
	\brief numerical_step is an abstract class, the particular local schemes to be derived from this

	The key (technically the only) member is operator() defining the local scheme. 
*/
template<class PPI, class PPO>
class numerical_step
{
public:
	typedef PPI path_piece_in;//!<input noise path piece
	typedef PPO path_piece_out;//!<solution path piece

	/** virtual destructor - one can derive from numerical_step safely
	*/
	virtual ~numerical_step(){}

	/** operator() - takes one numerical step
	* @param dyArg dyadic interval, step taken on 
	* @param sArg scaling factor
	* @param ppiArg input noise
	* @param oppArgIn initial condition, the result also will be written into this
	* @return reference to oppArgIn
	*/
	virtual path_piece_out & operator()(const mc::dyadic & dyArg, 
						mc::scalar sArg, 
						const path_piece_in & ppiArg, 
						path_piece_out & oppArgIn)=0; 
};



/** \class strategy
	\brief strategy class is to determine the global numerical scheme when solving SDEs

	Solving SDEs numerically is built up from numerical_step 's, taking dyadic, initial condition
	and an input path_piece, returning a solution path_piece. 
	
	strategy defines on what scale to call the numerical_step 's (the scale could be of variable step-size, 
	in which case strategy should take care of determining the step size, also tree-like (e.g. cubature tree)
	generation is also considered). 

	strategy also determines what scale the solution path_pieces are generated on e.g. for European type 
	options, generating the end value is sufficent, however 

	strategy will be used in combination with numerical_step for constrictuing particular path_generator
	classes. 
*/
//template<class PPI, class PPO>
template<class PPI,class PPO, class PMO = typename mc::path_piece_types<PPO>::path_map_by_right_end, class PMI = typename mc::path_piece_types<PPO>::path_map >
class strategy
{
public:
	typedef PMO path_map_out;
	typedef PMI path_map_in;
	typedef PPI path_piece_in;//!<input noise path piece
	typedef PPO path_piece_out;//!<solution path piece
	typedef pmc::numerical_step<path_piece_in,path_piece_out> numerical_step;//!<numerical step
	typedef typename path_map_out::const_iterator const_iterator;//!<solution path piece iterator
	typedef mc::path<path_piece_in,path_map_in> path_in;//!<input noise path
	typedef mc::path<path_piece_out,path_map_out> path_out;//!<solution path
	//typedef typename path_out::path_map path_map_out;//!<solution path container member


	/** virtual destructor - one can derive from numerical_step safely
	*/
	virtual ~strategy(){}
	
	/** operator() - executes global scheme
	* @param nsArg local schemes is executed through this
	* @param piArg input path/driving noise
	* @param dyArg defines the interval and accuracy of the saved path_piece_out
	* @param sArg scaling factor
	* @param pmArg generated path_piece_out will be written into
	* @param ppoArg global initial condition
	*/
	virtual const_iterator
		operator()(numerical_step & nsArg,
				path_in & piArg,
				const mc::dyadic & dyArg, 
				mc::scalar sArg, 
				path_map_out & pmArg, 
				const path_piece_out & ppoArg)=0;

	/** MaxAccuracy() - returns the max available accuracy, could be INT_MAX
	*/
	virtual unsigned int MaxAccuracy() const=0;

};




}


#endif //_SCHEMES_H__
