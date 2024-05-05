#include "Practical06/Function.hpp"
#include <functional>
#include <boost/numeric/ublas/io.hpp>

using namespace exercises;
using namespace std;
using namespace ptrnamespace;
//#include <boost/preprocessor/stringize.hpp>
//#pragma message "C++ version=" BOOST_PP_STRINGIZE(__cplusplus)

#if __cplusplus >= 201402L 
	typedef std::function<double(double)> UnaryFunction;
	typedef std::function<double(double,double)> BinaryFunction;
#endif



//implementation of operator+=(const Function &)
//this replaces m_ifun with an IBinaryUnaryOp
Function & exercises::Function::operator+=(const Function & fArg)
{
	m_ifun=IFunPtr(make_shared<IFunctionBinaryComp<plus<double>>>(m_ifun,fArg.m_ifun));
	return *this;
}


#if __cplusplus < 201402L 
	// pre C++14
	//function object for incrementing doubles by a certain value
	class IncrementByValue
	{
	public:
		IncrementByValue(const double dArg) : m_dArg(dArg) {}
		double operator()(const double dArg) const { return dArg+m_dArg;}
	private:
		double m_dArg;
	};	
#endif


//implementation of operator+=(const double)
//this replaces m_ifun with an IFunctionUnaryComp
Function & exercises::Function::operator+=(const double dArg)
{

#if __cplusplus < 201402L 
	// pre C++14	
	m_ifun=IFunPtr(make_shared<IFunctionUnaryComp<IncrementByValue>>(m_ifun,IncrementByValue(dArg)));
#else
	// C++14
	m_ifun=IFunPtr(make_shared<IFunctionUnaryComp<UnaryFunction>>(m_ifun,
								[dArg](double dVal){return dArg + dVal;}));	
#endif

	
	return *this;
}


Function & exercises::Function::operator-=(const Function & fArg)
{
	m_ifun=IFunPtr(make_shared<IFunctionBinaryComp<minus<double>>>(m_ifun,fArg.m_ifun));
	return *this;
}


Function & exercises::Function::operator-=(const double dArg)
{

#if __cplusplus < 201402L 
	// pre C++14
	// creating function object by binding the built-in binary function object
	typedef binder2nd<minus<double> > DecrementByValue;	
	m_ifun=IFunPtr(make_shared<IFunctionUnaryComp<DecrementByValue>>(m_ifun, bind2nd(minus<double>(),dArg)));
#else
	// C++14
	m_ifun=IFunPtr(make_shared<IFunctionUnaryComp<UnaryFunction>>(m_ifun, [dArg](double dVal){return dVal - dArg;}));
#endif
	
	return *this;
}

Function & exercises::Function::operator*=(const Function & fArg)
{
	m_ifun=IFunPtr(make_shared<IFunctionBinaryComp<multiplies<double>>>(m_ifun,fArg.m_ifun));
	return *this;
}


Function & exercises::Function::operator*=(const double dArg)
{

#if __cplusplus < 201402L 
	// pre C++14
	typedef binder2nd<multiplies<double> > MultiplyByValue;
	m_ifun=IFunPtr(make_shared<IFunctionUnaryComp<MultiplyByValue>>(m_ifun,bind2nd(multiplies<double>(),dArg)));
#else
	// C++14
	m_ifun=IFunPtr(make_shared<IFunctionUnaryComp<UnaryFunction>>(m_ifun, [dArg](double dVal){return dVal * dArg;}));
#endif
	
	return *this;
}


Function & exercises::Function::operator/=(const Function & fArg)
{
	m_ifun=IFunPtr(make_shared<IFunctionBinaryComp<divides<double>>>(m_ifun,fArg.m_ifun));
	return *this;
}


Function & exercises::Function::operator/=(const double dArg)
{

#if __cplusplus < 201402L 
	// pre C++14
	typedef binder2nd<divides<double> > DividesByValue;
	m_ifun=IFunPtr(make_shared<IFunctionUnaryComp<DividesByValue>>(m_ifun,bind2nd(divides<double>(),dArg)));
#else
	// C++14
	m_ifun=IFunPtr(make_shared<IFunctionUnaryComp<UnaryFunction>>(m_ifun, [dArg](double dVal){return dVal / dArg;}));
#endif

	return *this;
}


#if __cplusplus < 201402L 
	// pre C++14
	//function object for max
	class Maximum
	{
	public:
		double operator()(const double dArg1,const double dArg2) const
		{
			return max(dArg1,dArg2);
		}
	};
#endif


Function & exercises::Function::max(const Function & fArg)
{
#if __cplusplus < 201402L 
	// pre C++14
	m_ifun=IFunPtr(make_shared<IFunctionBinaryComp<Maximum>>(m_ifun,fArg.m_ifun));
#else
	// C++14
	m_ifun=IFunPtr(make_shared<IFunctionBinaryComp<BinaryFunction>>(m_ifun, fArg.m_ifun,
					[](double dVal1, double dVal2)->double{return ::max(dVal1, dVal2);}));
#endif
	
	return *this;
}


#if __cplusplus < 201402L 
	// pre C++14
	//function object for min
	class Minimum
	{
	public:
		double operator()(const double dArg1,const double dArg2) const
		{
			return min(dArg1,dArg2);
		}
	};
#endif

Function & exercises::Function::min(const Function & fArg)
{
#if __cplusplus < 201402L 
	// pre C++14
	m_ifun=IFunPtr(make_shared<IFunctionBinaryComp<Minimum>>(m_ifun,fArg.m_ifun));
#else
	// C++14
	m_ifun=IFunPtr(make_shared<IFunctionBinaryComp<BinaryFunction>>(m_ifun, fArg.m_ifun,
					[](double dVal1, double dVal2){return ::min(dVal1, dVal2);}));
#endif

	return *this;
}

#if __cplusplus < 201402L 
	// pre C++14
	//function object for exp
	class Exponential
	{
	public:
		double operator()(const double dArg) const
		{
			return exp(dArg);
		}
	};
#endif

Function & exercises::Function::exp()
{
#if __cplusplus < 201402L 
	// pre C++14
	m_ifun =IFunPtr(make_shared<IFunctionUnaryComp<Exponential>>(m_ifun) );
#else
	// C++14
	m_ifun =IFunPtr(make_shared<IFunctionUnaryComp<UnaryFunction>>(m_ifun, [](double dVal){return ::exp(dVal);}));
#endif
	
	return *this;
}


#if __cplusplus < 201402L 
	// pre C++14
	//function object for log
	class Logarithm
	{
	public:
		double operator()(const double dArg) const
		{
			return log(dArg);
		}
	};
#endif

Function & exercises::Function::log()
{
#if __cplusplus < 201402L 
	// pre C++14
	m_ifun =IFunPtr(make_shared<IFunctionUnaryComp<Logarithm>>(m_ifun) );
#else
	// C++14
	m_ifun =IFunPtr(make_shared<IFunctionUnaryComp<UnaryFunction>>(m_ifun, [](double dVal){return ::log(dVal);}));
#endif

	return *this;
}


//*********************************************************************
// implementation of global functions in terms of member functions
//*********************************************************************


Function exercises::operator+(const Function & fArg1, const Function & fArg2)
{
	Function result(fArg1);
	return result+=fArg2;
}

Function exercises::operator-(const Function & fArg1, const Function & fArg2)
{
	Function result(fArg1);
	return result-=fArg2;
}

Function exercises::operator*(const Function & fArg1, const Function & fArg2)
{
	Function result(fArg1);
	return result*=fArg2;
}

Function exercises::operator/(const Function & fArg1, const Function & fArg2)
{
	Function result(fArg1);
	return result/=fArg2;
}

Function exercises::operator+(const Function & fArg, const double dArg)
{
	Function result(fArg);
	return result+=dArg;
}

Function exercises::operator-(const Function & fArg, const double dArg)
{
	Function result(fArg);
	return result-=dArg;
}

Function exercises::operator*(const Function & fArg, const double dArg)
{
	Function result(fArg);
	return result*=dArg;
}

Function exercises::operator/(const Function & fArg, const double dArg)
{
	Function result(fArg);
	return result/=dArg;
}

Function exercises::operator+(const double dArg, const Function & fArg)
{
	return fArg+dArg;
}

Function exercises::operator-(const double dArg, const Function & fArg)
{
	return fArg-dArg;
}

Function exercises::operator*(const double dArg, const Function & fArg)
{
	return fArg*dArg;
}

Function exercises::operator/(const double dArg, const Function & fArg)
{
	return fArg/dArg;
}

Function exercises::exp(const Function & fArg)
{
	Function result(fArg);
	return result.exp();
}

Function exercises::log(const Function & fArg)
{
	Function result(fArg);
	return result.log();
}

Function exercises::max(const Function & fArg1, const Function & fArg2)
{
	Function result(fArg1);
	return result.max(fArg2);
}

Function exercises::min(const Function & fArg1, const Function & fArg2)
{
	Function result(fArg1);
	return result.min(fArg2);
}