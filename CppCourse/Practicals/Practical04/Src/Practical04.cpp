#include "Practical04/Practical04Exercises.hpp"
#include "Practical04/Interpolate.hpp"
#include "Practical04/BinaryOperators.hpp"
#include "Practical04/SparseVector.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>


using namespace exercises;
using namespace std;
using namespace utils;


void TestInterpolate1(MyStream & mystream);
void TestInterpolate2(MyStream & mystream);
void TestSparseVector(MyStream & mystream);

const string fileName = (string)COURSE_OUTPUT_DIR + "/Practicals/Practical04/Practical04_output.txt";
int main()
{
    cout << "Output being written to: " << fileName << "\n";
	fstream myfile;
	myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
	myfile << "\n";
	myfile << "\n";

	TestInterpolate1(mystream);
	TestInterpolate2(mystream);
	TestSparseVector(mystream);

	myfile.close();
    return 0;
}

MyStream & operator<<(MyStream & stream, SparseVector const& arg)
{
    std::cout << arg;
    stream.myfile << arg;
    return stream;
}

void TestInterpolate1(MyStream & mystream)
{
	mystream<< "\n";
	mystream<< "*************************************" << "\n";
	mystream<< "*  DF2Yield, Yield2DF, Interpolate  *" << "\n";
	mystream<< "*************************************" << "\n";
	
	vector<double> xVals, yVals, xTest, yTest;
	xVals.push_back(0.08);
	xVals.push_back(0.25);
	xVals.push_back(0.50);
	xVals.push_back(0.75);
	xVals.push_back(1.00);
	xVals.push_back(1.50);
	xVals.push_back(2.0);
	xVals.push_back(3.0);
	xVals.push_back(4.0);
	xVals.push_back(5.0);
	
	yVals.push_back(0.991);
	yVals.push_back(0.985);
	yVals.push_back(0.9801);
	yVals.push_back(0.9745);
	yVals.push_back(0.9512);
	yVals.push_back(0.9278);
	yVals.push_back(0.9152);
	yVals.push_back(0.8523);
	yVals.push_back(0.7912);
	yVals.push_back(0.7098);

	

	vector<double>::iterator xIter=xVals.begin();
	vector<double>::iterator xeIter=xVals.end();
	vector<double>::iterator yIter=yVals.begin();

	mystream << "\n";
	mystream << "Input discount curve:" << "\n";
	for(; xIter != xeIter; ++xIter, ++yIter)
		mystream << "D(" << *xIter << ") = \t" << *yIter << "\n";


	xTest.push_back(0.04);
	xTest.push_back(0.08);
	xTest.push_back(0.21);
	xTest.push_back(0.61);
	xTest.push_back(0.85);
	xTest.push_back(1.2);
	xTest.push_back(1.7);
	xTest.push_back(2.5);
	xTest.push_back(3.5);
	xTest.push_back(4.6);
	xTest.push_back(5.0);
	xTest.push_back(5.7);

	yTest.resize(xTest.size());
	std::transform(xTest.begin(),xTest.end(),yTest.begin(),Interpolate<DF2Yield,Yield2DF>(xVals,yVals));


	xIter=xTest.begin();
	xeIter=xTest.end();
	yIter=yTest.begin();

	mystream << "\n";
	mystream << "Interpolated discount curve:" << "\n";
	for(; xIter != xeIter; ++xIter, ++yIter)
		mystream << "D(" << *xIter << ") = \t" << *yIter << "\n";

}

void TestInterpolate2(MyStream & mystream)
{

	mystream<< "\n";
	mystream<< "*************************************" << "\n";
	mystream<< "*  DF2Libor, Libor2DF, Interpolate  *" << "\n";
	mystream<< "*************************************" << "\n";
	
	vector<double> xVals, yVals, xTest, yTest;
	xVals.push_back(0.08);
	xVals.push_back(0.17);
	xVals.push_back(0.25);
	xVals.push_back(0.5);
	xVals.push_back(0.75);
	xVals.push_back(1.0);
		
	yVals.push_back(0.995);
	yVals.push_back(0.985);
	yVals.push_back(0.982);
	yVals.push_back(0.974);
	yVals.push_back(0.965);
	yVals.push_back(0.952);

	vector<double>::iterator xIter=xVals.begin();
	vector<double>::iterator xeIter=xVals.end();
	vector<double>::iterator yIter=yVals.begin();

	mystream << "\n";
	mystream << "Input discount curve:" << "\n";
	for(; xIter != xeIter; ++xIter, ++yIter)
		mystream << "D(" << *xIter << ") = \t" << *yIter << "\n";

	xTest.push_back(0.04);
	xTest.push_back(0.17);
	xTest.push_back(0.21);
	xTest.push_back(0.45);
	xTest.push_back(0.5);
	xTest.push_back(0.55);
	xTest.push_back(0.71);
	xTest.push_back(0.95);
	xTest.push_back(1.0);
	

	yTest.resize(xTest.size());
	std::transform(xTest.begin(),xTest.end(),yTest.begin(),Interpolate<DF2Libor,Libor2DF>(xVals,yVals));


	xIter=xTest.begin();
	xeIter=xTest.end();
	yIter=yTest.begin();

	mystream << "\n";
	mystream << "Interpolated discount curve:" << "\n";
	for(; xIter != xeIter; ++xIter, ++yIter)
		mystream << "D(" << *xIter << ") = \t" << *yIter << "\n";

}

void TestSparseVector(MyStream & mystream)
{
	mystream<< "\n";
	mystream<< "******************" << "\n";
	mystream<< "*  SparseVector  *" << "\n";
	mystream<< "******************" << "\n";
	mystream<< "\n";

	SparseVector sv1, sv2, sv3;
	sv1.insert(make_pair(1,1.5));
	sv1.insert(make_pair(10,1.5));
	sv1.insert(make_pair(20,22.3));

	sv2[1]=-1.5;
	sv2[10]=1.5;
	sv2[11]=11.123;

	mystream<< "sv1=" <<  sv1 << "\n";
	mystream<< "sv2=" << sv2 << "\n";
	mystream<< "sv3=" << sv3 << "\n";

	sv3+=(sv1-sv2);
	mystream<< "sv3+=(sv1-sv2); sv3=" << sv3 << "\n";

	sv1-=sv2;
	mystream<< "sv1-=sv2; sv1=" << sv1 << "\n";

	sv3=sv2*2.5;
	mystream<< "sv3=sv2*2.5; sv3=" << sv3 << "\n";

	sv1*=5.0;
	mystream<< "sv1*=5.0; sv1=" << sv1 << "\n";

	sv1*=0.0;
	mystream<< "sv1*=0.0; sv1=" << sv1 << "\n";

	mystream << "\n";
}




