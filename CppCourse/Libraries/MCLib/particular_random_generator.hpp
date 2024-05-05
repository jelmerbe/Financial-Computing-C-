//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PARTICULAR_RANDOM_GENERATOR_H__
#define _PARTICULAR_RANDOM_GENERATOR_H__

#if __cplusplus > 199711L
  #include <random>
  #include <functional>
	typedef std::mt19937 base_generator_type;//!< generator engine
	typedef std::mt19937::result_type result_type;
	typedef std::normal_distribution<> normal_distribution;
#else
  #include <boost/random/mersenne_twister.hpp>
  #include <boost/random/variate_generator.hpp>
  #include <boost/random/normal_distribution.hpp>
	typedef boost::mt19937 base_generator_type;//!< generator engine
    typedef boost::mt19937::result_type result_type;
	typedef boost::normal_distribution<> normal_distribution;
#endif

#include <algorithm>
#include <vector>
#include "MCLib/type_definitions.hpp"

namespace pmc
{

/** \class normal_random_generator
	\brief A particular random_generator generating standard normals

	The operator() takes a reference to a bvector and fills it with standard normals.
	If doesn't compile on other platform, try different base_generator_type.
	*/
class normal_random_generator
{
public:
	typedef ::base_generator_type base_generator_type;
	typedef ::result_type result_type;
	typedef ::normal_distribution normal_distribution;

	/** Constructor
	* @param seed1 initial seed
	*/
	normal_random_generator(result_type seed1=123795) 
#if __cplusplus > 199711L
				: Generator(seed1),
				Normal_dist(0,1), 
				Normal_gen(std::bind(Normal_dist, std::ref(Generator))) {}									
#else
				: Generator(seed1),
				Normal_dist(0,1), 
				Normal_gen(Generator, Normal_dist) {}
#endif

	/** Standard normal generator
	* @param bvArg bvector passed by reference, standard normals to be written into
	*/
	void operator()(mc::bvector & bvArg)
	{
		std::generate(bvArg.begin(),bvArg.end(),Normal_gen);
	}

	/** Standard normal generator, standard normals to be written in a range
	* @param LeftIter begining of the range
	* @param RightIter end of range
	*/
	void operator()(mc::bvector::iterator LeftIter, mc::bvector::iterator RightIter)
	{
		std::generate(LeftIter,RightIter,Normal_gen);
	}

private:
	base_generator_type Generator; //!< random generator engine
	normal_distribution Normal_dist;//!< determines distribution

#if __cplusplus > 199711L
	std::function<double()> Normal_gen;
#else
	boost::variate_generator<base_generator_type&,
		boost::normal_distribution<> > Normal_gen;//!< generates random numbers, turns them to standard normals
#endif

};

}
#endif //_PARTICULAR_RANDOM_GENERATOR_H__
