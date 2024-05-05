#include "SampleExam2015MTQ3/SampleExam2015Q3Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;
using namespace exercises;
using namespace utils;

const string fileName = (string)COURSE_OUTPUT_DIR + "/SampleExam2015/SampleExam2015MTQ3/SampleExamQ3_output.txt";
double dK = 0.75;


void testTridiSolver(MyStream & mystream);
void testFiniteDifferenceSolver(MyStream & mystream);

double payoff(double);

int main()
{
  cout << "Output being written to: " << fileName << "\n";
  fstream myfile;
  myfile.open (fileName, ios::in | ios::out | ios::trunc);
  MyStream mystream(myfile);
  mystream << "\n";
  mystream << sMyName << "\n";
  mystream << "\n";

  testTridiSolver(mystream);
  testFiniteDifferenceSolver(mystream);

  myfile.close();
  return 0;
}

double payoff(double dArg)
{
  return dArg>dK ? dArg-dK : 0.0;
}

void testTridiSolver(MyStream & mystream)
{

  DVector a(4), b(4), c(4), x(4);

  for(size_t i=0; i<4; ++i){
    a[i]=-0.5*(i+1);
    b[i]=(i+1);
    c[i]=a[i];
  }
  x[0]=7.0;
  x[1]=9.0;
  x[2]=2.0;
  x[3]=3.0;
		
  mystream<< "\n";
  mystream<< "****************************************************" << "\n";
  mystream<< "*                Testing tridiSolver               *" << "\n";
  mystream<< "****************************************************" << "\n";
	
  size_t n=a.size();
	
  for(size_t i=0; i<n; ++i){
    mystream << " a[" << i << "]=" << a[i] <<
      ",\t b[" << i << "]=" << b[i] <<
      ",\t c[" << i << "]=" << c[i] <<
      ",\t x[" << i << "]=" << x[i] <<
      "\n";
  }

  tridiSolver(a,b,c,x);

  mystream << "\n";
  mystream << "The solution of diag[a,b,c]*y=x is:" << "\n";

  for(size_t i=0; i<n; ++i)
    mystream << "y[" << i << "]=" << x[i] << "\n";
	
  mystream << "\n";
  mystream << "Testing solution." << "\n";
  mystream << "x=diag[a,b,c]*y" << "\n";

  mystream << "x[" << 0 << "]=" <<           x[0]*b[0]+x[1]*c[0] << "\n";
  mystream << "x[" << 1 << "]=" << x[0]*a[1]+x[1]*b[1]+x[2]*c[1] << "\n";
  mystream << "x[" << 2 << "]=" << x[1]*a[2]+x[2]*b[2]+x[3]*c[2] << "\n";
  mystream << "x[" << 3 << "]=" << x[2]*a[3]+x[3]*b[3]           << "\n";
}


void testFiniteDifferenceSolver(MyStream & mystream)
{
  double dSmax = 1.5;
  double dT = 0.75;
  double dR = 0.05;
  double sigma = 0.32;
  size_t n = 1000;
  size_t m = 100;

  DMatrix res=implicitFiniteDifferenceSolver(dSmax,dT,dR,sigma,n,m,payoff);

  mystream << "\n";
  mystream << "****************************************************" << "\n";
  mystream << "*      Testing implicitFiniteDifferenceSolver      *" << "\n";
  mystream << "****************************************************" << "\n";

  mystream << "\n";
  mystream << "parameters:" << "\n";

  mystream << "Smax=" << dSmax << "\n";
  mystream << "T=" << dT << "\n";
  mystream << "r=" << dR << "\n";
  mystream << "sigma=" << sigma << "\n";
  mystream << "n=" << n << "\n";
  mystream << "m=" << m << "\n";

  mystream << "Payoff: call with strike " << dK << "\n";

  mystream << "\n";
  mystream << "results:" << "\n";

  size_t step = n/10;

  for(size_t i=0; i<n; i+=step){
    mystream << "S=" << res[0][i] << ",\t V=" << res[1][i] << ",\t BS price=" <<
      BSOptionPrice(res[0][i],dK,dT,dR,sigma,true) << "\n";
  }
}
