#ifndef _PRACTICAL06EXERCISES_HPP__
#define _PRACTICAL06EXERCISES_HPP__

#include "Function.hpp"

namespace exercises
{



/** CallPayoff call payoff
  * @param dK defines the strike
  * @param index defines the index of the relevant underlying
  * @return Function, such that its operator()(bvArg) returns max(0.0,bvArg[index]-dK);
  */
Function CallPayoff(double dK,BVector::size_type index);

/** PutPayoff put payoff
  * @param dK defines the strike
  * @param index defines the index of the relevant underlying
  * @return Function, such that its operator()(bvArg) returns max(0.0,dK-bvArg[index]);
  */
Function PutPayoff(double dK,BVector::size_type index);

/** SpreadOption spread option  payoff
  * @param dK1 defines the strike of the first call
  * @param dW1 defines weight of the first call
  * @param dK2 defines the strike of the second call
  * @param dW2 defines weight of the second call
  * @param index defines the index of the relevant underlying
  * @return Function, such that its operator()(bvArg) returns dW1*max(0.0,bvArg[index]-dK1)+dW2*max(0.0,bvArg[index]-dK2);
  */
Function SpreadOption(double dK1, double dW1, double dK2, double dW2, BVector::size_type index);

/** StraddleOption straddle option  payoff
  * @param dK1 defines the strike of the call
  * @param dW1 defines weight of the call
  * @param dK2 defines the strike of the put
  * @param dW2 defines weight of the put
  * @param index defines the index of the relevant underlying
  * @return Function, such that its operator()(bvArg) returns dW1*max(0.0,bvArg[index]-dK1)+dW2*max(0.0,dK2-bvArg[index]);
  */
Function StraddleOption(double dK1, double dW1, double dK2, double dW2, BVector::size_type index);

/** BasketPayoff basket option  payoff
  * @return Function, such that its operator()(bvArg) returns the entry of bvArg with max value 
  */
Function BasketPayoff();

/** AveragePayoff average payoff
  * @return Function, such that its operator()(bvArg) returns the mean of the entries of bvArg
  */
Function AveragePayoff();

/** SumOfSquares sum of squares
  * @return Function, such that its operator()(bvArg) returns the sum of squares of the entries of bvArg
  */
Function SumOfSquares();

/** InnerProduct sum of squares
  * @param bvBase boost vector 
  * @return Function, such that its operator()(bvArg) returns the inner product of bvBase and bvArg
  */
Function InnerProduct(const BVector & bvBase);



}

#endif //_PRACTICAL05EXERCISES_HPP__
