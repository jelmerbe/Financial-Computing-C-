#include "Practical01/Practical01Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace exercises;
using namespace utils;

void TestNorms(MyStream & mystream);
void TestMonteCarlo(MyStream & mystream);

const string fileName = (string)COURSE_OUTPUT_DIR + "/Practicals/Practical01/Practical01_output.txt";
int main()
{
    cout << "Output being written to: " << fileName << endl;
	fstream myfile;
	myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
    mystream << "\n\n";

	TestMonteCarlo(mystream);
	TestNorms(mystream);

	myfile.close();
	return 0;
}


void TestNorms(MyStream & mystream)
{
	vector<double> v;
	v.push_back(0.0);
	v.push_back(-10.0);
	v.push_back(10.0);
	v.push_back(20.0);
	v.push_back(30.0);
	v.push_back(-30.0);
	v.push_back(0.0);
	v.push_back(-100.0);

    mystream<< "\n";
    mystream<< "**********************************************" << "\n";
    mystream<< "*       Testing Norm2() and NormInf()        *" << "\n";
    mystream<< "**********************************************" << "\n";
    mystream << "The vector is: " << "\n";
	for(vector<double>::size_type i=0; i<v.size(); ++i)
        mystream << v[i] << " " ;
    mystream << "\n";

    mystream << "The 2 norm of v is: " << Norm2(v) << "\n";
    mystream << "The inf norm of v is: " << NormInf(v) << "\n";
    mystream << "\n";
}

void TestMonteCarlo(MyStream & mystream)
{
	double r(0.05), sigma(0.4), S0(1.0), K(1.0), T(0.5);
	unsigned long int N(1000000);

    mystream << "\n";
    mystream << "**********************************************" << "\n";
    mystream << "*  Testing MonteCarlo1() and MonteCarlo2()   *" << "\n";
    mystream << "**********************************************" << "\n";
    mystream << "Parameters: " << "\n";
    mystream << "r: \t" << r << "\n";
    mystream << "sigma: \t" << sigma << "\n";
    mystream << "S0: \t" << S0 << "\n";
    mystream << "K: \t" << K << "\n";
    mystream << "T: \t" << T << "\n";
    mystream << "N: \t" << N << "\n";
	double price1=MonteCarlo1(r,sigma,S0,K,T,N);
	vector<double> price2=MonteCarlo2(r,sigma,S0,T,N,callAt1);
    mystream << "price1: \t" << price1 << "\n";
    mystream << "price2: \t" << price2[0] << "\n";
    mystream << "stdev2: \t" << price2[1] << "\n";
    mystream << "Black-Scholes price: \t" << BSOptionPrice(S0,K,T,r,sigma) << "\n";
    mystream << "\n";
}
