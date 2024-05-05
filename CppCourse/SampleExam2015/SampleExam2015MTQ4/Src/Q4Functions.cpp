//
// Created by Jelmer Bennema on 1/11/24.
//

#include "SampleExam2015MTQ4/SampleExam2015Q4Exercises.hpp"

/** constructor
	* @param strike
	* @param rate
	* @param fl
	* @param iSamplingAccuracy
	*/
exercises::exam_payoff::exam_payoff(mc::scalar strike, mc::scalar rate, mc::scalar fl, unsigned int iSamplingAccuracy)
: m_strike(strike), m_rate(rate), m_floor(fl), m_iSamplingAccuracy(iSamplingAccuracy){}

/** operator()
 * @param poArg path argument along which the payoff to be worked out
 * @param bvOut result is written into
 * @return reference to bvOut
  */
mc::bvector & exercises::exam_payoff::operator()(path_out & poArg,
                         mc::bvector & bvOut){

    bvOut.resize(SizePayoff());
    mc::dyadic dyad(0,m_iSamplingAccuracy);
    unsigned int n = (1<<m_iSamplingAccuracy); //number of dyadic steps taken in total

    // find payoff
    for (int k = 0; k < n; k++, dyad++){

        // find max value of Y
        auto Y_k = poArg.find(dyad) -> second;
        mc::scalar max = 0.0;

        for (unsigned int j = 0; j < Y_k.size(); j++){
            if (Y_k[j] > m_floor && Y_k[j] > max){
                max = Y_k[j];
            }
        }

        // add to vector X0
        mc::scalar payoff = max - m_strike * exp(m_rate * k * dyad.GetLength());
        if (payoff > 0){
            bvOut[0] += payoff;
        }
    }

    return bvOut;
}

/** SizePayoff()
* @return the size of the evaluated payoff vector
 */
unsigned int exercises::exam_payoff::SizePayoff() const {
    return 1;
}

