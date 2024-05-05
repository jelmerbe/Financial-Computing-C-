//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
//********************************************************************
// knock_out_payoff implementation
//********************************************************************
template<typename ko_cond>
pmc::knock_out_payoff<ko_cond>::
knock_out_payoff(payoff_ptr PtrPayoff,
		 ko_cond KOCond,
		 unsigned int iPathDepAccuracy)
  : PtrPayoffIfNotKO_(PtrPayoff),
    KOCond_(KOCond),
    iPathDepAccuracy_(iPathDepAccuracy)
{}

template<typename ko_cond>
pmc::knock_out_payoff<ko_cond>::
knock_out_payoff(mc::payoff<mc::bvector> * PtrPayoff,
		 ko_cond KOCond,
		 unsigned int iPathDepAccuracy)
  : PtrPayoffIfNotKO_(PtrPayoff),
    KOCond_(KOCond),
    iPathDepAccuracy_(iPathDepAccuracy)
{}	


template<typename ko_cond>
mc::bvector & pmc::knock_out_payoff<ko_cond>::
operator()(path_out & poArg, mc::bvector & bvOut)
{
  unsigned int iPathDepAccuracy=
    std::min(iPathDepAccuracy_,poArg.MaxAccuracy());
  KOCond_.Reset();
  bool isNotKO(true);
  mc::dyadic dyadStep(0,iPathDepAccuracy);
  unsigned int i=0;
  unsigned int iMaxSteps=(1<<iPathDepAccuracy);
  while(isNotKO && i<iMaxSteps){
    isNotKO= !(KOCond_(poArg.find(dyadStep)->second));
    ++dyadStep;
    ++i;
  }
  if(isNotKO)
    return ((*PtrPayoffIfNotKO_)(poArg,bvOut));
  else {
    bvOut.resize(SizePayoff());
    return (bvOut*=mc::scalar(0));
  }
}

template<typename ko_cond>
unsigned int pmc::knock_out_payoff<ko_cond>::
SizePayoff() const
{
  return (*PtrPayoffIfNotKO_).SizePayoff();
}
