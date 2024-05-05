//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PARTICULAR_KO_PAYOFF_H__
#define _PARTICULAR_KO_PAYOFF_H__

#include "MCLib/base_payoff_statistics.hpp"

namespace pmc
{
	/** \class knock_out_payoff
	\brief knock_out_payoff is a particular payoff

	knock_out_payoff implements a path dependent option. The knock out condition is checked
	along the path. If the option is not knocked out, the data member payoff function object
	is evaluated, otherwise the zero vector is returned as payoff.
*/
template<typename ko_cond>
class knock_out_payoff : public mc::payoff<mc::bvector>
{
public:
  typedef sptr::shared_ptr<mc::payoff<mc::bvector> > payoff_ptr;//!<smart pointer to payoff

	/** constructor
	* @param PtrPayoff sets the payoff for the not knocked out case
	* @param KOCond sets the knock out condition
	* @param iPathDepAccuracy sets the scale on which the knock out condition is checked
	  */
  knock_out_payoff(payoff_ptr PtrPayoff,
		   ko_cond KOCond,
		   unsigned int iPathDepAccuracy=0);

	/** constructor
	* @param PtrPayoff sets the payoff for the not knocked out case
	* @param KOCond sets the knock out condition
	* @param iPathDepAccuracy sets the scale on which the knock out condition is checked
	  */
  knock_out_payoff(mc::payoff<mc::bvector> * PtrPayoff,
		   ko_cond KOCond,
		   unsigned int iPathDepAccuracy=0);


	/** operator()
	 * @param poArg path argument along which the payoff to be worked out
	 * @param bvOut result is written into
	 * @return reference to bvOut
	  */
  mc::bvector & operator()(path_out & poArg, mc::bvector & bvOut);

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	 */
  unsigned int SizePayoff() const;

private:
  payoff_ptr PtrPayoffIfNotKO_;//!< points to the payoff component
  ko_cond KOCond_;//!< template type function object, bool operator(bvector) member is assumed
  unsigned int iPathDepAccuracy_;//!< defines the scale on which the KO kondition is checked
};

}


#include "MCLib/Inl/particular_ko_payoff.inl"


#endif //_PARTICULAR_KO_PAYOFF_H__
