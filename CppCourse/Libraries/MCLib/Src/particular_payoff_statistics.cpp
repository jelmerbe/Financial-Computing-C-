//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.

#include "MCLib/particular_payoff_statistics.hpp"
#include <algorithm>
#include <limits>

//********************************************************************
// european_calls_payoff implementation
//********************************************************************
pmc::european_calls_payoff::
european_calls_payoff(const mc::bvector & bvStrikes, 
		      unsigned int ind)
  : bvStrikes_(bvStrikes),
    ind_(ind)		
{}

	
mc::bvector & pmc::european_calls_payoff::
operator()(path_out & poArg, mc::bvector & bvOut)
{
  const mc::bvector & underlying=poArg.find(mc::dyadic(0,0))->second;
  size_t n=SizePayoff();
  bvOut.resize(n);

  for(size_t i=0; i<n; ++i)
    bvOut[i]=std::max(underlying[ind_]-bvStrikes_[i],0.0);

  return bvOut;
}

unsigned int pmc::european_calls_payoff::SizePayoff() const {
  return bvStrikes_.size();
}


//********************************************************************
// european_puts_payoff implementation
//********************************************************************
pmc::european_puts_payoff::
european_puts_payoff(const mc::bvector & bvStrikes, 
		     unsigned int ind)
  : bvStrikes_(bvStrikes), ind_(ind)		
{}

	
mc::bvector & pmc::european_puts_payoff::
operator()(path_out & poArg, mc::bvector & bvOut)
{
  const mc::bvector & underlying=poArg.find(mc::dyadic(0,0))->second;
  size_t n=SizePayoff();
  bvOut.resize(n);
  for(size_t i=0; i<n; ++i)
    bvOut[i]=std::max(bvStrikes_[i]-underlying[ind_],0.0);

  return bvOut;
}

unsigned int pmc::european_puts_payoff::SizePayoff() const
{
  return bvStrikes_.size();
}


//********************************************************************
// time_dependent_call implementation
//********************************************************************
pmc::time_dependent_call::
time_dependent_call(const mc::bvector & bvArg, 
		    mc::bvector::size_type index)
  : m_index(index), m_bvStrikes(bvArg)
{}


mc::bvector & pmc::time_dependent_call::
operator()(path_out & pFactors, 
	   const mc::dyadic & dTimeStep,
	   mc::bvector & bvValue)
{
  const mc::bvector & underlying=pFactors.find(dTimeStep)->second;
  size_t n=SizePayoff();
  bvValue.resize(n);
  for(size_t i=0; i<n; ++i)
    bvValue[i]=std::max(underlying[m_index]-m_bvStrikes[i],0.0);

  return bvValue;
}


unsigned int pmc::time_dependent_call::SizePayoff() const
{
	return m_bvStrikes.size();
}

//********************************************************************
// time_dependent_put implementation
//********************************************************************
pmc::time_dependent_put::
time_dependent_put(const mc::bvector & bvArg, 
		   mc::bvector::size_type index)
  : m_index(index), m_bvStrikes(bvArg)
{}


mc::bvector & pmc::time_dependent_put::
operator()(path_out & pFactors, 
	   const mc::dyadic & dTimeStep,
	   mc::bvector & bvValue)
{
  const mc::bvector & underlying=pFactors.find(dTimeStep)->second;
  size_t n=SizePayoff();
  bvValue.resize(n);
  for(size_t i=0; i<n; ++i)
    bvValue[i]=std::max(m_bvStrikes[i]-underlying[m_index],0.0);

  return bvValue;
}


unsigned int pmc::time_dependent_put::SizePayoff() const
{
  return m_bvStrikes.size();
}


//********************************************************************
// asian_discretely_sampled_payoff implementation
//********************************************************************
pmc::asian_discretely_sampled_payoff::
asian_discretely_sampled_payoff(unsigned int iSamplingAccuracy,
				unsigned int indY)
  :  iSamplingAccuracy_(iSamplingAccuracy),
     indY_(indY)
{}

mc::bvector & pmc::asian_discretely_sampled_payoff::
operator()(path_out & poArg, mc::bvector & bvOut)
{	
  bvOut.resize(SizePayoff());
  mc::dyadic dyadStep(0,iSamplingAccuracy_);
  unsigned int n=(1<<iSamplingAccuracy_);
  mc::scalar AvY(mc::scalar(0));
  mc::scalar multiplier;
  for(unsigned int i=0; i<n; ++i, ++dyadStep){
    multiplier=mc::scalar(i)/mc::scalar(i+1);
    AvY*=multiplier;
    AvY+=((*(poArg.find(dyadStep))).second)[indY_]/mc::scalar(i+1);
  }
  bvOut[0]=std::max(((*(poArg.find(dyadStep))).second)[indY_]-AvY,
		    mc::scalar(0));
  return bvOut;
}

unsigned int pmc::asian_discretely_sampled_payoff::SizePayoff() const
{
  return 1;
}

//********************************************************************
// asian_continuously_sampled_payoff implementation
//********************************************************************
pmc::asian_continuously_sampled_payoff::
asian_continuously_sampled_payoff(unsigned int indY, 
				  unsigned int indIntY)
  : indY_(indY), indIntY_(indIntY) 
{}

mc::bvector & pmc::asian_continuously_sampled_payoff::
operator()(path_out & poArg, mc::bvector & bvOut)
{
  bvOut.resize(SizePayoff());
  const mc::bvector & bvYT=(*(poArg.find(mc::dyadic(0,0)))).second;
  bvOut[0]=bvYT[indY_]-bvYT[indIntY_]/poArg.TimeHorizon();
  return bvOut;	
}

unsigned int pmc::asian_continuously_sampled_payoff::
SizePayoff() const
{
  return 1;
}

//********************************************************************
// lookback_discretely_sampled_payoff implementation
//********************************************************************
pmc::lookback_discretely_sampled_payoff::	
lookback_discretely_sampled_payoff(unsigned int iSamplingAccuracy,
				   unsigned int indY)
  :  iSamplingAccuracy_(iSamplingAccuracy),
     indY_(indY)
{}

mc::bvector & pmc::lookback_discretely_sampled_payoff::
operator()(path_out & poArg, mc::bvector & bvOut)
{	
  bvOut.resize(SizePayoff());
  mc::dyadic dyadStep(0,iSamplingAccuracy_);
  unsigned int n=(1<<iSamplingAccuracy_)-1;
  mc::scalar MaxY(std::numeric_limits<double>::min());
  for(unsigned int i=0; i<n; ++i, ++dyadStep)
    MaxY=std::max(MaxY,((*(poArg.find(dyadStep))).second)[indY_]);

  bvOut[0]=MaxY-((*(poArg.find(dyadStep))).second)[indY_];	
  return bvOut;
}

unsigned int pmc::lookback_discretely_sampled_payoff::
SizePayoff() const
{
  return 1;
}



//********************************************************************
// mean_variance_statistics implementation
//********************************************************************
void pmc::mean_variance_statistics::
DumpOnePayoff(mc::bvector & bvArg)
{
  size_t n=bvArg.size();
  if(bvMean_.size()!=n) // first call, resets members
    {
      iNumberOfSimulations_=1;
      bvMean_=bvArg;
      bvMeanOfSquares_.resize(n);
      std::transform(bvArg.begin(),bvArg.end(),
		     bvArg.begin(),
		     bvMeanOfSquares_.begin(),
		     std::multiplies<mc::scalar>());
    }
  else {
    ++iNumberOfSimulations_;
    mc::scalar weight(1.0/mc::scalar(iNumberOfSimulations_));
    mc::scalar rescale(mc::scalar(iNumberOfSimulations_-1.0)*weight);
    bvMean_*=rescale;
    bvMeanOfSquares_*=rescale;
    bvMean_+=(bvArg*weight);
    for(size_t i=0; i<n; ++i)
      bvMeanOfSquares_[i]+=(bvArg[i]*bvArg[i]*weight);
  }
}


std::vector<mc::bvector> pmc::mean_variance_statistics::GetStatistics()
{
  size_t n=bvMean_.size();
  mc::bvector bvVariance(n);
  mc::bvector bvStdev(n);
  for(size_t i=0; i<n; ++i){
    mc::scalar val=(bvMeanOfSquares_[i]-bvMean_[i]*bvMean_[i])
      /mc::scalar(iNumberOfSimulations_);
    bvVariance[i]=val;
    bvStdev[i]=std::sqrt(val);
  }
  std::vector<mc::bvector> vRes(3);
  vRes[0]=bvMean_;
  vRes[1]=bvVariance;
  vRes[2]=bvStdev;

  return vRes;
}

