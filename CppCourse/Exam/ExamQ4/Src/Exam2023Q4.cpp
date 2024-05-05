
#include "ExamQ4/Exam2023Q4Exercises.hpp"
#include "MCLib/particular_factory.hpp"
#include "MCLib/utils.hpp"
#include "MCLib/vec_ops_setup.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace exercises;
using namespace utils;
using namespace vecop;

const string fileName = (string)COURSE_OUTPUT_DIR + "/Exam/ExamQ4/ExamQ4_output.txt";

void test_exam_payoff(MyStream &);

int main()
{
    cout << "Output being written to: " << fileName << endl;
	fstream myfile;
	myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
    mystream << "\n\n";

	test_exam_payoff(mystream);

    myfile.close();
	return 0;
}

typedef equation_setup base_equation_setup;
typedef geometricBM2D_setup particular_equation_setup;
typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;
typedef particular_factory::path_out path_out; 

mc::bvector mkbv(std::vector<mc::scalar> const& x)
{
    mc::bvector v(x.size());
    std::copy(x.cbegin(), x.cend(), v.begin());
    return v;
}

void test_helper(MyStream & mystream,
                 particular_factory & pfFactory,
                 mc::bvector & fInCond,
                 unsigned int iSamplingScale,
                 mc::scalar barrier,
                 unsigned int iAccuracyLimit,
                 unsigned int numberOfPaths,
                 mc::scalar  sT)
{

    exercises::exam_payoff payoff(iSamplingScale, barrier);


    mystream << "\n*******************************************" << "\n";
    mystream << "Parameters:" << "\n";
    mystream << "\tTime horizon:\t" << std::fixed << setprecision(4) << sT << "\n";
    mystream << "\tSampling scale:\t" << iSamplingScale << "\n";
    mystream << "\tBarrier:\t" << std::fixed << setprecision(4) << barrier << "\n";
    mystream << "\n";

    for(unsigned int i=0; i<numberOfPaths; i++)
    {
        mystream << "Test trajectory no. " << i << "\n";
        path_out poPath(pfFactory.GetNewPathOut(iAccuracyLimit,iAccuracyLimit,fInCond,sT));
        mystream << "\tFactors at time: " << fixed << setprecision(2) << 0.0 << ":\t"
                 << setprecision(6) << poPath.InitialValue() << "\n";

        mc::dyadic dyad(0, iAccuracyLimit);
        for(int j=0; j<(1<<iAccuracyLimit); ++j, ++dyad)
        {
            mc::scalar t = sT * mc::scalar(j+1) / mc::scalar(1<<iAccuracyLimit);
            mystream << "\tFactors at time: " << fixed << setprecision(2) << t << ":\t"
                     << setprecision(6) << poPath.find(dyad)->second << "\n";
        }

        mc::bvector bvValue;
        mystream << "\tPayoff value: " << payoff(poPath,bvValue) << "\n";
    }
    mystream << "*******************************************" << "\n";
}

void test_exam_payoff(MyStream & mystream)
{
    mystream << "*******************************************\n";
    mystream << "*         TESTING exam_payoff             *\n";
    mystream << "*******************************************\n";

    //setting up factory using particular ingredients
    mc::scalar mu1(0.001), sigma1(0.1), mu2(0.00075), sigma2(0.2), rho(0.3);
    particular_equation_setup pesEquation(mu1,sigma1,mu2,sigma2,rho);
    base_equation_setup & Equation=pesEquation;
    particular_factory pfFactory(Equation);

    //using factory
    unsigned int iAccuracyLimit(3);
    unsigned int numberOfPaths(2);
    mc::scalar sT(2.0);

    //initial condition
    mc::bvector fInCond = mkbv({0.1, 0.2});

    std::vector<double> barriers{1.1, 1.25};
    std::vector<unsigned int> samplingScales{2, 3};

    for (auto const& barrier : barriers)
    {
        for (auto const& samplingScale : samplingScales)
        {
            test_helper(mystream, pfFactory, fInCond, samplingScale, barrier, iAccuracyLimit, numberOfPaths, sT);
        }
    }
}

