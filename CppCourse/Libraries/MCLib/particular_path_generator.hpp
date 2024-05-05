//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PARTICULAR_PATH_GENERATOR_H__
#define _PARTICULAR_PATH_GENERATOR_H__

#include "MCLib/base_path_generator.hpp"
#include "MCLib/type_definitions.hpp"
#include <limits>


namespace pmc
{


/** \class bottom_up_generator
	\brief A particular path_generator generating at a predefined finest level, then aggregates.

	This class generates increments of iDim_ dimensional Brownian motion. If a dyadic shortest than
	the predefined accuracy is passed to operator(), it throws an accuracy_limit_error.
	RndGen is assumed to have an operator(bvector &) or an operator(bvector::iterator, bvector::iterator)
	implemented writing standard normals into the argument vector/range.
	*/
template<class RndGen>
class bottom_up_generator : public pmc::path_generator<mc::bvector>
{
public:
	//typedef mc::bvector path_piece;
	typedef RndGen random_generator;//!<random number generator
	typedef typename pmc::path_generator<mc::bvector>::path_map path_map;
    typedef sptr::shared_ptr<random_generator> random_generator_ptr; //!<pointer to random generator

	/** Constructor
	* @param iDim sets the dimension
	* @param iAccuracy sets the accuracy
	* @param rgArg sets the random number generator reference
	*/
	bottom_up_generator(unsigned int iDim, unsigned int iAccuracy, random_generator_ptr & rgArg)
		: rgRand_(rgArg), iDim_(iDim), iAccuracy_(iAccuracy) {}

	/** Generates Brownian increment at a finest scale, the coarse level increments are aggregated fine level increments.
	* Note: returning const reference here is fine, it'll refer to an entry in the container.
	* @param dyArg dyadic interval, determining time step
	* @param pmArg containes the already generated increments, the new ones will be written into
	* @param sArg time horizon, used for rescaling
	* @param ppArg sets the initial value
	*/
	const_iterator operator()(const mc::dyadic & dyArg, path_map & pmArg,
		mc::scalar sArg, const path_piece & ppArg);

	/** MaxAccuracy() - returns the max available accuracy, could be INT_MAX
	*/
	unsigned int MaxAccuracy() const
	{return iAccuracy_;}

private:
	random_generator_ptr & rgRand_;//!< Random generator, shared ptr member
	unsigned int iDim_; //!< dimension of generator Brownian motion
	unsigned int iAccuracy_;//!<Max accuracy allowed.

private:
	/** Copy assignment declared but not implemented, therfore disallowed.
	*/
	bottom_up_generator & operator=(const bottom_up_generator &);
};

/** \class brownian_bridge_generator
	\brief A particular path_generator generating at a predefined finest level, then aggregates.

	This class generates increments of iDim_ dimensional Brownian motion. If a dyadic shortest than
	the predefined accuracy is passed to operator(), it throws an accuracy_limit_error.
	RndGen is assumed to have an operator(bvector &) or an operator(bvector::iterator, bvector::iterator)
	implemented writing standard normals into the argument vector/range.
	*/
template<class RndGen>
class brownian_bridge_generator : public pmc::path_generator<mc::bvector>
{
public:
	//typedef mc::bvector path_piece;
	typedef RndGen random_generator;//!< random number generator
	typedef typename pmc::path_generator<mc::bvector>::path_map path_map;
    typedef sptr::shared_ptr<random_generator> random_generator_ptr; //!<pointer to random generator

	/** Constructor
	* @param iDim sets the dimension
	* @param rgArg sets the random number generator reference
	*/
	brownian_bridge_generator(unsigned int iDim, random_generator_ptr & rgArg)
		: iDim_(iDim), rgRand_(rgArg) {}

	/** Generates Brownian increment conditionally to existing one as Brownian bridge
	* @param dyArg dyadic interval, determining time step
	* @param pmArg containes the already generated increments, the new ones will be written into
	* @param sArg time horizon, used for rescaling
	* @param ppArg sets the initial value
	* @return const iterator to path piece
	*/
	const_iterator operator()(const mc::dyadic & dyArg, path_map & pmArg,
		mc::scalar sArg, const path_piece & ppArg);

	/** MaxAccuracy() - returns the max available accuracy, could be INT_MAX
	*/
	unsigned int MaxAccuracy() const
	{return INT_MAX;}

private:
	random_generator_ptr & rgRand_;//!< Random generator, shared ptr member
	unsigned int iDim_; //!< dimension of generator Brownian motion

private:
	/** Copy assignment declared but not implemented, therfore disallowed.
	*/
	brownian_bridge_generator & operator=(const brownian_bridge_generator &);
};


}

#include "MCLib/Inl/particular_path_generator.inl"

#endif //_PARTICULAR_PATH_GENERATOR_H__
