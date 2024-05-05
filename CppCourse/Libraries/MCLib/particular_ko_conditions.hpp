//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PARTICULAR_KO_CONDITIONS_H__
#define _PARTICULAR_KO_CONDITIONS_H__

#include "MCLib/type_definitions.hpp"

namespace pmc
{


/** \class UpAndOut
	\brief UpAndOut is a particular KO condition
	UpAndOut function object for up-and-out KO 
*/
class UpAndOut
{
public:
	/** Constructor
	* @param sBarrier barrier
	* @param ind index of path piece out that determines KO event
	*/
  UpAndOut(mc::scalar sBarrier, 
	   unsigned int ind=0);

	/** operator() determines KO event
	* @param bvArg path piece
	* @return true if KO'd
	*/
  bool operator()(const mc::bvector & bvArg) const;

	/** Reset()
	*/
  void Reset(){}

private:
  mc::scalar sBarrier_;//!< KO barrier
  unsigned int ind_;//!< index of component triggering the KO
};

/** \class DoubleBarrier
	\brief DoubleBarrier is a particular KO condition
	DoubleBarrier function object for double barrier KO
*/
class DoubleBarrier
{
public:
	/** Constructor
	* @param sUpperBarrier upper barrier
	* @param sLowerBarrier lower barrier
	* @param ind index of component determining KO event
	*/
  DoubleBarrier(mc::scalar sUpperBarrier,
		mc::scalar sLowerBarrier,
		unsigned int ind=0);

	/** operator() determines KO event
	* @param bvArg path piece out
	* @return true if KO'd
	*/
  bool operator()(const mc::bvector & bvArg) const;

	/** Reset()
	*/
  void Reset(){}

private:
  mc::scalar sUpperBarrier_;//!< upper barrier
  mc::scalar sLowerBarrier_;//!< lower barrier
  unsigned int ind_;//!< index of component triggering the KO
};


/** \class UpDownAndOut
	\brief UpDownAndOut is a particular KO condition
	UpDownAndOut function object for UpDownAndOut KO
*/
class UpDownAndOut
{
public:
	/** Constructor 
	* @param sUpperBarrier upper barrier
	* @param sLowerBarrier lower barrier
	* @param ind index of component determining KO event
	*/
  UpDownAndOut(mc::scalar sUpperBarrier, 
	       mc::scalar sLowerBarrier,
	       unsigned int ind=0);

	/** opertaor() determines KO event
	* @param bvArg path piece out
	* @return true if KO'd
	*/
  bool operator()(const mc::bvector & bvArg);

	/** Reset()
	*/
  void Reset(){}


private:
  mc::scalar sUpperBarrier_;//!< upper barrier
  mc::scalar sLowerBarrier_;//!< lower barrier
  bool UpCrossed_;//!< keeps track of the first trigger
  unsigned int ind_;//!< index of component triggering the KO
};


}



#endif //_PARTICULAR_KO_CONDITIONS_H__

