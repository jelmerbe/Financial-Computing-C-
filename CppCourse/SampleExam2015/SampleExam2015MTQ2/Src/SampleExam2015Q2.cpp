#include "SampleExam2015MTQ2/SampleExam2015Q2Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace exercises;
using namespace utils;

void testPolynomialInterpolator(MyStream & mystream);

const string fileName = (string)COURSE_OUTPUT_DIR + "/SampleExam2015/SampleExam2015MTQ2/SampleExamQ2_output.txt";
int main()
{
  cout << "Output being written to: " << fileName << "\n";
  fstream myfile;
  myfile.open (fileName, ios::in | ios::out | ios::trunc);
  MyStream mystream(myfile);
  mystream << "\n";
  mystream << sMyName << "\n";
  mystream << "\n";

  testPolynomialInterpolator(mystream);

  myfile.close();
  return 0;
}

void testPolyEval(polynomialInterpolator & pI, dVector & xVals, MyStream & mystream);

void testPolynomialInterpolator(MyStream & mystream){
    
  mystream<< "\n";
  mystream<< "********************************************************" << "\n";
  mystream<< "* Testing interpolator with empty x-val, y-val vectors *" << "\n";
  mystream<< "********************************************************" << "\n";
  
  dVector xValsTest, xVals, yVals;
  const unsigned int ntest = 10;
  double xtest[ntest] = {0.0, 0.25, 0.5, 1.0, 1.25, 1.75, 2.0, 2.3, 2.6, 3.0};
  for(unsigned int i=0; i<ntest; i++)
    xValsTest.push_back(xtest[i]);

  polynomialInterpolator pI1(xVals,yVals);
  mystream << "Evaluating the polynomial " << "\n";
  testPolyEval(pI1, xValsTest, mystream);
  
  mystream<< "********************************************************" << "\n";
  mystream<< "*         Adding points to an empty polynomial         *" << "\n";
  mystream<< "********************************************************" << "\n";

  const unsigned int n = 5;  
  double xinput[n] = {0.0, 0.5, 1.25, 2.0, 2.6};
  double yinput[n] = {1.0, 1.0, -2.5, 4.0, 3.14159265};
  
  for(unsigned int i = 0; i<3; i++){
    double x=xinput[2*i];
    double y=yinput[2*i];
    mystream << "Adding x: " << x << ", y: " << y << "\n";
    pI1.addPoint(x,y);
    mystream << "Evaluating the extended polynomial" << "\n";
    testPolyEval(pI1, xValsTest, mystream);
  }


  mystream<< "********************************************************" << "\n";
  mystream<< "*        Constructing a non-empty interpolator         *" << "\n";
  mystream<< "********************************************************" << "\n";

  const unsigned int nInp=3;
  xVals.resize(nInp), yVals.resize(nInp);
  mystream << "Input values" << "\n";
  for(unsigned int i=0; i<3; i++){
    xVals[i] = xinput[i];
    yVals[i] = yinput[i];
    mystream << "\tx: " << xVals[i] << ",\ty: " << yVals[i] << "\n";
  }
  
  polynomialInterpolator pI2(xVals,yVals);
  mystream << "Evaluating the polynomial " << "\n";
  testPolyEval(pI2, xValsTest, mystream);

  mystream<< "********************************************************" << "\n";
  mystream<< "*                  Adding more point                   *" << "\n";
  mystream<< "********************************************************" << "\n";

  for(unsigned int i = nInp; i<n; i++){
    double x=xinput[i];
    double y=yinput[i];
    mystream << "Adding x: " << x << ", y: " << y << "\n";
    pI2.addPoint(x,y);
    mystream << "Evaluating the extended polynomial" << "\n";
    testPolyEval(pI2, xValsTest, mystream);
  }

  mystream << "\n";
}

void testPolyEval(polynomialInterpolator & pI, dVector & xVals, MyStream & mystream){
  for(unsigned int i=0; i<xVals.size(); i++){
    mystream << "\tx: " << xVals[i] << "\tp(x): " << pI(xVals[i]) << "\n";    
  }
  mystream << "\n";
}
