#ifndef _SPARSE_VECTOR_H__
#define _SPARSE_VECTOR_H__

#include <map>
#include <iostream>

namespace exercises
{

typedef std::map<unsigned int, double> SparseVector;

/** operator+= operator, increments svArg1 by svArg2
  * @param svArg1 first argument is to be incremented
  * @param svArg2 second argument
  * @return reference to the modified first argument
 */
SparseVector & operator+=(SparseVector & svArg1, const SparseVector & svArg2);


/** operator+ operator, increments svArg1 by svArg2
  * @param svArg1 first argument is to be incremented
  * @param svArg2 second argument
  * @return sum of the arguments
 */
SparseVector operator+(const SparseVector & svArg1, const SparseVector & svArg2);

/** operator-= operator, decrements svArg1 by svArg2
  * @param svArg1 first argument is to be decremented
  * @param svArg2 second argument
  * @return reference to the modified first argument
 */
SparseVector & operator-=(SparseVector & svArg1, const SparseVector & svArg2);

/** operator- operator, increments svArg1 by svArg2
  * @param svArg1 first argument is to be incremented
  * @param svArg2 second argument
  * @return difference of the arguments
 */
SparseVector operator-(const SparseVector & svArg1, const SparseVector & svArg2);


/** operator*= operator, scalar product
  * @param svArg sparse vector argument
  * @param dArg scalar argument argument
  * @return reference to the sparse vector vector argument
 */
SparseVector & operator*=(SparseVector & svArg, const double dArg);


/** operator* operator, scalar product
  * @param svArg sparse vector argument
  * @param dArg scalar argument argument
  * @return product of arguments
 */
SparseVector operator*(const SparseVector & svArg, const double dArg);

/** operator* operator, scalar product
  * @param dArg scalar argument argument
  * @param svArg sparse vector argument
  * @return product of arguments
 */
SparseVector operator*(const double dArg, const SparseVector & svArg);


/** operator<< ostream operator
  * @param os ostream
  * @param svArg sparse vector to be displayed
  * @return reference to the ostream argument
 */
std::ostream & operator<<(std::ostream & os, const SparseVector & svArg);

}

#endif //_SPARSE_VECTOR_H__