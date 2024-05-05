//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.

#include "MCLib/utils.hpp"
#if __cplusplus > 199711L
  // erf is part of <cmath> in c++11
  namespace erfns = std;
#else
  #include <boost/math/special_functions/erf.hpp>
  namespace erfns = boost::math;
#endif
#include <cmath>

using namespace mc;
using namespace std;

mc::scalar mc::normcf(mc::scalar Arg)
{
	return scalar(1)/scalar(2)*(1+erfns::erf(Arg/sqrt(scalar(2))));
}

mc::scalar mc::BSOptionPrice(mc::scalar S0, 
						    mc::scalar K, 
							mc::scalar T, 
							mc::scalar r, 
							mc::scalar sigma,
							bool IsCall)
{
  if(K < 1.0e-14)
    return S0;
  
  double sigmaSqrtT = sigma * sqrt(T);  
  if(sigmaSqrtT < 1.0e-14){
    double payoff = S0 - K * exp(-r*T);
    if(IsCall)
      return max(0.0, payoff);
    else
      return max(0.0, -payoff);
   }
  else {
    mc::scalar d1=(log(S0/K)+(r+sigma*sigma/scalar(2))*T)/sigmaSqrtT;
    mc::scalar d2=(log(S0/K)+(r-sigma*sigma/scalar(2))*T)/sigmaSqrtT;
    if(IsCall)
      return S0*normcf(d1)-exp(-r*T)*K*normcf(d2);
    else
      return exp(-r*T)*K*(1-normcf(d2))-S0*(1-normcf(d1));
  }
}
