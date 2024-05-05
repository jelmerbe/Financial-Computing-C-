
#include "ExamQ3/Exam2023Q3Exercises.hpp"
#include "MCLib/particular_payoff_statistics.hpp"
#include "MCLib/vec_ops_setup.hpp"
#include "MCLib/particular_factory.hpp"
#include "MCLib/utils.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace exercises;
using namespace utils;
using namespace vecop;

void test_reference_callable(unsigned int iX, unsigned int iY, MyStream & mystream);

const string fileName = (string)COURSE_OUTPUT_DIR + "/Exam/ExamQ3/ExamQ3_output.txt";

int main()
{
    cout << "Output being written to: " << fileName << endl;
	fstream myfile;
    myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
    mystream << "\n";
    mystream << "\n";

    test_reference_callable(30,30, mystream);

	myfile.close();
	return 0;
}

mc::bvector mkbv(std::vector<mc::scalar> const& x)
{
    mc::bvector v(x.size());
    std::copy(x.cbegin(), x.cend(), v.begin());
    return v;
}

class Coupon : public mc::time_dependent_payoff<mc::bvector>
{
public:
    Coupon(mc::scalar fixedArg, mc::scalar strikeArg, mc::scalar weightArg) :
        fixed(fixedArg), strike(strikeArg), weight(weightArg) {}

    mc::bvector & operator()(
            path_out & pFactors,
            const mc::dyadic & dTimeStep,
            mc::bvector & bvValue)
    {
        bvValue.resize(s);
        mc::bvector const &yt = pFactors.find(dTimeStep)->second;
        bvValue[0] = fixed + std::max(yt[0] * weight + yt[1] * (1.0 - weight) - strike, 0.0);
        return bvValue;
    }

    unsigned int SizePayoff() const
    {
        return s;
    }

private:
    mc::scalar fixed, strike, weight;
    const unsigned int s = 1;
};



void test_reference_callable(unsigned int iX, unsigned int iY, MyStream & mystream)
{

    mystream << "*******************************************\n" ;
    mystream << "*      TESTING test_general_callable      *\n" ;
    mystream << "*******************************************\n" ;

    typedef equation_setup base_equation_setup;
    typedef geometricBM2D_setup particular_equation_setup;
    typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;
    typedef exercises::reference_callable general_callable;
    typedef std::vector<reference_callable::Function> fvector;

    mc::scalar mu1(0.001), sigma1(0.1), mu2(0.00075), sigma2(0.2), rho(0.3), sT(1.0), sR(0.001);
    particular_equation_setup pesEquation(mu1,sigma1,mu2,sigma2,rho);
    particular_factory pfFactory(pesEquation);

    // setting up initial grid
    std::vector<mc::bvector> factorsAt0;
    mc::scalar coordinateMin(0.7), range(0.6), xStep=range/mc::scalar(iX), yStep=range/mc::scalar(iY);
    mc::scalar xCoordinate(coordinateMin);
    for(unsigned int x=0; x < iX; x++, xCoordinate+=xStep)
    {
        mc::scalar yCoordinate(coordinateMin);
        for(unsigned int y=0; y < iY; y++, yCoordinate += yStep)
        {
            factorsAt0.push_back(mkbv({xCoordinate,yCoordinate}));
        }
    }

    //setting up test functions
    fvector testFunctions;
    unsigned int iMaxDegree(3);
    testFunctions.push_back([](bvector const& ){return mc::scalar(1.0);});
    testFunctions.push_back([](bvector const& v){return v[0];});
    testFunctions.push_back([](bvector const& v){return v[1];});
    testFunctions.push_back([](bvector const& v){return v[0] * v[0];});
    testFunctions.push_back([](bvector const& v){return v[1] * v[1];});
    testFunctions.push_back([](bvector const& v){return v[0] * v[1];});


    mc:scalar fixedW1(- coordinateMin - 0.5 * range), strikeW1(0.0), weightW1(1.0),
              fixedW2(- coordinateMin - 0.5 * range), strikeW2(0.0), weightW2(0.0),
              fixedV1(1.0), fixedV2(2.0), strike(10000.0), weight(0.0);


    Coupon couponW1(fixedW1, strikeW1, weightW1),
           couponW2(fixedW2, strikeW2, weightW2),
           couponV1(fixedV1, strike, weight),
           couponV2(fixedV2, strike, weight),
           couponZ(-1000.0, strike, weight);

    unsigned int iCouponScale = 3;
    unsigned int iNumericalSDEAccuracy = 4;
    //initialising the option pricers
    reference_callable mainCallable(factorsAt0, iCouponScale, iNumericalSDEAccuracy, sT, sR,
                                pfFactory,  couponW1, couponW2, couponV1, couponV2, testFunctions);

    reference_callable v1Callable(factorsAt0, iCouponScale, iNumericalSDEAccuracy, sT, sR,
                                pfFactory,  couponW1, couponZ, couponV1, couponV2, testFunctions);

    reference_callable v2Callable(factorsAt0, iCouponScale, iNumericalSDEAccuracy, sT, sR,
                                  pfFactory,  couponZ, couponW2, couponV1, couponV2, testFunctions);


    //using option pricer
    //setting up test values for initial condition
    std::vector<mc::bvector> testVals;
    std::vector<mc::scalar> sample{0.25, 0.5, 0.75};
    for(mc::scalar x : sample)
    {
        for(mc::scalar y : sample)
        {
            testVals.push_back(mkbv({coordinateMin + range * x, coordinateMin + range * y}));
        }
    }

      for(auto & testVal : testVals)
      {
        mc::bvector bvEstimates;
        mystream << "Initial state: " << testVal << "\n";
        mainCallable(testVal, bvEstimates);
        mystream << "\tEstimated PV of callable option:\t" << std::setprecision(5) << bvEstimates << "\n";
        v1Callable(testVal, bvEstimates);
        mystream << "\tEstimated PV of underlying V1 cash-flow:\t" << std::setprecision(5) << bvEstimates << "\n";
        v2Callable(testVal, bvEstimates);
        mystream << "\tEstimated PV of underlying V2 cash-flow:\t" << std::setprecision(5) << bvEstimates << "\n";
      }
}



