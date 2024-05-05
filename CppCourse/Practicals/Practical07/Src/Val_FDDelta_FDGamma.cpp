//
// Created by Jelmer Bennema on 1/6/24.
//

#include "Practical07/Practical07Exercises.hpp"

class path_out;

void exercises::Val_FDDelta_FDGamma(unsigned int iLocalAccuracy, unsigned int iGlobalAccuracy,
                                    unsigned int iNumberOfPaths, mc::scalar sT, mc::bvector &ppoInCond, mc::scalar eps,
                                    mc::mc_factory<mc::bvector, mc::bvector> &ParticularFactory,
                                    mc::payoff<mc::bvector> &ParticularPayoff, mc::statistics &ParticularStatisticsVal,
                                    mc::statistics &ParticularStatisticsDelta,
                                    mc::statistics &ParticularStatisticsGamma) {

    typedef mc::mc_factory<mc::bvector,mc::bvector> factory;
    typedef factory::path_out path_out;
    typedef factory::path_in_ptr path_in;

    mc::bvector bvPayS, bvPayUp, bvPayDown;
    mc::bvector ValUp; mc::bvector ValDown;
    mc::bvector epss(ppoInCond.size(), eps);

    ValUp = ppoInCond + epss;
    ValDown = ppoInCond - epss;

    for (unsigned int i = 0; i < iNumberOfPaths; ++i) {

        // generate noise input
        path_in pi_ptr = ParticularFactory.GetNewPathInPtr(iLocalAccuracy, sT);

        //find paths out
        path_out poPath(ParticularFactory.GetNewPathOut(pi_ptr, iLocalAccuracy,
                                                        iGlobalAccuracy, ppoInCond, sT));
        path_out poPathUp(ParticularFactory.GetNewPathOut(pi_ptr,iLocalAccuracy,
                                                          iGlobalAccuracy, ValUp, sT));
        path_out poPathDown(ParticularFactory.GetNewPathOut(pi_ptr, iLocalAccuracy,
                                                            iGlobalAccuracy, ValDown, sT));

        // find payoffs
        ParticularPayoff(poPath, bvPayS);
        ParticularPayoff(poPathUp, bvPayUp);
        ParticularPayoff(poPathDown, bvPayDown);

        // dump statistics of Val
        ParticularStatisticsVal.DumpOnePayoff(bvPayS);

        // find sensitivities and dump
        mc::bvector Delta = (bvPayUp - bvPayDown) / 2 * eps;
        mc::bvector Gamma = (bvPayUp - 2 * bvPayS + 2 * bvPayDown) / eps * eps;

        ParticularStatisticsDelta.DumpOnePayoff(Delta);
        ParticularStatisticsGamma.DumpOnePayoff(Gamma);
    }

}