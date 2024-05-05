
#ifndef _INTERPOLATE_H_
#define _INTERPOLATE_H_ 

#include <vector>
#include <algorithm>


namespace exercises
{

/** \class Interpolate
	\brief Interpolate is a general interpolator object

	Template arguments: PreOp, PostOp assumed to be binary function objects with default constructor
	*/
template<typename PreOp, typename PostOp>
class Interpolate 
{
public: 
	typedef std::vector<double> DVector;
	typedef std::vector<double>::const_iterator CIter;
	typedef std::vector<double>::iterator Iter;
	

	/** Interpolate constructor
	  * @param xVals observed x-values, assumed to be sorted in ascending order
	  * @param yVals observed y-values
	  * @param preTransformation pointer to function object for pre-transformation of y-values
	  * @param postTransformation pointer to function object for post-transformation of y-values
	  */
	Interpolate(const DVector xVals, const DVector yVals);
	
	/** operator() - member function
	  * @param dX x-value argument
	  * @return interpolated and post-transformed value
	  */
	double operator()(const double dX) const;

private:
	DVector m_xVals;
	DVector m_yVals;
	PostOp m_postOp;
};


//*************************************************************************
//*************************************************************************
// Implementation of member functions (constructor)
//*************************************************************************
//*************************************************************************

template<typename PreOp, typename PostOp>
Interpolate<PreOp,PostOp>::Interpolate(DVector xVals, 
					DVector yVals)
					: m_xVals(xVals), 
					  m_yVals(yVals.size()),
					  m_postOp(PostOp())
					  
{
	//pre-transformation - done only once
	std::transform(yVals.begin(),yVals.end(),m_xVals.begin(),m_yVals.begin(),PreOp());
}


}

#ifdef _PRACTICAL_04_SOLUTION_
	#include "Practical04Solutions/Inl/Interpolate.inl"
#else
	#include "Practical04/Inl/Interpolate.inl"
#endif

#endif //_INTERPOLATE_H_
