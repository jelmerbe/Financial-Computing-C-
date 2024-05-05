//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PARTICULAR_FACTORY_H__
#define _PARTICULAR_FACTORY_H__

#include "MCLib/base_factory.hpp"
#include "MCLib/type_definitions.hpp"
#include "MCLib/particular_random_generator.hpp"
#include "MCLib/base_solution_path_generator.hpp"
#include "MCLib/particular_path_generator.hpp"
#include "MCLib/particular_numerical_step.hpp"
#include "MCLib/particular_strategy.hpp"


namespace pmc
{


/** \class simple_mc_factory
	\brief simple_mc_factory is a particular mc_factory

	This factory generates BM input paths with

	- bottom-up generator

	and output paths with

	- Euler numerical step

	- equal step size global strategy
	*/
template<class VO_setup>
class simple_mc_factory : public mc::mc_factory<mc::bvector,mc::bvector>
{
public:
	typedef typename mc::mc_factory<mc::bvector,mc::bvector>::path_map_in path_map_in;
	typedef typename mc::mc_factory<mc::bvector,mc::bvector>::path_map_out path_map_out;

	typedef typename VO_setup::Vec_ops Vec_ops;//!<vector of vector fields
	typedef path_in::path_generator_ptr path_generator_ptr;//!<pointer to path generator
	typedef pmc::normal_random_generator random_generator;//!<random number generator
	typedef random_generator::result_type result_type;//!<result type of the rand generator
	//==============================================================================
	//PARTICULAR PATH GENERATOR FOR INPUT PATHS
    typedef sptr::shared_ptr<random_generator> random_generator_ptr; //!<pointer to random generator
	typedef pmc::bottom_up_generator<random_generator> particular_path_generator;//!<particular input noise generator
	//==============================================================================
	typedef pmc::numerical_step<path_piece_in,path_piece_out> numerical_step;//!<base numerical step
	typedef sptr::shared_ptr<numerical_step> numerical_step_ptr;//!<pointer to base numerical step
	//==============================================================================
	//PARTICULAR NUMERICAL STEP
	typedef pmc::num::euler_numerical_step<Vec_ops> particular_numerical_step;//!<particular numerical step
	//==============================================================================
	typedef pmc::strategy<path_piece_in,path_piece_out> strategy;//!<base strategy
	typedef sptr::shared_ptr<strategy> strategy_ptr;//!<pointer to base strategy
	//==============================================================================
	//PARTICULAR STRATEGY
	typedef pmc::strat::equal_step_strategy<path_piece_in,path_piece_out> particular_strategy;//!<particular strategy
	//==============================================================================
	typedef typename mc::mc_factory<mc::bvector,mc::bvector>::path_out path_out;//!<solution path
	typedef path_out::path_generator_ptr path_generator_out_ptr;//!<pointer to input noise generator
	typedef pmc::solution_path_generator<path_piece_in,path_piece_out> solution_path_generator;//!<solution path generator



	/** constructor
	* @param vosArg sets the equation
	* @param seed sets the seed of the random number generator
	*/
	simple_mc_factory(VO_setup & vosArg, result_type seed=123795)
	: voEquation_(vosArg.operator()()), nrgRandomGenerator_(sptr::make_shared<random_generator>(seed))
	{iDim_=vosArg.GetDim();}

	/** GetNewPathIn
	* Generates a new input path
	* @param iAccuracyLimit sets the scale for the input path
	* @param sT time horizon
	*/
	path_in GetNewPathIn(unsigned int iAccuracyLimit, mc::scalar sT);

	/** GetNewPathInPtr
	* Generates a shared_ptr to a new input path
	* @param iAccuracyLimit sets the scale for the input path
	* @param sT time horizon
	*/
	path_in_ptr GetNewPathInPtr(unsigned int iAccuracyLimit, mc::scalar sT);

	/** GetNewPathOut
	* Generates a new output path, with a new input path inside (independent from existing input paths)
	* @param iAccuracyLimit sets the scale for the local steps and the accuracy of the input paths
	* @param iGlobalAccuracy sets the global scale for the output paths
	* @param ppoArg global initial condition
	* @param sT time horizon
	*/
	path_out GetNewPathOut(unsigned int iAccuracyLimit,
						unsigned int iGlobalAccuracy,
						path_piece_out ppoArg,
						mc::scalar sT);

	/** GetNewPathOut
	* Generates a new output path, with an already existing input path
	* @param pipArg pointer to an input path
	* @param iAccuracyLimit sets the scale for the local steps
	* @param iGlobalAccuracy sets the global scale for the output paths
	* @param ppoArg global initial condition
	* @param sT time horizon
	*/
	path_out GetNewPathOut(path_in_ptr pipArg,
						unsigned int iAccuracyLimit,
						unsigned int iGlobalAccuracy,
						path_piece_out ppoArg,
						mc::scalar sT);


private:
	Vec_ops voEquation_;//!<vector of vector fields
	unsigned int iDim_;//!<dimension
	random_generator_ptr nrgRandomGenerator_;//!<random number generator
};



/** \class general_mc_factory
	\brief general_mc_factory is a particular mc_factory

	This factory generates input paths with templated

	- path generator - PPathGen ::random_generator member type assumed with a certain fixed constructor

	and output paths with templated

	- numerical step - PNumStep, ::vector_fields member type assumed

	- global strategy - PStrategy

	*/
template<class PPI,
		 class PPO,
		 class PPathGen,
		 class VO_setup,
		 class PNumStep,
		 class PStrategy,
		 class PMO = typename mc::path_piece_types<PPO>::path_map_by_right_end, 
		 class PMI = typename mc::path_piece_types<PPO>::path_map>
class general_mc_factory : public mc::mc_factory<PPI,PPO,PMO,PMI>
{
public:
    typedef typename mc::mc_factory<PPI,PPO,PMO,PMI>::path_piece_in path_piece_in;//!<input noise path piece
	typedef typename mc::mc_factory<PPI,PPO,PMO,PMI>::path_piece_out path_piece_out;//!<solution path piece
	typedef typename mc::mc_factory<PPI,PPO,PMO,PMI>::path_in path_in;//!<input noise path
	typedef typename mc::mc_factory<PPI,PPO,PMO,PMI>::path_out path_out;//!<solution path
	typedef typename mc::mc_factory<PPI,PPO,PMO,PMI>::path_in_ptr path_in_ptr;//!<pointer to input noise
	typedef typename mc::mc_factory<PPI,PPO,PMO,PMI>::path_out_ptr path_out_ptr;//!<pointer to solution path
	typedef typename path_in::path_generator_ptr path_generator_ptr;//!<pointer to input path generator
	typedef typename PNumStep::vector_fields Vec_ops;//!<vector of vector fields
	typedef typename PPathGen::random_generator random_generator;//!<random generator
	typedef typename random_generator::result_type result_type;//!<result type of rand generator
	//==============================================================================
	//PARTICULAR PATH GENERATOR FOR INPUT PATHS
    typedef sptr::shared_ptr<random_generator> random_generator_ptr; //!<pointer to random generator
	typedef PPathGen particular_path_generator;//!<particular path generator
	//==============================================================================
	typedef pmc::numerical_step<path_piece_in,path_piece_out> numerical_step;//!<base numerical step
	typedef sptr::shared_ptr<numerical_step> numerical_step_ptr;//!<pointer to numerical step
	//==============================================================================
	//PARTICULAR NUMERICAL STEP
	typedef PNumStep particular_numerical_step;//!<particular numerical step
	//==============================================================================
	typedef pmc::strategy<path_piece_in,path_piece_out,PMO,PMI> strategy;//!<base strategy
	typedef sptr::shared_ptr<strategy> strategy_ptr;//!<pointer to base strategy
	//==============================================================================
	//PARTICULAR STRATEGY
	typedef PStrategy particular_strategy;//!<particular strategy
	//==============================================================================
	typedef typename path_out::path_generator_ptr path_generator_out_ptr;//!<pointer to input noise generator
	typedef pmc::solution_path_generator<path_piece_in,path_piece_out> solution_path_generator;//!<solution path generator



	/** constructor
	* @param vosArg sets the equation
	* @param seed sets the seed of the random number generator
	*/
	general_mc_factory(VO_setup & vosArg, result_type seed=123795)
		: voEquation_(vosArg.operator()()), nrgRandomGenerator_((sptr::make_shared<random_generator>(seed)))
		{iDim_=vosArg.GetDim();}

	/** GetNewPathIn
	* Generates a new input path
	* @param iAccuracyLimit sets the scale for the input path
	* @param sT time horizon
	*/
	path_in GetNewPathIn(unsigned int iAccuracyLimit, mc::scalar sT);

	/** GetNewPathInPtr
	* Generates a shared_ptr to a new input path
	* @param iAccuracyLimit sets the scale for the input path
	* @param sT time horizon
	*/
	path_in_ptr GetNewPathInPtr(unsigned int iAccuracyLimit, mc::scalar sT);

	/** GetNewPathOut
	* Generates a new output path, with a new input path inside (independent from existing input paths)
	* @param iAccuracyLimit sets the scale for the local steps and the accuracy of the input paths
	* @param iGlobalAccuracy sets the global scale for the output paths
	* @param ppoArg global initial condition
	* @param sT time horizon
	*/
	path_out GetNewPathOut(unsigned int iAccuracyLimit,
						unsigned int iGlobalAccuracy,
						path_piece_out ppoArg,
						mc::scalar sT);

	/** GetNewPathOut
	* Generates a new output path, with an already existing input path
	* @param pipArg pointer to an input path
	* @param iAccuracyLimit sets the scale for the local steps
	* @param iGlobalAccuracy sets the global scale for the output paths
	* @param ppoArg global initial condition
	* @param sT time horizon
	*/
	path_out GetNewPathOut(path_in_ptr pipArg,
						unsigned int iAccuracyLimit,
						unsigned int iGlobalAccuracy,
						path_piece_out ppoArg,
						mc::scalar sT);


private:
	Vec_ops voEquation_;//!<vector of vector fields
	unsigned int iDim_;//!<dimension
	random_generator_ptr nrgRandomGenerator_;//!<random number generator
};




}





#include "MCLib/Inl/particular_factory.inl"

#endif //_PARTICULAR_FACTORY_H__
