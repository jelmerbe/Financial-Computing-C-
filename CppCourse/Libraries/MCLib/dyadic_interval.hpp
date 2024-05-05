//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved. 
//Credit is given to Terry Lyons. 
#ifndef _DYADIC_INTERVAL_H__
#define _DYADIC_INTERVAL_H__

#include <iostream>
#include <cmath>
#include <utility>
#include <functional>
#include <algorithm>

namespace mc
{

//forward declaration
class dyadic;

/** operator<< for dyadics. 
* @param osArg ostream 
* @param dyArg dyadic interval
  */
std::ostream& operator <<(std::ostream & osArg, const dyadic & dyArg);

/** \class dyadic
	\brief dyadic is an implementation of dyadic sub-intervals of [0,1]

	The instances of the dyadic type are intervals of the form [k2^{-n},(k+1)2^{-n)]. 
	Ordering is defined by [a,b]<[c,d] iff a<c or (a=c and b<d).
	A version of this class was created in 2005-2006 during the C++ workshops led Terry Lyons.
	*/
class dyadic
{
	// operator<< is declared as friend of dyadic
	friend std::ostream& operator<<(std::ostream& osArg,const dyadic& dyArg);
public:

	/** Default constructor
	 * Constructs the interval [0,1].
	 */
	dyadic(): k(0), n(0) {} 
		
	/** Constructor.
	 * Constructs the interval [k2^{-n},(k+1)2^{-n)].
	 * @param kArg coefficient
	 * @param nArg exponent*(-1)
	 */
	dyadic(unsigned int kArg, unsigned int nArg): 
		k(std::min<int>(kArg,(1<<nArg)-1)), 
			n(nArg) {}
	
	/** Copy constructor.
	  * @param dyadArg
	 */
	dyadic(const dyadic & dyadArg):  k(dyadArg.k), n(dyadArg.n) {}

	/** Destructor
	 */
	~dyadic(void){}

	/** operator==
	 */
	inline bool operator==(const dyadic & dyArg ) const { return (k==dyArg.k && n==dyArg.n);} 

	/** operator!=
	 */
	inline bool operator!=(const dyadic & dyArg) const { return (k!=dyArg.k || n!=dyArg.n); }
	
	/** operator>
	 */
	bool operator>(const dyadic & ) const ;

	/** operator<
	 */
	bool operator<(const dyadic & ) const ;

	/** operator++ (prefix)
	 * incrementing a dyadic k2^n -> (k+1)2^n
	 */
	dyadic & operator++();
	
	/** operator++(int) (postfix)
	 * incrementing a dyadic k2^n -> (k+1)2^n
	 */
	dyadic operator++(int);

	/** operator+=
	 * incrementing by iArg (within [0,1])
	 * @param iArg dyadic is shifted to the right by this many steps
	 */
	dyadic & operator+=(unsigned int iArg);

	/** operator+
	 * incrementing by iArg (within [0,1])
	 * @param iArg dyadic is shifted to the right by this many steps
	 */
	dyadic operator+(unsigned int iArg) const;

	/** operator-- (prefix)
	 * incrementing a dyadic k2^n -> (k-1)2^n, unless k=0
	 */
	dyadic & operator--();
	
	/** operator-- (postfix)
	 * incrementing a dyadic k2^n -> (k-1)2^n, unless k=0
	 */
	dyadic operator--(int);

	/** operator-=
	 * decrementing by iArg (within [0,1])
	 * @param iArg dyadic is shifted to the left by this many steps
	 */
	dyadic & operator-=(unsigned int iArg);

	/** operator-
	 * decrementing by iArg (within [0,1])
	 * @param iArg dyadic is shifted to the left by this many steps
	 */
	dyadic operator-(unsigned int iArg) const;

	/** Returning the smallest dyadic interval including but not equal to this
	* i.e. for (2k+1)*2^n it returns k*2^(n-1)	
	* for (2k)*2^n it returns k*2^(n-1)
	*/
	dyadic BigLeft() const;

	/** Returning the left half of this 
	* i.e. for k*2^n it returns (2k)*2^(n+1)	
	*/
	dyadic SmallLeft() const;

	/** Returning the right half of this if exists
	* i.e. for k*2^n it returns (2k+1)*2^(n+1)	
	*/
	dyadic SmallRight() const;
	
	/** Checking if this is of the form (2k)*2^n
	*/
	inline bool IsLeft() const {return ((2*(k/2))==k);}

	/** Returning the length of the interval
	*/
	inline double GetLength() const {return ldexp(1.0,(-1)*n);}

	/** Returning the length of the interval
	*/
	inline double GetHalfLength() const {return ldexp(1.0,(-1)*(n+1));}

	/** Returning accuracy
	*/
	inline unsigned int Accuracy() const {return n;}

	/** Returning position
	*/
	inline unsigned int Position() const {return k;}

	/** Returning an element with same left point but of increased accuracy
	*/
	inline dyadic IncreaseAccuracyLeft(unsigned int a) const {return dyadic(k*(1<<a),n+a);}
    
	/** Returning an element with same right point but of increased accuracy
	*/
	inline dyadic IncreaseAccuracyRight(unsigned int a) const {return dyadic((k+1)*(1<<a)-1,n+a);}

private:

	unsigned int k; //!< coefficient 
	unsigned int n; //!< exponent*(-1)

};

// Exercises:
// define and implement dyadic & dyadic::operator+=(int) 
// define and implement dyadic & dyadic::operator-=(int) 


/** \class dyadicLessByRightEnd
	\brief dyadicLessByRightEnd is a function object for sorting dyadics by their left end point

	*/
class dyadicLessByRightEnd : std::binary_function <dyadic,dyadic,bool>
{
public:
	bool operator() (const dyadic & d2, const dyadic & d1) const
    {
		unsigned int k1(d1.Position()+1), k2(d2.Position()+1), n1(d1.Accuracy()), n2(d2.Accuracy());
		if (n1>n2)
			return k1 < k2*(1<<(n1-n2));
		else
			return k1*(1<<(n2-n1)) < k2;
	}
};

}
#endif //_DYADIC_INTERVAL_H__
