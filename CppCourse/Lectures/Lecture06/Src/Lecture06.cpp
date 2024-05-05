#include "Lecture06/LinkedLists.hpp"

using namespace std;


template<class L>
void testList(unsigned int m, unsigned int n) {
  for(unsigned int i=0; i<m; i++){
    // create list    
    L l(0); 
    if(i % 100 == 0)
      cout << "\ti: " << i << endl;
    for(unsigned int j=1; j<n; j++)
      l.append(j);
    //  local l is destroyed
  }
}

template<class L>
void dummyPrint(L l) {
  cout << "List printed from dummyPrint: " << l << endl;
}

template<class L>
void testDummyPrint() {
  L l(123);
  l.append(234);
  l.append(345);
  cout << "**************************************" << endl;
  cout << "Testing pass-by-value" << endl;
  cout << "Test list: " << l << endl;
  dummyPrint(l);
  cout << "Test list after dummy print: " << l << endl;
}

// command line arguments
// under linux/mac run it: ./Lecture06 1000 500 1
// in VS specify command line arguments in Project->Properties

int main(int argc, char* argv[]) {
  
  cout << "**************************************" << endl;
  cout << "Running " << argv[0] << endl;
  cout << "**************************************" << endl;
  if(argc<4){
    cout << "At least three arguments are expected" << endl;
    return 0;
  }
  
  unsigned int m(atoi(argv[1]));
  unsigned int n(atoi(argv[2]));
  unsigned int t(atoi(argv[3]));

  // this is not very elegant, later we'll see better solutions
  switch (t){
  case 1:
    testList<LinkedList01>(m,n);
    testDummyPrint<LinkedList01>();
    break;
  case 2:
    testList<LinkedList02>(m,n);
    testDummyPrint<LinkedList02>();
    break;
  case 3:
    testList<LinkedList03>(m,n);
    testDummyPrint<LinkedList03>();
    break;
  case 4:
    testList<LinkedList04>(m,n);
    testDummyPrint<LinkedList04>();
    break;
  default:
    cout << "Third argument should be one of (1,2,3,4)" << endl;
    return 0;
  }

  cout << "Test completed" << endl;
  return 0;
}

// exercises:
// -- length of list
// -- check if a particular value is an element
// -- return last element in the list
// -- return next to last element in the list
// -- implement deep copy
// -- why hard coded int? create a template'd version

