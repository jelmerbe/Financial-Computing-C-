#include "Practical03/Practical03Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace exercises;
using namespace std;
using namespace utils;

void testLength(MyStream & mystream);
void testHasElement(MyStream & mystream);
void testLastElement(MyStream & mystream);
void testNextToLastElement(MyStream & mystream);
void testClone(MyStream & mystream);
LinkedList03 sampleList(unsigned int length);

const string fileName = (string)COURSE_OUTPUT_DIR + "/Practicals/Practical03/Practical03_output.txt";
int main()
{
    cout << "Output being written to: " << fileName << "\n";
	fstream myfile;
	myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
    mystream << "\n";
    mystream << "\n";

    testLength(mystream);
	testHasElement(mystream);
	testLastElement(mystream);
	testNextToLastElement(mystream);
	testClone(mystream);

	myfile.close();
	return 0;
}


void testLength(MyStream & mystream){

  mystream<< "\n";
  mystream<< "*************************************" << "\n";
  mystream<< "*          Testing length           *" << "\n";
  mystream<< "*************************************" << "\n";

  unsigned int n[4] = {1,2,4,16};
  for(unsigned int i(0); i < 4; i++){
    LinkedList03 l = sampleList(n[i]);
    mystream << "Sample list " << i << ": " << l << "\n";
    mystream << "\t length (non-recursive):\t " << length(l) << "\n";
    mystream << "\t length (recursive):\t " << lengthRecursive(l) << "\n";
  }

}

void testHasElement(MyStream & mystream){

  mystream<< "\n";
  mystream<< "*************************************" << "\n";
  mystream<< "*        Testing hasElement         *" << "\n";
  mystream<< "*************************************" << "\n";

  unsigned int n[4] = {1,2,4,16};
  unsigned int e[3] = {0,2,32};
  for(unsigned int i(0); i < 4; i++){
    LinkedList03 l = sampleList(n[i]);
    mystream << "Sample list " << i << ": " << l << "\n";
    mystream << "\t hasElement " << e[0] << " (non-recursive):\t " << (hasElement(l,e[0]) ? "true" : "false")  << "\n";
    mystream << "\t hasElement " << e[1] << " (non-recursive):\t " << (hasElement(l,e[1]) ? "true" : "false") << "\n";
    mystream << "\t hasElement " << e[2] << " (non-recursive):\t " << (hasElement(l,e[2]) ? "true" : "false") << "\n";
    mystream << "\t hasElement " << e[0] << " (recursive):\t " << (hasElementRecursive(l,e[0]) ? "true" : "false") << "\n";
    mystream << "\t hasElement " << e[1] << " (recursive):\t " << (hasElementRecursive(l,e[1]) ? "true" : "false") << "\n";
    mystream << "\t hasElement " << e[2] << " (recursive):\t " << (hasElementRecursive(l,e[2]) ? "true" : "false") << "\n";
  }

  mystream << "\n";

}

void testLastElement(MyStream & mystream){

  mystream<< "\n";
  mystream<< "*************************************" << "\n";
  mystream<< "*       Testing lastElement         *" << "\n";
  mystream<< "*************************************" << "\n";

  unsigned int n[4] = {1,2,4,16};
  for(unsigned int i(0); i < 4; i++){
    LinkedList03 l = sampleList(n[i]);
    mystream << "Sample list " << i << ": " << l << "\n";
    mystream << "\t lastElement (non-recursive):\t " << lastElement(l) << "\n";
    mystream << "\t lastElement (recursive):\t " << lastElementRecursive(l) << "\n";
  }
  mystream << "\n";

}

void testNextToLastElement(MyStream & mystream) {

    mystream << "\n";
    mystream << "*************************************" << "\n";
    mystream << "*        Testing nextToLast         *" << "\n";
    mystream << "*************************************" << "\n";

    unsigned int n[4] = {2, 4, 8, 16};
    for (unsigned int i(0); i < 4; i++) {
        LinkedList03 l = sampleList(n[i]);
        mystream << "Sample list " << i << ": " << l << "\n";
        mystream << "\t next to last element (non-recursive):\t " << nextToLast(l) << "\n";
        mystream << "\t next to last element (recursive):\t " << nextToLastRecursive(l) << "\n";
    }
    mystream << "\n";
}

void testClone(MyStream & mystream){

  mystream<< "\n";
  mystream<< "*************************************" << "\n";
  mystream<< "*           Testing clone           *" << "\n";
  mystream<< "*************************************" << "\n";

  unsigned int n[3] = {2,4,8};
  for(unsigned int i(0); i < 3; i++){
    LinkedList03 l = sampleList(n[i]);
    mystream << "Sample list " << i << ": " << l << "\n";
    LinkedList03 lClone = clone(l);
    mystream << "\t clone of sample list:\t " << lClone << "\n";
    l.setData(0);
    l.getNext()->setData(0);
    mystream << "Modified sample list " << i << ": " << l << "\n";
    mystream << "\t modification should not have impact on the clone:\t " << lClone << "\n";
  }
  mystream << "\n";

}

LinkedList03 sampleList(unsigned int length){
  LinkedList03 l(length-1);
  if(length>0)
    length--;
  for(; length > 0; length--)
    l.append(length-1);
  return l;
}


