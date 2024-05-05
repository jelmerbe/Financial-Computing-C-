
#include "ExamQ3/Exam2023Q3Exercises.hpp"
#include <numeric>

// constructor - find out coefficients
exercises::reference_callable::reference_callable(const std::vector<path_piece_out> &factorsAt0,
                                                  unsigned int iCouponScale, unsigned int iNumericalSDEAccuracy,
                                                  mc::scalar sT, mc::scalar sR,
                                                  exercises::reference_callable::factory &ParticularFactory,
                                                  exercises::reference_callable::time_dependent_payoff &v1Payoff,
                                                  exercises::reference_callable::time_dependent_payoff &v2Payoff,
                                                  exercises::reference_callable::time_dependent_payoff &v3Payoff,
                                                  exercises::reference_callable::time_dependent_payoff &v4Payoff,
                                                  const exercises::reference_callable::fvector &testFunctions) {

    // initialize m_testfunctions
    m_TestFunctions = testFunctions;

    // find coefficients
    typedef factory::path_in_ptr path_in;
    mc::dyadic dyad(0,1);
    std::vector<std::vector<double>> V1, V2, V3, V4; // vector of doubles, rows are paths, times are columns
    mc::bvector C1, C2, C3, C4;
    double numberofpaths = 10000;

    for (int i = 0; i < numberofpaths; i++){
        // generate path
        path_out poPath(ParticularFactory.GetNewPathOut(iNumericalSDEAccuracy, iCouponScale, factorsAt0[0], sT));

        //initialize backward recursion
        auto YT = poPath.find(dyad) -> second;

        v1Payoff(YT, dyad, V1);
        v2Payoff(YT, dyad, V2);
        v3Payoff(YT, dyad, V3);
        v4Payoff(YT, dyad, V4);

        // run backward recursion for j = 1, 2, 3, 4
        double n = 1<<iNumericalSDEAccuracy;
        // loop backwards through time to find option value at T = 0
        for (unsigned int j = n; j > 0 ; j--){
            V1[i][j] = C1[j] + V1[i][j + 1];                  // option 1
            V2[i][j] = C2[j] + exercises::max(V1[i][j + 1], V2[i][j + 1]);    // option 2
            V3[i][j] = C3[j] + V3[i][j + 1];                  // option 3
            if (V2[i][j+1] > V1[i][j + 1]){                 // option 4
                V4[i][j] = C4[j] + V3[i][j+1];
            }
            else {V4[i][j] = C4[j] + V4[i][j+1]; }
        }
    }

    // now that we have all the option values at time zero, for this particular path, we can compute the regression statistics
    // store coefficients using regression functions for j = 1, 2, 3, 4

    // find expected value of option 4
    double Expectedfour = std::accumulate(V4[0].begin(), V4[0].end(), 0.0) / numberofpaths;
    m_Coefficients = Regression(poPath, factorsAt0, testFunctions);

}
