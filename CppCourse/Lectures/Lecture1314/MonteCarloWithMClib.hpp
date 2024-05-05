#ifndef _MONTECARLO_WITH_MCLIB_HPP__
#define _MONTECARLO_WITH_MCLIB_HPP__


#include "MCLib/base_factory.hpp"
#include "MCLib/base_payoff_statistics.hpp"


/** MonteCarloMClib Monte Carlo estimate based on MClib
  * @param iNumericalScale defines the scale of the numerical SDE method
  * @param iSolutionStoredScale defines the scale of the solution paths
  * @param iNumberOfPaths number of paths to be simulated
  * @param sT time horizon - scaling parameter
  * @param ppoInCond initial condition of solution
  * @param ParticularFactory defines a set of rules (input noise generation, numerical SDE etc.)
  * @param ParticularPayoff payoff function
  * @param ParticularStatistics statistics object
  * @return reference to the input argument statistics object that contains information on the simulated payoff values
  */
template<typename PPI, typename PPO>
mc::statistics & MonteCarloMClib(unsigned int iNumericalScale,
				 unsigned int iSolutionStoredScale,
				 unsigned int iNumberOfPaths,
				 mc::scalar sT,
				 PPO & ppoInCond,
				 mc::mc_factory<PPI,PPO> & ParticularFactory,
				 mc::payoff<PPO> & ParticularPayoff,
				 mc::statistics & ParticularStatistics)
{
	typedef mc::mc_factory<PPI,PPO> factory;
	//typedef typename factory::path_in_ptr path_in_ptr;
	typedef typename factory::path_out path_out;



	mc::bvector bvStocks;
	for(unsigned int i=0; i<iNumberOfPaths; ++i)
	{
		//generating solution paths along new input noise
	  path_out poPath(ParticularFactory.GetNewPathOut(iNumericalScale,iSolutionStoredScale,ppoInCond,sT));
		//evaluating payoff along Path (results written into bvStock)
	  ParticularPayoff(poPath,bvStocks);
		//working out statistics
	  ParticularStatistics.DumpOnePayoff(bvStocks);
	}
	return ParticularStatistics;
}

#endif //_MONTECARLO_WITH_MCLIB_HPP__
