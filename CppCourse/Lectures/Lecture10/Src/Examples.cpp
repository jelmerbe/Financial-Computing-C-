#include "Lecture10/Examples.hpp"
#include <iostream>
#include <string>

using namespace std;

double thirdOfSecondElement(const dVector & vec){
  PRECONDITION(vec.size()>=2); // assertion checked in debug mode
  return vec[1]/3.0;  
}

double thirdOfSecondElementWithBoundCheck(const dVector & vec){
  if(vec.size()<2)
    throw string("Input vector has less than two entries; at least two are required.");

  return vec[1]/3.0;
}

void callThirdOfSecondElementExample() {
  dVector vec1(2,1.1);  
  cout << "Result of thirdOfSecondElement(vec1): " << thirdOfSecondElement(vec1) << endl;

  dVector vec2(1,1.1);
  // try block, attempted execution
  try{ 
    cout << "Result of thirdOfSecondElementWithBoundCheck(vec2): " 
	 << thirdOfSecondElementWithBoundCheck(vec2) << endl;
  }
  // catch block handles potential errors
  catch(const string msg){
    cout << msg << endl;
  }

 /*
Assertion failed: (vec.size()>=2), 
function thirdOfSecondElement, 
file Examples.cpp, line 8.
 */



}
