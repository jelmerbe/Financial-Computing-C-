

#include "MCLib/particular_regressions.hpp"
#include "MCLib/vec_ops_setup.hpp"
#include "MCLib/particular_factory.hpp"
#include "MCLib/particular_payoff_statistics.hpp"
#include "MCLib/particular_ko_conditions.hpp"
#include "MCLib/particular_ko_payoff.hpp"
#include "MCLib/utils.hpp"
#include "MCLib/dyadic_interval.hpp"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
using namespace pmc;
using namespace vecop;

void test_payoffs(unsigned int iNumberOfPaths);
void test_EuropeanOptionPricer();
void test_BermudanOptionPricer();

int main()
{
	test_EuropeanOptionPricer();
	test_BermudanOptionPricer();
	test_payoffs(10000);
	return 0;
}


void test_payoffs(unsigned int iNumberOfPaths)
{
	cout << endl;
	cout << "*********************************************" << endl;
	cout << "*         TESTING VARIOUS PAYOFFS           *" << endl;
	cout << "*********************************************" << endl;
	cout << endl;
	cout << endl;

	typedef equation_setup base_equation_setup;
	typedef geometricBM1D_setup particular_equation_setup;
	typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;

	typedef particular_factory::path_in path_in;
	typedef particular_factory::path_out path_out;
	typedef sptr::shared_ptr<path_in> path_in_ptr;

	//setting up factory using particular ingredients
	unsigned int iAccuracy=5;
	mc::scalar sT(1.0), sR(0.05), sSigma(0.4);
	particular_equation_setup pesEquation(sR,sSigma);
	particular_factory bsFactory(pesEquation);

	//setting up initial condition
	mc::bvector fInCond(1);
	fInCond[0]=1.0;

	//setting up European call payoff
	mc::bvector bvStrikes(3);
	bvStrikes[0]=0.8;
	bvStrikes[1]=1.0;
	bvStrikes[2]=1.2;
	pmc::european_calls_payoff callPayoff(bvStrikes);

	//setting up asian payoffs
	pmc::asian_discretely_sampled_payoff AsianPayoff1(iAccuracy);
	pmc::asian_discretely_sampled_payoff AsianPayoff2(iAccuracy-2);


	//setting up KO payoffs
	mc::scalar sLowerBarrier(0.65);
	mc::scalar sUpperBarrier(1.5);
	pmc::knock_out_payoff<pmc::DoubleBarrier> koPayoff1(new pmc::european_calls_payoff(bvStrikes),
											pmc::DoubleBarrier(sUpperBarrier,sLowerBarrier),iAccuracy);
	
	pmc::knock_out_payoff<pmc::UpDownAndOut> koPayoff2(new pmc::european_calls_payoff(bvStrikes),
											pmc::UpDownAndOut(sUpperBarrier,sLowerBarrier),iAccuracy);

	//setting up statistics
	pmc::mean_variance_statistics mvStatisticsEuCall,mvStatisticsEuCallCoarse, 
								  mvStatisticsAsian1, mvStatisticsAsian2,
								  mvStatisticsKO1, mvStatisticsKO2;
	

	//simulation
	mc::bvector bvTemp;
	for(unsigned int i=0; i<iNumberOfPaths; ++i)
	{
		path_in_ptr pathInPtr(bsFactory.GetNewPathInPtr(iAccuracy,sT));
		path_out poPath(bsFactory.GetNewPathOut(pathInPtr,iAccuracy,iAccuracy,fInCond,sT));
		path_out poPathCoarse(bsFactory.GetNewPathOut(pathInPtr,iAccuracy-1,0,fInCond,sT));
		mvStatisticsEuCall.DumpOnePayoff(callPayoff(poPath,bvTemp));
		mvStatisticsEuCallCoarse.DumpOnePayoff(callPayoff(poPathCoarse,bvTemp));
		mvStatisticsAsian1.DumpOnePayoff(AsianPayoff1(poPath,bvTemp));
		mvStatisticsAsian2.DumpOnePayoff(AsianPayoff2(poPath,bvTemp));
		mvStatisticsKO1.DumpOnePayoff(koPayoff1(poPath,bvTemp));
		mvStatisticsKO2.DumpOnePayoff(koPayoff2(poPath,bvTemp));
	}

	//working out statistics
	vector<mc::bvector> StatValEuCall=mvStatisticsEuCall.GetStatistics();
	vector<mc::bvector> StatValEuCallCoarse=mvStatisticsEuCallCoarse.GetStatistics();
	vector<mc::bvector> StatValAsian1=mvStatisticsAsian1.GetStatistics();
	vector<mc::bvector> StatValAsian2=mvStatisticsAsian2.GetStatistics();
	vector<mc::bvector> StatValKO1=mvStatisticsKO1.GetStatistics();
	vector<mc::bvector> StatValKO2=mvStatisticsKO2.GetStatistics();

	cout << "*********************************************" << endl;
	cout << "*      European option with Monte Carlo     *" << endl;
	cout << "*********************************************" << endl;
	cout << "Call with strike:         " << bvStrikes[0] << endl;
	cout << "Black-Scholes price:      " << mc::BSOptionPrice(fInCond[0],bvStrikes[0],sT,sR,sSigma,true) << endl;
	cout << "Monte Carlo estimate:     " << StatValEuCall[0][0]*std::exp(-sR*sT) << endl;
	cout << "Stdev of MC estimate:     " << StatValEuCall[2][0]*std::exp(-sR*sT) << endl;
	cout << "Estimate on coarse scale: " << StatValEuCallCoarse[0][0]*std::exp(-sR*sT) << endl;
	cout << endl;
	cout << "Call with strike:         " << bvStrikes[1] << endl;
	cout << "Black-Scholes price:      " << mc::BSOptionPrice(fInCond[0],bvStrikes[1],sT,sR,sSigma,true) << endl;
	cout << "Monte Carlo estimate:     " << StatValEuCall[0][1]*std::exp(-sR*sT) << endl;
	cout << "Stdev of MC estimate:     " << StatValEuCall[2][1]*std::exp(-sR*sT) << endl;
	cout << "Estimate on coarse scale: " << StatValEuCallCoarse[0][1]*std::exp(-sR*sT) << endl;
	cout << endl;
	cout << "*********************************************" << endl;
	cout << "*       Asian option with Monte Carlo       *" << endl;
	cout << "*********************************************" << endl;
	cout << "Asian on scale " << iAccuracy << endl;
	cout << "Monte Carlo estimate: " << StatValAsian1[0][0]*std::exp(-sR*sT) << endl;
	cout << "Stdev of MC estimate: " << StatValAsian1[2][0]*std::exp(-sR*sT) << endl;
	cout << endl;
	cout << "Asian on scale " << iAccuracy-2 << endl;
	cout << "Monte Carlo estimate: " << StatValAsian2[0][0]*std::exp(-sR*sT) << endl;
	cout << "Stdev of MC estimate: " << StatValAsian2[2][0]*std::exp(-sR*sT) << endl;
	cout << endl;
	cout << "*********************************************" << endl;
	cout << "*  Double barrier option with Call payoff   *" << endl;
	cout << "*********************************************" << endl;
	cout << "Strike of call:     " << bvStrikes[0] << endl;
	cout << "Lower barrier:      " << sLowerBarrier << endl;
	cout << "Upper barrier:      " << sUpperBarrier << endl;
	cout << "Monte Carlo estimate: " << StatValKO1[0][0]*std::exp(-sR*sT) << endl;
	cout << "Stdev of MC estimate: " << StatValKO1[2][0]*std::exp(-sR*sT) << endl;
	cout << endl;
	cout << "*********************************************" << endl;
	cout << "*  Up Down and Out option with Call payoff  *" << endl;
	cout << "*********************************************" << endl;
	cout << "Strike of call:     " << bvStrikes[1] << endl;
	cout << "Lower barrier:      " << sLowerBarrier << endl;
	cout << "Upper barrier:      " << sUpperBarrier << endl;
	cout << "Monte Carlo estimate: " << StatValKO2[0][1]*std::exp(-sR*sT) << endl;
	cout << "Stdev of MC estimate: " << StatValKO2[2][1]*std::exp(-sR*sT) << endl;
	cout << endl;


	path_out poPath(bsFactory.GetNewPathOut(3,3,fInCond,sT));
	mc::dyadic d1(0,1), d2(1,2), d3(3,3), d4(7,4);
	mc::dyadic e1(1,1), e2(3,2), e3(7,3), e4(15,4);
	cout << "Testing path_map of solution path: " << endl;
	cout << d1 << " " << poPath.find(d1)->second[0] << endl;
	cout << d2 << " " << poPath.find(d2)->second[0] << endl;
	cout << d3 << " " << poPath.find(d3)->second[0] << endl;
	cout << d4 << " " << poPath.find(d4)->second[0] << endl;
	cout << e1 << " " << poPath.find(e1)->second[0] << endl;
	cout << e2 << " " << poPath.find(e2)->second[0] << endl;
	cout << e3 << " " << poPath.find(e3)->second[0] << endl;
	cout << e4 << " " << poPath.find(e4)->second[0] << endl;

}


void test_EuropeanOptionPricer()
{
	cout << endl;
	cout << "*********************************************" << endl;
	cout << "*          EUROPEAN OPTION PRICER           *" << endl;
	cout << "*********************************************" << endl;
	cout << endl;
	cout << endl;

	typedef equation_setup base_equation_setup;
	typedef geometricBM1D_setup particular_equation_setup;

	typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;
	
	typedef pmc::european_option_pricer<mc::bvector, basis_function> european_option_pricer;

	//setting up factory using particular ingredients
	unsigned int iAccuracy=5;
	mc::scalar sT(1.0), sR(0.5), sSigma(0.4);
	particular_equation_setup pesEquation(sR,sSigma);
	particular_factory bsFactory(pesEquation);

	//setting up payoff
	mc::bvector bvStrikes(3);
	bvStrikes[0]=0.8;
	bvStrikes[1]=1.0;
	bvStrikes[2]=1.2;
	pmc::european_calls_payoff callPayoff(bvStrikes);

	//setting up grid of initial values
	unsigned int iNumberOfGridPoints=10000;
	//...
	mc::scalar sGridPoint(0.7), sRange(0.6), sDStep=sRange/mc::scalar(iNumberOfGridPoints);
	std::vector<mc::bvector> factorsAt0;
	for(unsigned int i=0; i<iNumberOfGridPoints; ++i, sGridPoint+=sDStep)
		factorsAt0.push_back(mc::bvector(1,sGridPoint));
	
	//setting up test functions
	european_option_pricer::fvector testFunctions;	
	//...
	unsigned int iMaxDegree(5);
	//testFunctions.push_back(dop::Function(mc::scalar(1.0)));
    testFunctions.push_back([](bvector const& ){return mc::scalar(1.0);});
	//testFunctions.push_back(dop::Function(size_t(0)));
    testFunctions.push_back([](bvector const& arg){ return arg[0];});
	for(unsigned int i=2; i<=iMaxDegree;++i) {
        //testFunctions.push_back(dop::Function(0, i));
        testFunctions.push_back([i](bvector const& arg){ return std::pow(arg[0], static_cast<double>(i));});
    }
	
	//initialising the option pricer
	european_option_pricer callPricer(factorsAt0, iAccuracy, sT, sR,
						 bsFactory, callPayoff, testFunctions);


	//using option pricer
	//setting up test values for initial condition
	std::vector<mc::bvector> testVals;
	//...
	testVals.push_back(mc::bvector(1,0.78));
	testVals.push_back(mc::bvector(1,0.82));
	testVals.push_back(mc::bvector(1,0.87));
	testVals.push_back(mc::bvector(1,0.93));
	testVals.push_back(mc::bvector(1,0.98));
	testVals.push_back(mc::bvector(1,1.08));
	testVals.push_back(mc::bvector(1,1.12));
	testVals.push_back(mc::bvector(1,1.22));
	

	cout << "Parameters:" << endl;
	cout << "Risk-free rate: " << sR << endl;
	cout << "Volatility: " << sSigma << endl;
	cout << "Time to maturity: " << sT << endl;
	cout << "Strikes: " << bvStrikes << endl;

	for(unsigned int i=0; i<testVals.size(); ++i)
	{
		mc::bvector bvEstimates;
		callPricer(testVals[i],bvEstimates);
		cout<< "Stock price: " << testVals[i][0] << endl;
		cout<< "   Estimated option prices: " 
			  << bvEstimates[0] << ", " 
			  << bvEstimates[1] << ", "
			  << bvEstimates[2] << endl;
		cout<< "   Exact option prices:     " 
			  << mc::BSOptionPrice(testVals[i][0], bvStrikes[0],sT,sR,sSigma,true) << ", " 
			  << mc::BSOptionPrice(testVals[i][0], bvStrikes[1],sT,sR,sSigma,true) << ", " 
			  << mc::BSOptionPrice(testVals[i][0], bvStrikes[2],sT,sR,sSigma,true) << endl;
	}
}

void test_BermudanOptionPricer()
{
	cout << endl;
	cout << "*********************************************" << endl;
	cout << "*          BERMUDAN OPTION PRICER           *" << endl;
	cout << "*********************************************" << endl;
	cout << endl;
	cout << endl;

	typedef equation_setup base_equation_setup;
	typedef geometricBM1D_setup particular_equation_setup;
	typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;
	typedef pmc::bermudan_option_pricer<mc::bvector,basis_function> bermudan_option_pricer;

	//setting up factory using particular ingredients
	unsigned int iAccuracy=5;
	mc::scalar sT(0.5), sR(0.05), sSigma(0.2);
	particular_equation_setup pesEquation(sR,sSigma);
	particular_factory bsFactory(pesEquation);

	//setting up payoff
	mc::bvector bvStrikes(3);
	bvStrikes[0]=0.8;
	bvStrikes[1]=1.0;
	bvStrikes[2]=1.2;
	pmc::time_dependent_put putPayoff(bvStrikes);

	//setting up grid of initial values
	unsigned int iNumberOfGridPoints=10000;
	//...
	mc::scalar sGridPoint(0.7), sRange(0.6), sDStep=sRange/mc::scalar(iNumberOfGridPoints);
	std::vector<mc::bvector> factorsAt0;
	for(unsigned int i=0; i<iNumberOfGridPoints; ++i, sGridPoint+=sDStep)
		factorsAt0.push_back(mc::bvector(1,sGridPoint));
	
	//setting up test functions
	bermudan_option_pricer::fvector testFunctions;	
	//...
	unsigned int iMaxDegree(5);
    //testFunctions.push_back(dop::Function(mc::scalar(1.0)));
    testFunctions.push_back([](bvector const& ){return mc::scalar(1.0);});
    //testFunctions.push_back(dop::Function(size_t(0)));
    testFunctions.push_back([](bvector const& arg){ return arg[0];});
    for(unsigned int i=2; i<=iMaxDegree;++i) {
        //testFunctions.push_back(dop::Function(0, i));
        testFunctions.push_back([i](bvector const& arg){ return std::pow(arg[0], static_cast<double>(i));});
    }

	//initialising the option pricer
	bermudan_option_pricer europeanPutPricer(factorsAt0, iAccuracy,0, sT, sR,
						 bsFactory, putPayoff, testFunctions);

	bermudan_option_pricer bermudanPutPricer(factorsAt0, iAccuracy,iAccuracy, sT, sR,
						 bsFactory, putPayoff, testFunctions);

	//using option pricer
	//setting up test values for initial condition
	std::vector<mc::bvector> testVals;
	//...
	testVals.push_back(mc::bvector(1,0.78));
	testVals.push_back(mc::bvector(1,0.8));
	testVals.push_back(mc::bvector(1,0.82));
	testVals.push_back(mc::bvector(1,0.84));
	testVals.push_back(mc::bvector(1,0.86));
	testVals.push_back(mc::bvector(1,0.9));
	testVals.push_back(mc::bvector(1,1.0));
	testVals.push_back(mc::bvector(1,1.1));
	

	cout << "Parameters of put option:" << endl;
	cout << "Risk-free rate: " << sR << endl;
	cout << "Volatility: " << sSigma << endl;
	cout << "Time to maturity: " << sT << endl;
	cout << "Strikes: " << bvStrikes << endl;

	for(unsigned int i=0; i<testVals.size(); ++i)
	{
		mc::bvector bvEstimates;
		bermudanPutPricer(testVals[i],bvEstimates);
		cout<< "Stock price: " << testVals[i][0] << endl;
		cout<< "   Estimated bermudan option prices: " 
			  << bvEstimates[0] << ", " 
			  << bvEstimates[1] << ", "
			  << bvEstimates[2] << endl;
		europeanPutPricer(testVals[i],bvEstimates);
		cout<< "   Estimated european option prices: " 
			  << bvEstimates[0] << ", " 
			  << bvEstimates[1] << ", "
			  << bvEstimates[2] << endl;
		cout<< "   Values by Black-Scholes formula:  " 
			  << mc::BSOptionPrice(testVals[i][0], bvStrikes[0],sT,sR,sSigma,false) << ", " 
			  << mc::BSOptionPrice(testVals[i][0], bvStrikes[1],sT,sR,sSigma,false) << ", " 
			  << mc::BSOptionPrice(testVals[i][0], bvStrikes[2],sT,sR,sSigma,false) << endl;
	}


}

/*
*********************************************
*          BERMUDAN OPTION PRICER           *
*********************************************


Parameters of put option:
Risk-free rate: 0.05
Volatility: 0.2
Time to maturity: 0.5
Strikes: [3](0.8,1,1.2)
Stock price: 0.78
   Estimated bermudan option prices: 0.0518558, 0.218213, 0.418455
   Estimated european option prices: 0.0434198, 0.196693, 0.389085
   Values by Black-Scholes formula:  0.0441012, 0.198308, 0.390453
Stock price: 0.8
   Estimated bermudan option prices: 0.0429653, 0.198257, 0.398259
   Estimated european option prices: 0.0351983, 0.178821, 0.37009
   Values by Black-Scholes formula:  0.0353578, 0.179871, 0.370521
Stock price: 0.82
   Estimated bermudan option prices: 0.0353555, 0.179021, 0.378088
   Estimated european option prices: 0.028271, 0.161561, 0.351055
   Values by Black-Scholes formula:  0.0279794, 0.162017, 0.350636
Stock price: 0.84
   Estimated bermudan option prices: 0.02889, 0.16067, 0.35793
   Estimated european option prices: 0.0224798, 0.145002, 0.331927
   Values by Black-Scholes formula:  0.021858, 0.144868, 0.33082
Stock price: 0.86
   Estimated bermudan option prices: 0.0234413, 0.143337, 0.337796
   Estimated european option prices: 0.0176798, 0.12922, 0.312699
   Values by Black-Scholes formula:  0.0168627, 0.128545, 0.311107
Stock price: 0.9
   Estimated bermudan option prices: 0.0151306, 0.112076, 0.297735
   Estimated european option prices: 0.0105371, 0.100264, 0.274078
   Values by Black-Scholes formula:  0.00967853, 0.0988042, 0.272159
Stock price: 1
   Estimated bermudan option prices: 0.00491136, 0.0550412, 0.201839
   Estimated european option prices: 0.00219935, 0.0451711, 0.180825
   Values by Black-Scholes formula:  0.00199354, 0.0441972, 0.180598
Stock price: 1.1
   Estimated bermudan option prices: 0.00253088, 0.0245557, 0.120867
   Estimated european option prices: 0.00033325, 0.0156023, 0.104511
   Values by Black-Scholes formula:  0.000326221, 0.0160638, 0.105221
*/



