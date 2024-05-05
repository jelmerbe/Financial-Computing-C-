//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#include "MCLib/dyadic_interval.hpp"

bool mc::dyadic::operator<(const dyadic & dyArg) const
{
	if(n==dyArg.n)
		return k < dyArg.k;
	else if(n>dyArg.n)
		return k <= dyArg.k*(1<<(n-dyArg.n));
	else
		return k*(1<<(dyArg.n-n)) < dyArg.k;
}

bool mc::dyadic::operator>(const dyadic & dyArg) const
{
	return dyArg< *this;
}



mc::dyadic & mc::dyadic::operator++()
{
	unsigned int iTwoToN=(1<<n)-1;
	if(k<iTwoToN)
		++k;
	return *this;
}


mc::dyadic mc::dyadic::operator++(int)
{
	dyadic dyad(*this);
	++*this;
	return dyad;
}

mc::dyadic & mc::dyadic::operator+=(unsigned int iArg)
{
	if(k<(1<<n)-iArg)
		k+=iArg;
	return *this;
}

mc::dyadic mc::dyadic::operator+(unsigned int iArg) const
{
	return dyadic(*this)+=iArg;
}


mc::dyadic & mc::dyadic::operator--()
{
	if(k>0)
	{
		--k;
	}
	return *this;
}

mc::dyadic mc::dyadic::operator--(int)
{
	dyadic dyad(*this);
	--*this;
	return dyad;
}

mc::dyadic & mc::dyadic::operator-=(unsigned int iArg)
{
	if(k>=iArg)
		k-=iArg;

	return *this;
}


mc::dyadic mc::dyadic::operator-(unsigned int iArg) const
{
	return dyadic(*this)-=iArg;
}


mc::dyadic mc::dyadic::BigLeft() const
{
	if(n==0)
	{
		return dyadic(0,0);
	}
	else
	{
		unsigned int argn=n-1;
		unsigned int argk=(k/2);
		return dyadic(argk, argn);
	}
}

mc::dyadic mc::dyadic::SmallRight() const
{
	unsigned int argn=n+1;
	unsigned int argk=2*k+1;
	return dyadic(argk, argn);
}

mc::dyadic mc::dyadic::SmallLeft() const
{
	unsigned int argn=n+1;
	unsigned int argk=2*k;
	return dyadic(argk, argn);
}


std::ostream& mc::operator <<(std::ostream & osArg, const dyadic & dyArg)
{
	osArg<< "(" << dyArg.k << "," << dyArg.n << ")" ;
	return osArg;
}
