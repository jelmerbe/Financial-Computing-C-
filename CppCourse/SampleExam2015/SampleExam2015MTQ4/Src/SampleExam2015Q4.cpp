
#include "SampleExam2015MTQ4/SampleExam2015Q4Exercises.hpp"
#include "MCLib/particular_path_generator.hpp"
//#include "DOPLib/DifferentialOperator_particular_setup.hpp"
#include "MCLib/vec_ops_setup.hpp"
#include "MCLib/particular_factory.hpp"
#include "MCLib/particular_ko_conditions.hpp"
#include "Utils//UtilityFunctions.hpp"
#include <boost/math/constants/constants.hpp>
#include <vector>
#include <iostream>
#include <iomanip>


using namespace std;
using namespace exercises;
using namespace utils;
using namespace vecop;


void test_exam_payoff(MyStream & mystream);


const string fileName = (string)COURSE_OUTPUT_DIR + "/SampleExam2015/SampleExam2015MTQ4/SampleExamQ4_output.txt";
int main()
{
  cout << "Output being written to: " << fileName << "\n";
  fstream myfile;
  myfile.open (fileName, ios::in | ios::out | ios::trunc);
  MyStream mystream(myfile);
  myfile << "\n";
  myfile << sMyName << "\n";
  myfile << "\n";

  test_exam_payoff(mystream);

  myfile.close();
  return 0;
}




void test_exam_payoff(MyStream & mystream)
{
  mystream << "*******************************************" << "\n";
  mystream << "*         TESTING exam_payoff             *" << "\n";
  mystream << "*******************************************" << "\n";
	
  typedef equation_setup base_equation_setup;
  typedef geometricBM2D_setup particular_equation_setup;

  typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;

  typedef particular_factory::path_out path_out;

	//setting up factory using particular ingredients
  mc::scalar mu1(0.15), sigma1(0.15), mu2(0.1), sigma2(0.2), rho(0.3);
  particular_equation_setup pesEquation(mu1,sigma1,mu2,sigma2,rho);
  base_equation_setup & Equation=pesEquation;
  particular_factory pfFactory(Equation);
	
	//using factory
  unsigned int iAccuracyLimit(3);
  unsigned int iSamplingAccuracy(iAccuracyLimit-1);
  mc::scalar sT(2.0);
	
	//initial condition
  mc::bvector fInCond(2);
  fInCond[0]=1.0;
  fInCond[1]=0.9;
		
  mc::scalar strike(1.01), rate(0.05), fl(1.15);
  exercises::exam_payoff payoff(strike, rate, fl, iSamplingAccuracy);

  mystream << "Parameters:" << "\n";
  mystream << "\tStrike: " << strike << "\n";
  mystream << "\tRate: " << rate << "\n";
  mystream << "\tFloor: " << fl << "\n";
  mystream << "\n";
  mystream << "Sampling accuracy: " << iSamplingAccuracy << "\n";
  mystream << "\n";
  unsigned int numberOfPaths(5);

  for(unsigned int i=0; i<numberOfPaths; i++){
    mystream << "Test trajectory no. " << i << "\n";  
    path_out poPath(pfFactory.GetNewPathOut(iAccuracyLimit,iAccuracyLimit,fInCond,sT));
    mc::bvector bvValue;
    for(int j=0; j<(1<<iAccuracyLimit); ++j){
      mc::dyadic dyadicTemp(j,iAccuracyLimit);
      mystream << "\tFactors at time: " << sT * mc::scalar(j+1) / mc::scalar(1<<iAccuracyLimit) << ": " << setprecision(10) << poPath.find(dyadicTemp)->second << "\n";
    }
    
    mystream << "\tPayoff value: " << payoff(poPath,bvValue) << "\n";
    mystream << "\n";

  }
}


