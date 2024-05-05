
#include "Practical07/Practical07Exercises.hpp"
#include "MCLib/particular_path_generator.hpp"
//#include "MCLib/particular_numerical_step.hpp"
//#include "MCLib/particular_strategy.hpp"
//#include "DOPLib/DifferentialOperator_particular_setup.hpp"
#include "MCLib/vec_ops_setup.hpp"
#include "MCLib/particular_factory.hpp"
#include "MCLib/particular_payoff_statistics.hpp"
#include "MCLib/particular_ko_conditions.hpp"
#include "MCLib/particular_ko_payoff.hpp"
//#include "MCLib/utils.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <vector>
#include <iostream>
//#include <fstream>
#include <cmath>

using namespace std;
using namespace exercises;
using namespace utils;
using namespace vecop;

void testMCFDGreeks(unsigned int, MyStream & mystream);
void test_UpRangeOut(unsigned int iNumSim, MyStream & mystream);
void test_basket(MyStream & mystream);
void test_geometric_average(MyStream & mystream);
void test_half_call_half_put(MyStream & mystream);

const string fileName = (string)COURSE_OUTPUT_DIR + "/Practicals/Practical07/Practical07_output.txt";
int main()
{
    cout << "Output being written to: " << fileName << "\n";
	fstream myfile;
	myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
    mystream << "\n";
    mystream << "\n";

	test_UpRangeOut(1000, mystream);
	test_basket(mystream);
	test_geometric_average(mystream);
	test_half_call_half_put(mystream);
	testMCFDGreeks(1000, mystream);

	myfile.close();
	return 0;
}

void testMCFDGreeks(unsigned int iNumberOfPaths, MyStream & mystream)
{
		
  typedef equation_setup base_equation_setup;
	//typedef boost::shared_ptr<base_equation_setup> base_equation_setup_ptr;
  typedef geometricBM1D_setup particular_equation_setup;

	//typedef mc::mc_factory<path_piece_in,path_piece_out> base_mc_factory;
  typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;

	//typedef mc::payoff<path_piece_out> base_payoff;
	//typedef mc::statistics base_statistics;

	//setting up factory using particular ingredients
  mc::scalar mu(0.05), sigma(0.2);
  particular_equation_setup pesEquation(mu,sigma);
  base_equation_setup & Equation=pesEquation;
  particular_factory factory(Equation);
	
	
	//setting up payoff
  mc::bvector bvStrikes(3);
  bvStrikes[0]=0.8;
  bvStrikes[1]=0.85;
  bvStrikes[2]=0.9;
  pmc::european_calls_payoff payoff(bvStrikes);
	//time horizon
  mc::scalar sT(0.25);
	//initial condition
  mc::bvector ppoInCond(1);
  ppoInCond[0]=0.8;
  mc::scalar dDiscount = exp(-mu*sT);
  unsigned int iLocalAccuracy(6);
  unsigned int iGlobalAccuracy(0);
  mc::scalar eps(1.0e-4);

  mystream<< "*********************************************" << "\n";
  mystream <<"*          Testing FDSensitivities          *" << "\n";
  mystream<< "*********************************************" << "\n";
  mystream<< "\n";

  pmc::mean_variance_statistics statVal, statDelta, statGamma;
  Val_FDDelta_FDGamma(iLocalAccuracy,
		      iGlobalAccuracy,
		      iNumberOfPaths,
		      sT,
		      ppoInCond,
		      eps,
		      factory,
		      payoff,
		      statVal,
		      statDelta,
		      statGamma);



  std::vector<mc::bvector> statValuesVal   = statVal.GetStatistics();
  std::vector<mc::bvector> statValuesDelta = statDelta.GetStatistics();
  std::vector<mc::bvector> statValuesGamma = statGamma.GetStatistics();

  for(unsigned int i=0; i<3; i++){
    mystream << "Strike: " <<  bvStrikes[i] << "\n";
    mystream << "Estimated option value: " << statValuesVal[0][i]*dDiscount << "\n";
    mystream << "3sigma confidence interval: [" << (statValuesVal[0][i]-3.0*statValuesVal[2][i])*dDiscount 
	   << ", " << (statValuesVal[0][i]+3.0*statValuesVal[2][i])*dDiscount << "]" << "\n";
    mystream << "Exact value: " << BSOptionPrice(ppoInCond[0],bvStrikes[i],sT,mu,sigma) << "\n";
    mystream << "Estimated delta: " << statValuesDelta[0][i]*dDiscount << "\n";
    mystream << "3sigma confidence interval: [" << (statValuesDelta[0][i]-3.0*statValuesDelta[2][i])*dDiscount
	   << ", " << (statValuesDelta[0][i]+3.0*statValuesDelta[2][i])*dDiscount << "]" << "\n";
    mystream << "Exact delta: " << BSDelta(ppoInCond[0],bvStrikes[i],sT,mu,sigma) << "\n";
    mystream << "Estimated gamma: " << statValuesGamma[0][i]*dDiscount << "\n";
    mystream << "3sigma confidence interval: [" << (statValuesGamma[0][i]-3.0*statValuesGamma[2][i])*dDiscount
	   << ", " << (statValuesGamma[0][i]+3.0*statValuesGamma[2][i])*dDiscount << "]" << "\n";
    mystream << "Exact gamma: " << BSGamma(ppoInCond[0],bvStrikes[i],sT,mu,sigma) << "\n";
    mystream << "\n";
  }

}

void test_UpRangeOut(unsigned int iNumSim, MyStream & mystream)
{
    mystream << "*******************************************" << "\n";
	mystream << "*           TESTING UpRangeOut            *" << "\n";
	mystream << "*******************************************" << "\n";
	
	typedef mc::bvector path_piece_in;
	typedef mc::bvector path_piece_out;
	//typedef mc::path<path_piece_in> path_in;
	//typedef mc::path<path_piece_out> path_out;
	//typedef boost::shared_ptr<path_in> path_in_ptr;

	typedef equation_setup base_equation_setup;
	//typedef boost::shared_ptr<base_equation_setup> base_equation_setup_ptr;
	typedef geometricBM1D_setup particular_equation_setup;

	typedef mc::mc_factory<path_piece_in,path_piece_out> base_mc_factory;
	//typedef boost::shared_ptr<base_mc_factory> base_mc_factory_ptr;

	typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;
	//typedef boost::shared_ptr<particular_factory> particular_factory_ptr;


	//typedef particular_factory::path_in path_in;
	typedef particular_factory::path_out path_out;
	//typedef boost::shared_ptr<path_in> path_in_ptr;


	typedef mc::payoff<path_piece_out> base_payoff;
	typedef mc::statistics base_statistics;

	//setting up factory using particular ingredients
	mc::scalar mu(0.1), sigma(0.25);
	particular_equation_setup pesEquation(mu,sigma);
	base_equation_setup & Equation=pesEquation;
	particular_factory pfFactory(Equation);
	base_mc_factory & Factory=pfFactory;

	//using factory
	unsigned int iAccuracyLimit(5);
	mc::scalar sT(2.0);
	
	//initial condition
	mc::bvector fInCond(1);
	fInCond[0]=1.0;
	
	//setting up payoff
	mc::bvector bvStrikes(1);
	bvStrikes[0]=0.85;
	
	
	mc::scalar sUpperBarrier(1.25);
	unsigned int iNumberOfeventsBarrier1(8),iNumberOfeventsBarrier2(16),iNumberOfeventsBarrier3(32);

	
	pmc::knock_out_payoff<exercises::UpRangeOut> koPayoff1(new pmc::european_calls_payoff(bvStrikes),
											exercises::UpRangeOut(sUpperBarrier,iNumberOfeventsBarrier1),iAccuracyLimit);
	pmc::knock_out_payoff<exercises::UpRangeOut> koPayoff2(new pmc::european_calls_payoff(bvStrikes),
											exercises::UpRangeOut(sUpperBarrier,iNumberOfeventsBarrier2),iAccuracyLimit);
	pmc::knock_out_payoff<exercises::UpRangeOut> koPayoff3(new pmc::european_calls_payoff(bvStrikes),
											exercises::UpRangeOut(sUpperBarrier,iNumberOfeventsBarrier3),iAccuracyLimit);
	
	

	base_payoff & Payoff1=koPayoff1;
	base_payoff & Payoff2=koPayoff2;
	base_payoff & Payoff3=koPayoff3;

	//setting up statistics
	pmc::mean_variance_statistics mvStatistics1, mvStatistics2, mvStatistics3;
	base_statistics & Statistics1=mvStatistics1;
	base_statistics & Statistics2=mvStatistics2;
	base_statistics & Statistics3=mvStatistics3;

	mc::bvector bvValue(1);

	for(unsigned int i=0; i<iNumSim; ++i)
	{
		path_out poPath(Factory.GetNewPathOut(iAccuracyLimit,iAccuracyLimit,fInCond,sT));
	    Statistics1.DumpOnePayoff(Payoff1(poPath,bvValue));
		Statistics2.DumpOnePayoff(Payoff2(poPath,bvValue));
		Statistics3.DumpOnePayoff(Payoff3(poPath,bvValue));
	}
	vector<mc::bvector> StatVal1=Statistics1.GetStatistics();
	vector<mc::bvector> StatVal2=Statistics2.GetStatistics();
	vector<mc::bvector> StatVal3=Statistics3.GetStatistics();
	mystream<< "\n";

	mystream<< "Sample size: " << iNumSim << "\n";
	mystream<< "Up-Range-Out knock out option" << "\n";
	mystream<< "Upper barrier: " << sUpperBarrier << "\n";
	mystream<< "Number of barrier events: " << iNumberOfeventsBarrier1 << "\n";
	mystream<< "Time to maturity: " << sT << "\n";
	mystream<< "Strike: " << bvStrikes[0] <<  "\n";
	mystream<< " Option value: " << StatVal1[0][0] << "\n";
	mystream<< " Option stdev: " << StatVal1[2][0] <<  "\n";
	mystream<< "\n";
	mystream<< "Up-Range-Out knock out option" << "\n";
	mystream<< "Upper barrier: " << sUpperBarrier << "\n";
	mystream<< "Number of barrier events: " << iNumberOfeventsBarrier2 << "\n";
	mystream<< "Time to maturity: " << sT << "\n";
	mystream<< "Strike: " << bvStrikes[0] <<  "\n";
	mystream<< " Option value: " << StatVal2[0][0] << "\n";
	mystream<< " Option stdev: " << StatVal2[2][0] << "\n";
	mystream<< "Up-Range-Out knock out option" << "\n";
	mystream<< "Upper barrier: " << sUpperBarrier << "\n";
	mystream<< "Number of barrier events: " << iNumberOfeventsBarrier3 << "\n";
	mystream<< "Time to maturity: " << sT << "\n";
	mystream<< "Strike: " << bvStrikes[0] <<  "\n";
	mystream<< " Option value: " << StatVal3[0][0] << "\n";
	mystream<< " Option stdev: " << StatVal3[2][0] << "\n";
	mystream<< "\n";
}

void test_geometric_average(MyStream & mystream)
{
	mystream << "*******************************************" << "\n";
	mystream << "*    TESTING geometric_average_payoff     *" << "\n";
	mystream << "*******************************************" << "\n";
	
	//typedef mc::bvector path_piece_in;
	//typedef mc::bvector path_piece_out;
	//typedef mc::path<path_piece_in> path_in;
	//typedef mc::path<path_piece_out> path_out;
	//typedef boost::shared_ptr<path_in> path_in_ptr;

	typedef equation_setup base_equation_setup;
	typedef geometricBM2D_setup particular_equation_setup;

	typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;
	//typedef boost::shared_ptr<particular_factory> particular_factory_ptr;

	//typedef particular_factory::path_in path_in;
	typedef particular_factory::path_out path_out;
	//typedef boost::shared_ptr<path_in> path_in_ptr;


	//setting up factory using particular ingredients
	mc::scalar mu1(0.1), sigma1(0.25), mu2(0.2), sigma2(0.35), rho(0.7);
	particular_equation_setup pesEquation(mu1,sigma1,mu2,sigma2,rho);
	base_equation_setup & Equation=pesEquation;
	particular_factory pfFactory(Equation);
	
	//using factory
	unsigned int iAccuracyLimit(2);
	mc::scalar sT(2.0);
	
	//initial condition
	mc::bvector fInCond(2);
	fInCond[0]=1.0;
	fInCond[1]=1.2;
		
	unsigned int index(1);
	exercises::geometric_average_payoff geometricAveragePayoff(iAccuracyLimit,index);
	
	path_out poPath(pfFactory.GetNewPathOut(iAccuracyLimit,iAccuracyLimit,fInCond,sT));


	mc::bvector bvValue;
	for(int i=0; i<(1<<iAccuracyLimit); ++i)
	{
		mc::dyadic dyadicTemp(i,iAccuracyLimit);
		mystream << "factors at time: " << mc::scalar(i)/mc::scalar(1<<iAccuracyLimit) << " - " << poPath.find(dyadicTemp)->second << "\n";
	}
	mystream << "Geometric average of coordinate: " << index << " - " << geometricAveragePayoff(poPath,bvValue) << "\n";

}


void test_basket(MyStream & mystream)
{

	mystream << "*******************************************" << "\n";
	mystream << "*         TESTING basket_payoff           *" << "\n";
	mystream << "*******************************************" << "\n";

	//typedef mc::bvector path_piece_in;
	//typedef mc::bvector path_piece_out;
	//typedef mc::path<path_piece_in> path_in;
	//typedef mc::path<path_piece_out> path_out;
	//typedef boost::shared_ptr<path_in> path_in_ptr;

	typedef equation_setup base_equation_setup;
	typedef geometricBM2D_setup particular_equation_setup;

	typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;
	//typedef boost::shared_ptr<particular_factory> particular_factory_ptr;

	//typedef particular_factory::path_in path_in;
	typedef particular_factory::path_out path_out;
	//typedef boost::shared_ptr<path_in> path_in_ptr;


	//setting up factory using particular ingredients
	mc::scalar mu1(0.1), sigma1(0.25), mu2(0.2), sigma2(0.35), rho(0.7);
	particular_equation_setup pesEquation(mu1,sigma1,mu2,sigma2,rho);
	base_equation_setup & Equation=pesEquation;
	particular_factory pfFactory(Equation);

	//using factory
	unsigned int iAccuracyLimit(0);
	mc::scalar sT(2.0);

	//initial condition
	mc::bvector fInCond(2);
	fInCond[0]=1.0;
	fInCond[1]=1.2;

	exercises::basket_payoff basketPayoff(2);

	path_out poPath(pfFactory.GetNewPathOut(iAccuracyLimit,iAccuracyLimit,fInCond,sT));


	mc::bvector bvValue;
	mystream << "Time-t value of factors: " << poPath.find(mc::dyadic(0,0))->second << "\n";
	mystream << "Basket payoff value:     " << basketPayoff(poPath,bvValue) << "\n";

}


void test_half_call_half_put(MyStream & mystream)
{
	mystream << "*******************************************" << "\n";
	mystream << "*       TESTING half_call_half_put        *" << "\n";
	mystream << "*******************************************" << "\n";
	
	//typedef mc::bvector path_piece_in;
	//typedef mc::bvector path_piece_out;
	//typedef mc::path<path_piece_in> path_in;
	//typedef mc::path<path_piece_out> path_out;
	//typedef boost::shared_ptr<path_in> path_in_ptr;

	typedef equation_setup base_equation_setup;
	typedef geometricBM2D_setup particular_equation_setup;

	typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;
	//typedef boost::shared_ptr<particular_factory> particular_factory_ptr;

	//typedef particular_factory::path_in path_in;
	typedef particular_factory::path_out path_out;
	//typedef boost::shared_ptr<path_in> path_in_ptr;

	//setting up factory using particular ingredients
	mc::scalar mu1(0.1), sigma1(0.25), mu2(0.2), sigma2(0.35), rho(0.7);
	particular_equation_setup pesEquation(mu1,sigma1,mu2,sigma2,rho);
	base_equation_setup & Equation=pesEquation;
	particular_factory pfFactory(Equation);
	
	//using factory
	unsigned int iAccuracyLimit(5);
	mc::scalar sT(2.0);
	
	//initial condition
	mc::bvector fInCond(2);
	fInCond[0]=1.0;
	fInCond[1]=0.5;

	//setting up strikes
	mc::bvector bvStrikes(2);
	bvStrikes[0]=0.7;
	bvStrikes[1]=1.7;
		
	unsigned int index(1);
	exercises::half_call_half_put HCHPPayoff(bvStrikes,index);
	
	path_out poPath(pfFactory.GetNewPathOut(iAccuracyLimit,iAccuracyLimit,fInCond,sT));


	mc::bvector bvValue;
	mc::dyadic dyadicTemp1((1<<(iAccuracyLimit-1))-1,iAccuracyLimit);
	mc::dyadic dyadicTemp2((1<<(iAccuracyLimit-1))+2,iAccuracyLimit);

	mystream << "Strikes: " << bvStrikes << "\n";
	mystream << "Factors at time: " << 
		mc::scalar(dyadicTemp1.Position())/mc::scalar(1<<iAccuracyLimit) << " - " <<
		poPath.find(dyadicTemp1)->second << "\n";
	mystream << "Half call half put of coordinate: " << index << " - " << HCHPPayoff(poPath,dyadicTemp1,bvValue) << "\n";
	mystream << "Factors at time: " << 
		mc::scalar(dyadicTemp2.Position())/mc::scalar(1<<iAccuracyLimit) << " - " <<
		poPath.find(dyadicTemp2)->second << "\n";
	mystream << "Half call half put of coordinate: " << index << " - " << HCHPPayoff(poPath,dyadicTemp2,bvValue) << "\n";
}
