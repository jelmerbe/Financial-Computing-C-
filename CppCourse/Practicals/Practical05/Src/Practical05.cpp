

#ifdef _PRACTICAL_05_SOLUTIONS_
	#include "Practical05Solutions/BitManipTests.hpp"
#else
	#include "Practical05/BitManipTests.hpp"
#endif
#include "Practical05/Practical05Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include "boost/numeric/ublas/io.hpp"
#include <boost/math/special_functions/erf.hpp>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace exercises;
using namespace std;
using namespace utils;


void TestRegressionProjection(MyStream & mystream);
void TestMonteCarlo4_EuropeanOptionPricer(MyStream & mystream);
double Const(const BVector & vArg){return 1.0;}
double X1_1(const BVector & vArg){return vArg[0];}
double X1_2(const BVector & vArg){return vArg[0]*vArg[0];}
double X1_3(const BVector & vArg){return vArg[0]*vArg[0]*vArg[0];}
double X2_1(const BVector & vArg){return vArg[1];}
double X2_2(const BVector & vArg){return vArg[1]*vArg[1];}
double X2_3(const BVector & vArg){return vArg[1]*vArg[1]*vArg[1];}
double X12_11(const BVector & vArg){return vArg[0]*vArg[1];}
double X12_12(const BVector & vArg){return vArg[0]*vArg[1]*vArg[1];}
double X12_21(const BVector & vArg){return vArg[0]*vArg[0]*vArg[1];}
double X12_22(const BVector & vArg){return vArg[0]*vArg[0]*vArg[1]*vArg[1];}
double Basket(const BVector & vArg){return max(vArg[0],vArg[1]);}
double CallAt1(const BVector & vArg){return max(vArg[0]-1.0,0.0);}

const string fileName = (string)COURSE_OUTPUT_DIR + "/Practicals/Practical05/Practical05_output.txt";
int main(int argc, char **argv) {

    cout << "Output being written to: " << fileName << "\n";
	fstream myfile;
	myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
	mystream << "\n";
	mystream << "\n";

	TestRegressionProjection(mystream);
	TestMonteCarlo4_EuropeanOptionPricer(mystream);

	myfile.close();

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}

void TestRegressionProjection(MyStream & mystream)
{

	mystream<< "\n";
	mystream<< "************************" << "\n";
	mystream<< "*  Testing Regression  *" << "\n";
	mystream<< "************************" << "\n";


	FVector testFunctions;
	testFunctions.push_back(Const);
	testFunctions.push_back(X1_1);
	testFunctions.push_back(X1_2);
	testFunctions.push_back(X1_3);
	testFunctions.push_back(CallAt1);

	unsigned int n(1000);
	double dDS(1.0/n);
	double dS(0.5);
	double dR(0.05), dSigma(0.4), dT(1.0);
	double dDrift((dR-0.5*dSigma*dSigma)*dT);
	double dVol(dSigma*sqrt(dT));
	std::vector<BVector> vInitialStock(n);
	BVector vVals(n);
	for(unsigned int i=0; i<n; ++i, dS+=dDS)
	{
		vInitialStock[i]=(BVector(1,dS));
		vVals[i]=max(dS*exp(dDrift+dVol*NormalDist())-1.0,0.0);
	}
	BVector vBeta=Regression(vVals,vInitialStock,testFunctions);


	mystream << "R = " << dR << "\n";
	mystream << "Sigma = " << dSigma << "\n";
	mystream << "Maturity = " << dT << "\n";
	mystream << "Strike = " << 1.0 << "\n";
	mystream << "Sample size = " << n << "\n";
	mystream << "Range : " << vInitialStock.front()[0] << " - " << vInitialStock.back()[0] << "\n";
	mystream << "Number of test functions = " << testFunctions.size() << "\n";
	mystream << "Regression coefficients = " << vBeta << "\n";
	mystream<< "\n";
	mystream<< "************************" << "\n";
	mystream<< "*  Testing Projection  *" << "\n";
	mystream<< "************************" << "\n";

	mystream << "Call prices" << "\n";
	double dS0=vInitialStock[n/10][0];
	mystream << "S0 = " << dS0 << ", estimated price: " << Projection(BVector(1,dS0), testFunctions, vBeta) 
		   << ", exact price: " << BSOptionPrice(dS0,1.0,dT,dR,dSigma) << "\n";
	dS0=vInitialStock[n/2-n/10][0];
	mystream << "S0 = " << dS0 << ", estimated price: " << Projection(BVector(1,dS0), testFunctions, vBeta) 
		   << ", exact price: " << BSOptionPrice(dS0,1.0,dT,dR,dSigma) << "\n";
	dS0=vInitialStock[n/2][0];
	mystream << "S0 = " << dS0 << ", estimated price: " << Projection(BVector(1,dS0), testFunctions, vBeta) 
		   << ", exact price: " << BSOptionPrice(dS0,1.0,dT,dR,dSigma) << "\n";
	dS0=vInitialStock[n/2+n/10][0];
	mystream << "S0 = " << dS0 << ", estimated price: " << Projection(BVector(1,dS0), testFunctions, vBeta) 
		   << ", exact price: " << BSOptionPrice(dS0,1.0,dT,dR,dSigma) << "\n";
	dS0=vInitialStock[n-n/10][0];
	mystream << "S0 = " << dS0 << ", estimated price: " << Projection(BVector(1,dS0), testFunctions, vBeta) 
		   << ", exact price: " << BSOptionPrice(dS0,1.0,dT,dR,dSigma) << "\n";
	mystream << "\n";

}


void TestMonteCarlo4_EuropeanOptionPricer(MyStream & mystream)
{

	mystream<< "\n";
	mystream<< "**************************************************" << "\n";
	mystream<< "*  Testing MonteCarlo4 and EuropeanOptionPricer  *" << "\n";
	mystream<< "**************************************************" << "\n";

	//constructing initial grid
	unsigned int n(200);
	double dDS(0.25/n);
	double dS01(0.875), dS02(0.875);
	double dR(0.1), dSigma1(0.2), dSigma2(0.08), dRho(-0.7), dT(1.0);
	
	std::vector<BVector> vS0(n*n);
	BVector vTemp(2);
	unsigned int k(0);
	for(unsigned int i=0; i<n; ++i, dS01+=dDS)
	{
		double dS2(dS02);
		for(unsigned int j=0; j<n; ++j, dS2+=dDS, ++k)
		{
			vTemp[0]=dS01;
			vTemp[1]=dS2;
			vS0[k]=vTemp;
		}
	}

	//set of test functions
	FVector testFunctions;
	testFunctions.push_back(Const);
	testFunctions.push_back(X1_1);
	testFunctions.push_back(X1_2);
	testFunctions.push_back(X1_3);
	testFunctions.push_back(X2_1);
	testFunctions.push_back(X2_2);
	testFunctions.push_back(X2_3);
	testFunctions.push_back(X12_11);
	testFunctions.push_back(X12_12);
	testFunctions.push_back(X12_21);
	testFunctions.push_back(X12_22);
	testFunctions.push_back(Basket);

	//MonteCarlo4 is used for generating values
	BVector vVals=MonteCarlo4(vS0,dR,dSigma1,dSigma2,dRho,dT,Basket);

	//EuropeanOptionPricer
	EuropeanOptionPricer basketOption(vS0,vVals,testFunctions);
					
	mystream << "R = " << dR << "\n";
	mystream << "Sigma1 = " << dSigma1 << "\n";
	mystream << "Sigma2 = " << dSigma2 << "\n";
	mystream << "Rho = " << dRho << "\n";
	mystream << "Maturity = " << dT << "\n";
	mystream << "Sample size = " << n*n << "\n";
	mystream << "Step size = " << dDS << "\n";
	mystream << "Range : " << vS0.front()[0] << " - " << vS0.back()[0] << "\n";
	mystream << "Number of test functions = " << testFunctions.size() << "\n";
	mystream << "\n";
	mystream << "Option values" << "\n";
	k=n*n/100;
	mystream << "S1(0) = " << vS0[k][0] << ", S2(0) = " << vS0[k][1] << ", option value = " << basketOption(vS0[k]) << "\n";
	k=n*n*5/12;
	mystream << "S1(0) = " << vS0[k][0] << ", S2(0) = " << vS0[k][1] << ", option value = " << basketOption(vS0[k]) << "\n";
	k=n*n/2;
	mystream << "S1(0) = " << vS0[k][0] << ", S2(0) = " << vS0[k][1] << ", option value = " << basketOption(vS0[k]) << "\n";
	k=n*n*7/12;
	mystream << "S1(0) = " << vS0[k][0] << ", S2(0) = " << vS0[k][1] << ", option value = " << basketOption(vS0[k]) << "\n";
	k=n*n*99/100;
	mystream << "S1(0) = " << vS0[k][0] << ", S2(0) = " << vS0[k][1] << ", option value = " << basketOption(vS0[k]) << "\n";
	mystream << "\n";
}




