//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _UTILS_H__
#define _UTILS_H__

#include "MCLib/type_definitions.hpp"

namespace mc
{

	/** Cumulative density of the normal distribution
	  * @param Arg argument
	  */
	mc::scalar normcf(mc::scalar Arg);
	
	/** BS formula
	  * @param S0 initial stock price
	  * @param K strike
	  * @param T time to maturity
	  * @param r riskfree rate
	  * @param sigma volatility
	  * @param IsCall if true it returns call price, otherwise put price
	  */
	mc::scalar BSOptionPrice(mc::scalar S0, 
						    mc::scalar K, 
							mc::scalar T, 
							mc::scalar r, 
							mc::scalar sigma,
							bool IsCall=true);
}




#endif//_UTILS_H__