#ifndef _EXAM2015_QUESTION_4_HPP__
#define _EXAM2015_QUESTION_4_HPP__

#include "MCLib/base_payoff_statistics.hpp"
#include "MCLib/particular_payoff_statistics.hpp"
#include "MCLib/base_factory.hpp"
#include <vector>

namespace exercises
{

static std::string sMyName("1079868");

/** \class exam_payoff	
*/
class exam_payoff : 
    public mc::payoff<mc::bvector>
{
public:
	/** constructor
	* @param strike
	* @param rate
	* @param fl
	* @param iSamplingAccuracy
	*/
  exam_payoff(mc::scalar strike, mc::scalar rate, mc::scalar fl, unsigned int iSamplingAccuracy);

	/** operator()
	 * @param poArg path argument along which the payoff to be worked out
	 * @param bvOut result is written into
	 * @return reference to bvOut
	  */
  mc::bvector & operator()(path_out & poArg,
			   mc::bvector & bvOut);

	/** SizePayoff()
	* @return the size of the evaluated payoff vector
	 */
  unsigned int SizePayoff() const;

private:
  mc::scalar m_strike, m_rate, m_floor;
  unsigned int m_iSamplingAccuracy;
};

}

#endif //_EXAM2015_QUESTION_4_HPP__
