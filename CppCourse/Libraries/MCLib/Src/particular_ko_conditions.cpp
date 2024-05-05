#include "MCLib/particular_ko_conditions.hpp"

//********************************************************************
// UpAndOut implementation
//********************************************************************
pmc::UpAndOut::UpAndOut(mc::scalar sBarrier,
			unsigned int ind)
  : sBarrier_(sBarrier), ind_(ind)
{}

bool pmc::UpAndOut::operator()(const mc::bvector & bvArg) const
{
  return bvArg[ind_]>=sBarrier_;
}


//********************************************************************
// DoubleBarrier implementation
//********************************************************************
pmc::DoubleBarrier::DoubleBarrier(mc::scalar sUpperBarrier,
				  mc::scalar sLowerBarrier,
				  unsigned int ind)
  : sUpperBarrier_(sUpperBarrier),
    sLowerBarrier_(sLowerBarrier),
    ind_(ind)
{}

bool pmc::DoubleBarrier::operator()(const mc::bvector & bvArg) const
{
  return ((bvArg[ind_]<=sLowerBarrier_) || (bvArg[ind_]>=sUpperBarrier_));
}


//********************************************************************
// UpDownAndOut implementation
//********************************************************************
pmc::UpDownAndOut::UpDownAndOut(mc::scalar sUpperBarrier,
				 mc::scalar sLowerBarrier,
				 unsigned int ind)
  : sUpperBarrier_(sUpperBarrier),
    sLowerBarrier_(sLowerBarrier),
    UpCrossed_(false),
    ind_(ind)
{}

bool pmc::UpDownAndOut::operator()(const mc::bvector & bvArg)
{
  if(UpCrossed_)
    return (bvArg[ind_]<=sLowerBarrier_);
  else
    {
      UpCrossed_=(bvArg[ind_]>=sUpperBarrier_);
      return false;
    }
}

