#ifndef _FUNCTION_H__
#define _FUNCTION_H__

#include "Definitions.hpp"
#include "IFunction.hpp"

namespace exercises
{

/** \class Function
	\brief a class modelling R^k->R functions equipped with some operations (+,-,*,/,exp,log)

	*/
class Function
{
public:
	/** Function constructor, initialises m_ifun
	  * @param ifunptr smart pointer to IFunction
	  */
	explicit Function(IFunPtr ifunptr) : m_ifun(ifunptr) {}

	/** Function constructor, initialises m_ifun
	  * @param index initialises m_ifun to point to the particular 
			   IFunctionCoordinate returning the component corresponding to index
	  */
	explicit Function(const BVector::size_type index) : m_ifun(new IFunctionCoordinate(index)) {}

	/** Function operator(), R^k->R functionality
	  * @param bvArg boost vector
	  * @return the value evaluated by the IFunction pointed by m_ifun
	  */
	double operator()(const BVector & bvArg)
	{
		return (*m_ifun)(bvArg);
	}	

	Function & operator+=(const Function &);
	Function & operator-=(const Function &);
	Function & operator*=(const Function &);
	Function & operator/=(const Function &);

	Function & operator+=(const double);
	Function & operator-=(const double);
	Function & operator*=(const double);
	Function & operator/=(const double);

	Function & exp();
	Function & log();
	Function & max(const Function &);
	Function & min(const Function &);


private:
	IFunPtr m_ifun;//smart pointer to IFunction
};



// Global functions

Function operator+(const Function &, const Function &);
Function operator-(const Function &, const Function &);
Function operator*(const Function &, const Function &);
Function operator/(const Function &, const Function &);

Function operator+(const Function &, const double);
Function operator-(const Function &, const double);
Function operator*(const Function &, const double);
Function operator/(const Function &, const double);

Function operator+(const double , const Function &);
Function operator-(const double , const Function &);
Function operator*(const double , const Function &);
Function operator/(const double , const Function &);

Function exp(const Function & );
Function log(const Function & );

Function max(const Function &, const Function &);
Function min(const Function &, const Function &);







}

#endif //_FUNCTION_H__