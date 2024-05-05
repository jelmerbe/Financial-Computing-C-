
#ifndef _BINARY_OPERATORS_H__
#define _BINARY_OPERATORS_H__

#include <vector>
#include <functional>

namespace exercises
{

/** \class DF2Yield
	\brief DF2Yield is a particular binary function object derived from binary_function

	The operator() member takes discount factor and time to maturity and returns the corresponding yield
	*/
class DF2Yield : public std::binary_function<double,double,double>
{
public:
	/** operator() - member function
	  * @param dDiscountFactor discount factor
	  * @param dTimeToMaturity time to maturity
	  * @return continuously compounding yield corresponding to discount factor
	  */
	double operator()(const double dDiscountFactor, const double dTimeToMaturity) const;
};

/** \class Yield2DF
	\brief Yield2DF is a particular binary function object derived from BinaryFunction

	The operator() member takes yield and time to maturity and returns the corresponding discount factor
	*/
class Yield2DF : public std::binary_function<double,double,double>
{
public:
	/** operator() - member function
	  * @param dYield continuously compounding interest rate
	  * @param dTimeToMaturity time to maturity
	  * @return discount factor
	  */
	double operator()(const double dYield, const double dTimeToMaturity) const;
};


/** \class DF2Libor
	\brief DF2Libor is a particular binary function object derived from binary_function

	The operator() member takes discount factor and time to maturity and returns the corresponding yield
	*/
class DF2Libor : public std::binary_function<double,double,double>
{
public:
	/** operator() - member function
	  * @param dDiscountFactor discount factor
	  * @param dTimeToMaturity time to maturity
	  * @return spot Libor rate corresponding to discount factor and maturity
	  */
	double operator()(const double dDiscountFactor, const double dTimeToMaturity) const;
};

/** \class Libor2DF
	\brief Libor2DF is a particular binary function object derived from BinaryFunction

	The operator() member takes yield and time to maturity and returns the corresponding discount factor
	*/
class Libor2DF : public std::binary_function<double,double,double>
{
public:
	/** operator() - member function
	  * @param dLibor continuously compounding interest rate
	  * @param dTimeToMaturity time to maturity
	  * @return discount factor
	  */
	double operator()(const double dLibor, const double dTimeToMaturity) const;
};

}

#endif //_BINARY_OPERATORS_H__