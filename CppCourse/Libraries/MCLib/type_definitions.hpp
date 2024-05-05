//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.

/*! \mainpage Monte Carlo Project
 *
 * \section intro_sec Introduction
 *
 * Monte Carlo Project was created for teaching purposes at the Mathematical
 * Intitute, University of Oxford in 2009.
 *
 * The code is written by Lajos Gergely Gyurko. Some ideas of the RDE lib coordinated by
 * Terry Lyons in 2005-2006 has been reused.
 *
 *
 */


#ifndef _TYPE_DEFINITIONS_H__
#define _TYPE_DEFINITIONS_H__

#ifdef MSC_VER
#pragma warning(disable:4996)
#endif


#if __cplusplus >= 201402L  || (defined(_MSC_VER) && _MSC_VER >= 1916)
    #include <memory>
    #include <cstddef>
    namespace sptr = std;
#else
    #include <boost/shared_ptr.hpp>
    #include <boost/enable_shared_from_this.hpp>
    namespace sptr = boost;
#endif

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <limits>
#include <map>

namespace mc //! namespace holding the classes defining the abstract high level framework
{}

namespace pmc //! namespace holding particular classes derived from the abstract framework and holding classes not part of the high level interface
{}

namespace mc
{

/** class error_accuracy_mismatch
	/brief created for exception handling
*/
class error_accuracy_mismatch
{};

typedef double scalar;//!<scalar type
typedef boost::numeric::ublas::vector<scalar> bvector;//!<boost vector of scalars


class dyadic;

class dyadicLessByRightEnd;

/** \class path_piece_types
	\brief struct holding type definitions

	These types are used in path and path_generator
*/
template<class path_piece>
struct path_piece_types
{
	typedef typename std::map<mc::dyadic,path_piece> path_map;//!<path container member
	typedef typename path_map::iterator iterator;//!<iterator of path_map
	typedef typename path_map::const_iterator const_iterator;//!<const iterator of path_map

	typedef typename std::map<mc::dyadic,path_piece,dyadicLessByRightEnd> path_map_by_right_end;//!<path container member
};


}

#endif //_TYPE_DEFINITIONS_H__

