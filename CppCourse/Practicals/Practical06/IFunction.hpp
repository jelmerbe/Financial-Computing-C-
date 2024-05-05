#ifndef _IFUNCTION_H__
#define _IFUNCTION_H__

#include "Definitions.hpp"
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <cmath>

namespace exercises
{

/** \class IFunction
	\brief abstract class, defines framework for particular derived classes

	*/
class IFunction
{
public:
	/** ~IFunction destructor - must be virtual
	  */	
	virtual ~IFunction(){}
	
	/** operator() R^k->R function, pure virtual
	  * @param bvARg vector argument
	  */	
	virtual double operator()(const BVector & bvARg) const =0;
};


/** \class IFunctionConst
	\brief particular derived class 
	*/
class IFunctionConst : public IFunction
{
public:
	/** IFunctionConst constructor, initialises m_dConst
	  * @param dArg 
	  */
	IFunctionConst(double dArg=0.0) : m_dConst(dArg) {}

	/** operator() R^k->R function, for any argument it returns m_dConst
	  * @param bvARg vector argument
	  * @return m_dConst
	  */
	double operator()(const BVector & bvArg) const
	{
		return m_dConst;
	}

private:
	double m_dConst;
};

/** \class IFunctionCoordinate
	\brief particular derived class 
	*/
class IFunctionCoordinate : public IFunction
{
public:

	/** IFunctionCoordinate constructor, initialises m_index
	  * @param index 
	  */
	IFunctionCoordinate(BVector::size_type index=0) : m_index(index) {}

	/** operator() R^k->R function, returns the component of bvARg, with index index m_index
	  * @param bvARg vector argument
	  * @return component of bvARg, with index index m_index
	  */
	double operator()(const BVector & bvArg) const
	{
		return bvArg[m_index];
	}
private:
	BVector::size_type m_index;
};


/** \class IFunctionUnaryOp for unary compositions
	\brief particular derived class 
	*/
template<typename UnaryOp>
class IFunctionUnaryComp : public IFunction
{
public:
	/** IFunctionUnaryComp constructor, initialises data members
	  * @param ifun pointer to IFunction , defines the inner function object
	  * @param unaryOp defines outer function object
	  */
	IFunctionUnaryComp(IFunPtr ifun, UnaryOp unaryOp=UnaryOp()) : m_unaryOp(unaryOp), m_ifun(ifun) {}

	/** operator() R^k->R function, composes 
	  * @param bvARg vector argument
	  * @return calls operator() of m_ifun, then subs the result to operator() of m_unaryOp
	  */
	double operator()(const BVector & bvArg) const
	{
		return m_unaryOp((*m_ifun)(bvArg));
	}

private:
	UnaryOp m_unaryOp;//outer unary function object
	IFunPtr m_ifun;//inner function object
};


/** \class IFunctionBinaryComp for binary compositions
	\brief particular derived class 
	*/
template<typename BinaryOp>
class IFunctionBinaryComp : public IFunction
{
public:
	/** IFunctionUnaryComp constructor, initialises data members
	  * @param ifun1 pointer to IFunction , defines the first inner function object
	  * @param ifun2 pointer to IFunction , defines the second inner function object
	  * @param bineryOp defines outer binary function object
	  */
	IFunctionBinaryComp(IFunPtr ifun1, IFunPtr ifun2, BinaryOp binaryOp=BinaryOp()) 
		: m_binaryOp(binaryOp), m_ifun1(ifun1), m_ifun2(ifun2) {}

	/** operator() R^k->R function, composes 
	  * @param bvARg vector argument
	  * @return calls operator() of m_ifun1, and operator()of m_ifun2, 
				the results are substituted into the binary operator() of m_binaryOp
	  */
	double operator()(const BVector & bvArg) const 
	{
		return m_binaryOp((*m_ifun1)(bvArg),(*m_ifun2)(bvArg));
	}

private:
	BinaryOp m_binaryOp;//outer bunary function object
	IFunPtr m_ifun1;//first inner function object
	IFunPtr m_ifun2;//second inner function object
};


}

#endif //_IFUNCTION_H__