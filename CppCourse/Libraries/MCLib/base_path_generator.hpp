//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PATH_GENERATOR_H__
#define _PATH_GENERATOR_H__

#include "MCLib/type_definitions.hpp"
#include "MCLib/dyadic_interval.hpp"
#include <map>


namespace pmc
{

/** \class path_generator
	\brief path_generator defines the interface for particular path generators

	Abstract class.
	*/
template<class PP, class PM = typename mc::path_piece_types<PP>::path_map >
class path_generator
{
public:
	typedef PP path_piece;//!<path piece
	//typedef typename mc::path_piece_types<path_piece>::path_map path_map;//!<path container member
	typedef PM path_map; 
	typedef typename path_map::iterator iterator;//!<iterator
	typedef typename path_map::const_iterator const_iterator;//!<const iterator


	/** Constructor
	*/
	path_generator()  {}

	/** Destructor
	* Defined to be virtual, so classes can be derived publicly from path_generator.
	*/
	virtual ~path_generator() {}

	/** operator() - generates path_pieces into the path_map if there is no piece
	* corresponding to dyArg.
	* @param dyArg dyadic interval
	* @param pmArg path_map, the path_pieces to be stored in
	* @param sArg time horizon, for time scaling purposes
	* @param ppArg global initial condition
	*/
	virtual const_iterator operator()(const mc::dyadic & dyArg, path_map & pmArg, mc::scalar sArg,
		const path_piece & ppArg)=0;

	/** MaxAccuracy() - returns the max available accuracy, could be INT_MAX
	*/
	virtual unsigned int MaxAccuracy() const=0;
};



}


#endif //_PATH_GENERATOR_H__
