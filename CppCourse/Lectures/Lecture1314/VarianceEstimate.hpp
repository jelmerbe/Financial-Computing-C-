#ifndef _VARIANCE_ESTIMATE_HPP__
#define _VARIANCE_ESTIMATE_HPP__


#include "MCLib/base_factory.hpp"
#include "MCLib/base_payoff_statistics.hpp"


/** VarianceEstimate Monte Carlo estimate of difference of payoff when simulated on different scales
  * @param iAccuracy1 defines one of the scales (fine or coarse)
  * @param iAccuracy2 defines the other scale (coarse or fine)
  * @param iNumberOfPaths number of paths to be simulated
  * @param sT time horizon - scaling parameter
  * @param ppoInCond initial condition of solution
  * @param ParticularFactory defines a set of rules (input noise generation, numerical SDE etc.)
  * @param ParticularPayoff payoff function
  * @param ParticularStatistics statistics object
  * @return reference to the input argument statistics object that 
			contains information on the difference of payoff values on different scales
  */
template<typename PPI, typename PPO>
mc::statistics & VarianceEstimate(unsigned int iAccuracy1,
				  unsigned int iAccuracy2,
				  unsigned int iNumberOfPaths,
				  mc::scalar sT,
				  PPO & ppoInCond,
				  mc::mc_factory<PPI,PPO> & ParticularFactory,
				  mc::payoff<PPO> & ParticularPayoff,
				  mc::statistics & ParticularStatistics)
{
	typedef mc::mc_factory<PPI,PPO> factory;
	typedef typename factory::path_in_ptr path_in_ptr;
	typedef typename factory::path_out path_out;

	unsigned int iAccuracyFine=std::max(iAccuracy1,iAccuracy2);
	unsigned int iAccuracyCoarse=std::min(iAccuracy1,iAccuracy2);

	mc::bvector resMean1, resMean2, resDiff2, bVecCoarse, bVecFine;
	for(unsigned int i=0; i<iNumberOfPaths; ++i)
	{   
		//generating input noise
		path_in_ptr piPtr = ParticularFactory.GetNewPathInPtr(iAccuracyFine,sT);

		//generating solution paths on fine scale
		path_out poPath1(ParticularFactory.GetNewPathOut(piPtr,iAccuracyFine,iAccuracyFine,ppoInCond,sT));
		//evaluating payoff on fine scale
		ParticularPayoff(poPath1,bVecFine);

		//generating solution paths on coarse scale
		path_out poPath2(ParticularFactory.GetNewPathOut(piPtr,iAccuracyCoarse,iAccuracyCoarse,ppoInCond,sT));
		//evaluating payoff on fine scale
		ParticularPayoff(poPath2,bVecCoarse);

		//working out statistics of difference
		ParticularStatistics.DumpOnePayoff(bVecFine-=bVecCoarse);
	}
	return ParticularStatistics;
}

#endif //_VARIANCE_ESTIMATE_HPP__
