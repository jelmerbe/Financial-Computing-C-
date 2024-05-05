#include "Lecture1314/MonteCarloWithMClib.hpp"
#include "MCLib/vec_ops_setup.hpp"
#include "MCLib/particular_factory.hpp"
#include "MCLib/particular_payoff_statistics.hpp"
#include <iostream>

using namespace std;
using namespace vecop;

void TestMonteCarloMClib(unsigned int iNumberOfPaths);

int main()
{
	unsigned int iNumberOfPaths(10000);
	TestMonteCarloMClib(iNumberOfPaths);
	return 0;
}



void TestMonteCarloMClib(unsigned int iNumberOfPaths)
{
	cout << "********************************************" << endl;
	cout << "* TESTING SIMPLE_MC_FACTORY with EU payoff *" << endl;
	cout << "********************************************" << endl;

	typedef equation_setup base_equation_setup;
	typedef geometricBM1D_setup particular_equation_setup;
	typedef pmc::simple_mc_factory<base_equation_setup> particular_factory;

	//setting up factory using particular ingredients
	mc::scalar mu(0.1), sigma(0.2);
	particular_equation_setup pesEquation(mu,sigma);
	base_equation_setup & Equation=pesEquation;
	particular_factory pfFactory(Equation);
	
	//using factory
	unsigned int iAccuracy(5);
	unsigned int iGlobalAccuracy(0);
	mc::scalar sT(2.0);
	mc::bvector fInCond(1);
	fInCond[0]=1.0;
	
	//setting up a particular payoff
	mc::bvector bvStrikes(2);
	bvStrikes[0]=1.0;
	bvStrikes[1]=1.2;
    pmc::european_calls_payoff EuPayoff(bvStrikes);
	
    //setting up statistics
	pmc::mean_variance_statistics mvStatistics;
	
	MonteCarloMClib(iAccuracy,
					iGlobalAccuracy,
                    iNumberOfPaths,
					sT,
					fInCond,
					pfFactory,
					EuPayoff,
					mvStatistics);
	

	vector<mc::bvector> StatVal=mvStatistics.GetStatistics();
	cout<< "Option 1 value: " << StatVal[0][0] << " Option 2 value: " << StatVal[0][1] <<  endl;
	cout<< "Option 1 variance: " << StatVal[1][0] << " Option 2 variance: " << StatVal[1][1] <<  endl;
	cout<< "Option 1 stdev: " << StatVal[2][0] << " Option 2 stdev: " << StatVal[2][1] <<  endl;


}