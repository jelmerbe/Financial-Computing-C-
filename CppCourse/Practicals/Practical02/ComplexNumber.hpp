#ifndef _COMPLEX_NUMBER_H__
#define _COMPLEX_NUMBER_H__

#include <iostream>

class ComplexNumber
{
public:
	ComplexNumber();
	explicit ComplexNumber(double , double=0.0);

	ComplexNumber & operator+=(const ComplexNumber &);
	ComplexNumber & operator-=(const ComplexNumber &);
	ComplexNumber & operator*=(const ComplexNumber &);
	ComplexNumber & operator/=(const ComplexNumber &);
	
	ComplexNumber & operator+=(const double &);
	ComplexNumber & operator-=(const double &);
	ComplexNumber & operator*=(const double &);
	ComplexNumber & operator/=(const double &);

	std::ostream & print(std::ostream &) const;

private:
	double dRe_;
	double dIm_;
};

//non-members (can be constructed using member-functions)
ComplexNumber operator+(const ComplexNumber &,const ComplexNumber &);
ComplexNumber operator-(const ComplexNumber &,const ComplexNumber &);
ComplexNumber operator*(const ComplexNumber &,const ComplexNumber &);
ComplexNumber operator/(const ComplexNumber &,const ComplexNumber &);

ComplexNumber operator+(const ComplexNumber &,const double &);
ComplexNumber operator-(const ComplexNumber &,const double &);
ComplexNumber operator*(const ComplexNumber &,const double &);
ComplexNumber operator/(const ComplexNumber &,const double &);

ComplexNumber operator+(const double &,const ComplexNumber &);
ComplexNumber operator-(const double &,const ComplexNumber &);
ComplexNumber operator*(const double &,const ComplexNumber &);
ComplexNumber operator/(const double &,const ComplexNumber &);

std::ostream & operator<<(std::ostream &, const ComplexNumber &);




//...
#endif //_COMPLEX_NUMBER_H__
