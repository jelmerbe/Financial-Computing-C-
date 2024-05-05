
#include "ExamQ4/Exam2023Q4Exercises.hpp"
#include <numeric> // for accumulate
#include <algorithm> // for max element

// constructor
exercises::exam_payoff::exam_payoff(unsigned int samplingScale, mc::scalar barrier)
: m_samplingScale(samplingScale), m_barrier(barrier){}

// operator
mc::bvector &exercises::exam_payoff::operator()(mc::payoff<boost::numeric::ublas::vector<double>>::path_out &poArg,
                                                mc::bvector &bvOut) {

    mc::dyadic dyad(0, m_samplingScale);
    double delta = poArg.TimeHorizon() * dyad.GetLength();
    double k = 1 << m_samplingScale;
    double kStar = 0.0;
    bvOut.resize(SizePayoff());
    std::vector<double> Rk(k, 1.0);

    // find Rk
    for (int i = 1; i < k; i++, dyad++){
        // find sum over Yk (Yt)
        auto Ytj = poArg.find(dyad) -> second;
        double Yt = std::accumulate(Ytj.begin(), Ytj.end(), 0.0);
        double d = Ytj.size();

        // find Rk
        Rk[i] = Rk[i -1] * ( 1 + delta * Yt / (d + 1));
    }

    // find K* and adjust Rk accordingly
    if ( *max_element(Rk.begin(), Rk.end()) < m_barrier){
        kStar = k;
    }
    else {
        // find min value of k such that Rk[i] stays under barrier.
        for (int i = 0; i < k; ++i) {
            if (Rk[i] > m_barrier) {
                kStar = i;
                break;
            }
        }
    }

    double tstar = kStar * pow(2, -m_samplingScale) * poArg.TimeHorizon();
    bvOut[0] = Rk[kStar] * tstar;
    return bvOut;
}

// size payoff
unsigned int exercises::exam_payoff::SizePayoff() const {
    return 1;
}
