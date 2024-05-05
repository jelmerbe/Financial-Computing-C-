//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PATH_H__
#define _PATH_H__

#include <map>
#include "MCLib/type_definitions.hpp"
#include "MCLib/dyadic_interval.hpp"
#include "MCLib/base_path_generator.hpp"


namespace mc
{

/** \class path
	\brief path is a class used to model random trajectories

	From outside the class looks as a read-only container of data of type path_piece.
	[path_piece] is the type of input noise pieces, which could be increments, increments
	and areas, signature upto certain level, etc. The container is of type map,
	assigning path_piece data to dyadic intervals.
	The actual path_piece data generation is done through the member of type path_generator.
	Accuracy defines the fineness of the time scale for which path_pieces can be returned. Note that
	accuracy might be INT_MAX (see Levy construction based path generation).
	*/
template<class path_piece, class PM=typename mc::path_piece_types<path_piece>::path_map >
class path
{
public:

	
	//typedef typename path_piece_types<path_piece>::path_map path_map;//!<path container type
	typedef PM path_map;
	typedef typename path_map::iterator iterator;//!<iterator of path_map
	typedef typename path_map::const_iterator const_iterator;//!<const iterator of path_map
	typedef sptr::shared_ptr<pmc::path_generator<path_piece,path_map> > path_generator_ptr;//!<pointer to path generator

	/** Constructor
	* @param pgArg sets the pgGenerator
	* @param sArg sets the time horizon
	*/
	path(pmc::path_generator<path_piece,path_map> * pgArg, scalar sArg) : sT_(sArg), pgpGenerator_(pgArg) {}

	/** Constructor
	* @param pgArg sets the pgGenerator
	* @param sArg sets the time horizon
	* @param ppArg sets the initial value
	*/
	path(pmc::path_generator<path_piece,path_map> * pgArg, scalar sArg, const path_piece & ppArg)
		: sT_(sArg), ppInitialValue_(ppArg), pgpGenerator_(pgArg) {}

	/** Constructor
	* @param pgArg sets the pgGenerator
	* @param sArg sets the time horizon
	*/
	path(path_generator_ptr pgArg, scalar sArg) : sT_(sArg), pgpGenerator_(pgArg) {}

	/** Constructor
	* @param pgArg sets the pgGenerator
	* @param sArg sets the time horizon
	* @param ppArg sets the initial value
	*/
	path(path_generator_ptr pgArg, scalar sArg, const path_piece & ppArg)
		: sT_(sArg), ppInitialValue_(ppArg), pgpGenerator_(pgArg) {}

	/** Copy constructor
	* Copies members
	* @param ipArg argument to copy
	*/
	path(const path<path_piece,path_map> & ipArg) : sT_(ipArg.sT_), 
					ppInitialValue_(ipArg.ppInitialValue_), 
					pmContainer_(ipArg.pmContainer_), 
					pgpGenerator_(ipArg.pgpGenerator_)
	{
		//pmContainer_.insert(ipArg.pmContainer_.begin(), ipArg.pmContainer_.end());
	}

	/** Copy assignment
	* Copies members
	* @param ipArg argument to copy
	* @return reference to this
	*/
	path<path_piece,path_map> & operator=(const path<path_piece,path_map> & ipArg)
	{
		sT_=ipArg.sT_;
		pgpGenerator_=ipArg.pgpGenerator_;
		pmContainer_=ipArg.pmContainer_;
		ppInitialValue_=ipArg.ppInitialValue_;
		return *this;
	}

	/** Destructor
	*/
	~path() {}

	/** Returns const_iterator to the relevant pair<dyadic,path_piece>. If the entry does not exists
	* and cannot be generated, the pgGenerator_ should return pmContainer_.end();
	* @param dyArg dyadic interval
	* @return const_iterator to the relevant pair<dyadic,path_piece> or end()
	*/
	const_iterator find(const dyadic & dyArg)
	{
		return pgpGenerator_->operator()(dyArg,pmContainer_,sT_,ppInitialValue_);
	}

	/** Returns iterator to end() of the container.
	*/
	const_iterator end()
	{
		return pmContainer_.end();
	}

	/** TimeHorizon() - returns sT_
	*/
	scalar TimeHorizon() const {return sT_;}

	/** InitialValue() - returns ppInitialValue_
	*/
	const path_piece & InitialValue() const {return ppInitialValue_;}

	/** MaxAccuracy() - returns the max available accuracy, could be INT_MAX
	*/
	unsigned int MaxAccuracy() const {return pgpGenerator_->MaxAccuracy();}

private://data members
	scalar sT_;//!< time horizon
	path_piece ppInitialValue_; //<! initial state of the path
	path_map pmContainer_;//!< contains the already generated PP's
	path_generator_ptr pgpGenerator_;//!< ptr to generator, [const PP & op()(const dyadic &, path_map &, scalar) const] member assumed
};





}

#endif //_INPUT_PATH_H__
