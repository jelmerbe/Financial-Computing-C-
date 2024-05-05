//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _FACTORY_H__
#define _FACTORY_H__

#include "MCLib/type_definitions.hpp"
#include "MCLib/base_path.hpp"

namespace mc
{


/** \class mc_factory
	\brief mc_factory is the base class for setting up mc path generators

	The particular mc_factory's set up input and output paths.
	*/
template<class PPI,class PPO, class PMO = typename mc::path_piece_types<PPO>::path_map_by_right_end, class PMI = typename mc::path_piece_types<PPO>::path_map >
class mc_factory
{
public:
	typedef PPI path_piece_in;//!<input noise path piece
	typedef PPO path_piece_out;//!<solution path piece
	typedef mc::path<path_piece_in,PMI> path_in;//!<input noise path
	typedef mc::path<path_piece_out,PMO> path_out;//!<solution path
	typedef PMI path_map_in;
	typedef PMO path_map_out;
	typedef sptr::shared_ptr<path_in> path_in_ptr;//!<pointer to input noise path
	typedef sptr::shared_ptr<path_out> path_out_ptr;//!<pointer to solution path

	/** Destructor
	* declared virtual
	*/
	virtual ~mc_factory(){}

	/** GetNewPathIn
	* Generates a new input path
	* @param iAccuracyLimit sets the scale for the input path
	* @param sT time horizon
	* @return a new input path
	*/
	virtual path_in GetNewPathIn(unsigned int iAccuracyLimit, mc::scalar sT)=0;

	/** GetNewPathInPtr
	* Generates a shared_ptr to a new input path
	* @param iAccuracyLimit sets the scale for the input path
	* @param sT time horizon
	* @return a shared_ptr to a new input path
	*/
  virtual path_in_ptr GetNewPathInPtr(unsigned int iAccuracyLimit, 
				      mc::scalar sT)=0;

	/** GetNewPathOut
	* Generates a new output path, with a new input path inside (independent from existing input paths)
	* @param iAccuracyLimit sets the scale for the local steps and the accuracy of the input paths
	* @param iGlobalAccuracy sets the global scale for the output paths
	* @param ppoArg global initial condition
	* @param sT time horizon
	* @return a new output path
	*/
  virtual path_out GetNewPathOut(unsigned int iAccuracyLimit,
				 unsigned int iGlobalAccuracy,
				 path_piece_out ppoArg,
				 mc::scalar sT)=0;

	/** GetNewPathOut
	* Generates a new output path, with an already existing input path
	* @param pipArg pointer to an input path
	* @param iAccuracyLimit sets the scale for the local steps
	* @param iGlobalAccuracy sets the global scale for the output paths
	* @param ppoArg global initial condition
	* @param sT time horizon
	* @return a new output path
	*/
  virtual path_out GetNewPathOut(path_in_ptr pipArg,
				 unsigned int iAccuracyLimit,
				 unsigned int iGlobalAccuracy,
				 path_piece_out ppoArg,
				 mc::scalar sT)=0;

};

}

#endif //_FACTORY_H__
