#include "Practical02/Practical02Exercises.hpp"
#include "Practical02/ComplexNumber.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;
using namespace exercises;
using namespace utils;

void TestMonteCarlo3(MyStream & mystream);
void TestStrongConvergence(MyStream & mystream);
void TestComplexNumber(MyStream & mystream);

double drift(double, double);
double diffusion(double, double);
double diffusionDiff(double, double);
double callAt1(double);

const string fileName = (string)COURSE_OUTPUT_DIR + "/Practicals/Practical02/Practical02_output.txt";
int main()
{
    cout << "Output being written to: " << fileName << "\n";
	fstream myfile;
	myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
    mystream << "\n\n";

	TestMonteCarlo3(mystream);
	TestStrongConvergence(mystream);
	TestComplexNumber(mystream);

	myfile.close();
	return 0;
}

double drift(double dArg1, double dArg2)
{
	return 0.05*dArg2;
}

double diffusion(double dArg1, double dArg2)
{
	return 0.2*dArg2;
}

double diffusionDiff(double dArg1, double dArg2)
{
	return 0.2;
}


double callAt1(double dArg)
{
	return (dArg<1.0 ? 0.0 : dArg-1.0);
}

void TestMonteCarlo3(MyStream & mystream)
{
	double dS0(1.0), dK(1.0), dT(0.5);
	double dR=drift(0.0,1.0);
	double dSigma=diffusion(0.0,1.0); 
	unsigned long int iNumberOfPaths(10000);
	unsigned long int iNumberOfSteps(100);
	Equation equation;
	equation.push_back(drift);
	equation.push_back(diffusion);
	equation.push_back(diffusionDiff);

    mystream << "\n";
    mystream << "****************************************************" << "\n";
    mystream << "*  Testing Eulerstep, MilsteinStep, MonteCarlo3()  *" << "\n";
    mystream << "****************************************************" << "\n";
    mystream << "Parameters: " << "\n";
    mystream << "r: \t" << dR << "\n";
    mystream << "sigma: \t" << dSigma << "\n";
    mystream << "S0: \t" << dS0 << "\n";
    mystream << "K: \t" << dK << "\n";
    mystream << "T: \t" << dT << "\n";
    mystream << "Number of steps: \t" << iNumberOfSteps << "\n";
    mystream << "Number of paths: \t" << iNumberOfPaths << "\n";
    mystream << "Euler scheme results" << "\n";
	vector<double> price1=MonteCarlo3(dS0,dT,dR,equation,eulerStep,iNumberOfSteps,iNumberOfPaths,callAt1);
    mystream << "price2: \t" << price1[0] << "\n";
    mystream << "stdev2: \t" << price1[1] << "\n";
    mystream << "Milstein scheme results" << "\n";
	vector<double> price2=MonteCarlo3(dS0,dT,dR,equation,milsteinStep,iNumberOfSteps,iNumberOfPaths,callAt1);
    mystream << "price2: \t" << price2[0] << "\n";
    mystream << "stdev2: \t" << price2[1] << "\n";
    mystream << "Black-Scholes price: \t" << BSOptionPrice(dS0,dK,dT,dR,dSigma) << "\n";
    mystream << "\n";

}

void TestStrongConvergence(MyStream & mystream)
{
	
	//log2 of mx number of steps
	unsigned int iLevels(8);
	//vectors to store the error, initialised with all zero entries
	DVector eulerBias(iLevels,0.0), eulerMC(iLevels,0.0), milsteinBias(iLevels,0.0), milsteinMC(iLevels,0.0);
	DVector eulerEstimates(iLevels), milsteinEstimates(iLevels);
	//the coefficient functions
	Equation equation;
	equation.push_back(drift);
	equation.push_back(diffusion);
	equation.push_back(diffusionDiff);
	//other parameters
	double dS0(1.0), dT(10);
	double dR=drift(0.0,1.0);
	double dSigma=diffusion(0.0,1.0);
	unsigned long int iNumberOfPaths(100000);
	unsigned long int iMaxNumberOfSteps=(1<<(iLevels-1));
	//vectors for driving noise
	DVector noiseVector(2), brownianIncrements(iMaxNumberOfSteps), brownianIncrementsTemp(iMaxNumberOfSteps);
	unsigned int iNumberOfSteps;
	double dDt,dSqrtDt, dMinDt(dT/iMaxNumberOfSteps), dSqrtMinDt(std::sqrt(dMinDt));	

	//outer loop - generating paths
	for(unsigned long int iPaths=0; iPaths<iNumberOfPaths; ++iPaths)
	{

		double dSExact(dS0);
				
		//generate driving noise on the finest scale
		for(unsigned int iSteps=0; iSteps<iMaxNumberOfSteps; ++iSteps)
			brownianIncrements[iSteps]=NormalDist()*dSqrtMinDt;

		//running the method on different time scales
		for(unsigned int iLog2Steps=iLevels; iLog2Steps>0; --iLog2Steps)
		{
			double dSEuler(dS0);
			double dSMilstein(dS0);
			double dTime(0.0);
			iNumberOfSteps=(1<<(iLog2Steps-1));
			dDt=dT/iNumberOfSteps;
			dSqrtDt=std::sqrt(dDt);
			noiseVector[0]=dDt;
				
			//generate coarser input noise
			if(iLog2Steps<iLevels)
				for(unsigned long int iSteps=0; iSteps<iNumberOfSteps; ++iSteps)
					brownianIncrements[iSteps]=brownianIncrements[2*iSteps]+brownianIncrements[2*iSteps+1];

			//generating path
			for(unsigned long int iSteps=0; iSteps<iNumberOfSteps; ++iSteps)
			{
				//generating input noise
				noiseVector[1]=brownianIncrements[iSteps];
				//Euler step
				dSEuler=eulerStep(dSEuler,dTime,noiseVector,equation);
				//Milstein step
				dSMilstein=milsteinStep(dSMilstein,dTime,noiseVector,equation);
				//incrementing time
				dTime+=dDt;
			}
			eulerEstimates[iLog2Steps-1]=dSEuler;
			milsteinEstimates[iLog2Steps-1]=dSMilstein;
		}


		//exact solution
		dSExact=dSExact*std::exp(dT*(dR-0.5*dSigma*dSigma)+dSigma*brownianIncrements[0]);
		
		//updating error estimates
		for(unsigned int iLog2Steps=0; iLog2Steps<iLevels; ++iLog2Steps)
		{
			double dEulerSq=(dSExact-eulerEstimates[iLog2Steps])*(dSExact-eulerEstimates[iLog2Steps]);
			eulerBias[iLog2Steps]+=dEulerSq/iNumberOfPaths;
			eulerMC[iLog2Steps]+=dEulerSq*dEulerSq/iNumberOfPaths;
			double dMilsteinSq=(dSExact-milsteinEstimates[iLog2Steps])*(dSExact-milsteinEstimates[iLog2Steps]);
			milsteinBias[iLog2Steps]+=dMilsteinSq/iNumberOfPaths;
			milsteinMC[iLog2Steps]+=dMilsteinSq*dMilsteinSq/iNumberOfPaths;
		}

	}

	//final results
	for(unsigned int iLog2Steps=0; iLog2Steps<iLevels; ++iLog2Steps)
	{
		eulerMC[iLog2Steps]-=eulerBias[iLog2Steps]*eulerBias[iLog2Steps];
		eulerMC[iLog2Steps]=std::sqrt(eulerMC[iLog2Steps]/iNumberOfPaths);
		milsteinMC[iLog2Steps]-=milsteinBias[iLog2Steps]*milsteinBias[iLog2Steps];
		milsteinMC[iLog2Steps]=std::sqrt(milsteinMC[iLog2Steps]/iNumberOfPaths);
	}


	//display results
    mystream << "\n";
    mystream << "*********************************************************" << "\n";
    mystream << "*  Testing Eulerstep, MilsteinStep, strong convergence  *" << "\n";
    mystream << "*********************************************************" << "\n";
    mystream << "Steps: \t" << "MSE Eul.: \t" << "Stdev: \t\t" <<
							 "MSE Milst.: \t" << "Stdev:" << "\n";
	for(unsigned int iLog2Steps=0; iLog2Steps<iLevels; ++iLog2Steps)
	{
		iNumberOfSteps=(1<<iLog2Steps);
        mystream << iNumberOfSteps << "\t";
        mystream << std::setprecision(8) << eulerBias[iLog2Steps] << "\t"
			   << std::setprecision(8) << eulerMC[iLog2Steps] << "\t" 
			   << std::setprecision(8) << milsteinBias[iLog2Steps] << "\t" 
			   << std::setprecision(8) << milsteinMC[iLog2Steps] << "\n";
	}
    mystream  << "\n";
}


void TestComplexNumber(MyStream & mystream)
{
    mystream << "\n";
    mystream << "****************************" << "\n";
    mystream << "*  Testing ComplexNumbers  *" << "\n";
    mystream << "****************************" << "\n";
    mystream << "\n";

	//constructors
	ComplexNumber c1, c2(2.5), c3(3.11,3.11), c4(c3);
    mystream << "c1 = " << c1 << "\n";
    mystream << "c2 = " << c2 << "\n";
    mystream << "c3 = " << c3 << "\n";
    mystream << "c4 = " << c4 << "\n";

	//operations
	c1+=(c2+c3);
    mystream << "c1+=(c2+c3): c1 = " << c1 << "\n";
	c4-=(c2-c3);
    mystream << "c4-=(c2-c3): c4 = " << c4 << "\n";
	c3+=c2*=c1;
    mystream << "c3+=c2*=c1: c3 = " << c3 << " c2 = " << c2 << " c1 = " << c1 << "\n";
	c3/=(c2*c3);
    mystream << "c3/=(c2*c3): c3 = " << c3 << "\n";
	c3-=(2.5*c2);
    mystream << "c3-=(2.5*c2): c3 = " << c3 << "\n";
	c2/=(2.73+c4);
    mystream << "c2/=(2.73+c4): c2 = " << c2 << "\n";
	(((c4-=2.4)*=3.4)-=1.3)/=2.0;
    mystream << "(((c4-=2.4)*=3.4)-=1.3)/=2.0: c4 = " << c4 << "\n";
	c3=((((c2+2.3)-3.4)*2.4)/1.2);
    mystream << "c3=((((c2+2.3)-3.4)*2.4)/1.2): c3 = " << c3 << "\n";
	c2=(6.7*(1.2-(3.5+(3.4/c1))));
    mystream << "c2=(6.7*(1.2-(3.5+(3.4/c1)))): c2 = " << c2 << "\n";
}
