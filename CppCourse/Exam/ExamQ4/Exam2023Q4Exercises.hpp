#ifndef _EXAM_2023_QUESTION_4_HPP__
#define _EXAM_2023_QUESTION_4_HPP__

#include "MCLib/base_payoff_statistics.hpp"
#include <functional>
#include <vector>

namespace exercises
{


/** \class exam_payoff
*/
class exam_payoff :
    public mc::payoff<mc::bvector>
{
public:
	/** constructor
	 * @param samplingScale defines main-sampling scale
     * @param barrier barrier
	 */
  exam_payoff(
          unsigned int samplingScale,
          mc::scalar barrier);

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
    unsigned int m_samplingScale;
    mc::scalar m_barrier;
};


}

#endif //_EXAM_2023_QUESTION_4_HPP__
