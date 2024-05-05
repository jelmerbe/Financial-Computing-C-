#include "Lecture11/Member.hpp"
#include "Lecture11/DerivedExample.hpp"
#include <vector> 
#if __cplusplus >= 201402L  || (defined(_MSC_VER) && _MSC_VER >= 1916)
    #include <memory>
    #include <cstddef>
    namespace sptr = std;
#else
    #include <boost/shared_ptr.hpp>
    #include <boost/enable_shared_from_this.hpp>
    namespace sptr = boost;
#endif


using namespace std;

void testMembers();
void testSlicing();
void testPolymorphism();
void testFunction1(UniversityMember um);
void testFunction2(UniversityMember & um);
void testTestFunctions();
void testDerived();
void testDestructor();

int main() {
  testMembers();
  testSlicing();
  testPolymorphism();
  testTestFunctions();
  testDerived();
  testDestructor();
  return 0;
}

void testMembers() {
  UniversityMember um("John","Doe");
  Student st("Howard","Wolowitz", "St Hugh's",
	     "MSc Engineering");
  Faculty fa("Sheldon","Cooper","Physics",8);

  cout << "um: " << um << endl;
  cout << "um.getName(): " << um.getName() << endl << endl;
  cout << "st: " << st << endl;
  cout << "st.getName(): " << st.getName() << endl << endl;
  cout << "fa: " << fa << endl;
  cout << "fa.getName(): " << fa.getName() << endl << endl;
}
/*
  um: Name: John Doe
  um.getName(): Name: John Doe

  st: Name: Howard Wolowitz, College: St Hugh's, 
  Course: MSc Engineering
  st.getName(): Name: Howard Wolowitz

  fa: Name: Sheldon Cooper, Department: Physics, Grade: 8
  fa.getName(): Name: Sheldon Cooper
*/

void testSlicing(){
  UniversityMember um("John","Doe");
  Student st("Howard","Wolowitz", "St Hugh's",
	     "MSc Engineering");
  Faculty fa("Sheldon","Cooper","Physics",8);

  vector<UniversityMember> vec1;
  vec1.push_back(um);
  vec1.push_back(st);
  vec1.push_back(fa);
  cout << "Slicing: .printeDetails() called on values\n";
  for(unsigned int i=0; i<vec1.size(); ++i)
    (vec1[i].printDetails(cout) )<< endl;
}
/*
  Slicing: .printeDetails() called on values
  Name: John Doe
  Name: Howard Wolowitz
  Name: Sheldon Cooper
*/
void testPolymorphism() {
  UniversityMember um("John","Doe");
  Student st("Howard","Wolowitz", "St Hugh's",
	     "MSc Engineering");
  Faculty fa("Sheldon","Cooper","Physics",8);
  
  typedef sptr::shared_ptr<UniversityMember> UMPtr;
  vector<UMPtr> vec2;
  vec2.push_back(sptr::make_shared<UniversityMember>(um));
  vec2.push_back(sptr::make_shared<Student>(st));
  vec2.push_back(sptr::make_shared<Faculty>(fa));
  cout << "\nPolymorphism: ->printeDetails() called on pointers\n";
  for(unsigned int i=0; i<vec2.size(); ++i)
    (vec2[i]->printDetails(cout) ) << endl;
}
/*
  Polymorphism: ->printeDetails() called on pointers
  Name: John Doe
  Name: Howard Wolowitz, College: St Hugh's, 
  Course: MSc Engineering
  Name: Sheldon Cooper, Department: Physics, Grade: 8
*/
void testFunction1(UniversityMember um) {
//argument taken by value, derived part sliced
  um.printDetails(cout);
  cout << endl;
}
void testFunction2(UniversityMember & um) {
//argument taken by reference, derived part kept
  um.printDetails(cout);
  cout << endl;
}
void testTestFunctions(){
  UniversityMember um("John","Doe");
  Student st("Howard","Wolowitz", "St Hugh's",
	     "MSc Engineering");
  Faculty fa("Sheldon","Cooper","Physics",8);

  cout << "\nPolymorphism via reference\n";
  cout << "testFunction1(um): " ;
  testFunction1(um);
  cout << "testFunction1(st): " ;
  testFunction1(st);
  cout << "testFunction1(fa): " ;
  testFunction1(fa);
  cout << "testFunction2(um): " ;
  testFunction2(um);
  cout << "testFunction2(st): " ;
  testFunction2(st);
  cout << "testFunction2(fa): " ;
  testFunction2(fa);
}
/*
  Polymorphism via reference
  testFunction1(um): Name: John Doe
  testFunction1(st): Name: Howard Wolowitz
  testFunction1(fa): Name: Sheldon Cooper
  testFunction2(um): Name: John Doe
  testFunction2(st): Name: Howard Wolowitz, College: St Hugh's, 
  Course: MSc Engineering
  testFunction2(fa): Name: Sheldon Cooper, Department: Physics, 
  Grade: 8
*/
void testDerived() {
  Base b;
  Derived d;
  Base & rb1 = b;
  Base & rb2 = d;
  Derived & rd = d;
  cout << "\nTesting base-derived\n";
  rb1.memberFn(rb1);
  rb1.memberFn(rb2);
  rb1.memberFn(rd);
  rb2.memberFn(rb1);
  rb2.memberFn(rb2);
  rb2.memberFn(rd);
  rd.memberFn(rb1);
  rd.memberFn(rb2);
  rd.memberFn(rd);
}
/*
  Testing base-derived
  virtual member of Base
  virtual member of Base
  virtual member of Base
  overridden virtual of Derived
  overridden virtual of Derived
  overridden virtual of Derived
  overridden virtual of Derived
  overridden virtual of Derived
  additional feature of Derived
*/
void testDestructor(){
  cout << "\nTesting destructor\n";
  BaseWithDefect * bptr1 = new BaseWithDefect("Zero BWD.");
  BaseWithDefect * bptr2 = new DerivedFromBWD("First BWD.","First D.");
  DerivedFromBWD * dptr  = new DerivedFromBWD("Second BWD.","Second D.");
  delete bptr1;
  delete bptr2;
  delete dptr;
}
/*
  Testing destructor
  BaseWithDefect with name Zero BWD. is being destroyed.
  BaseWithDefect with name First BWD. is being destroyed.
  DerivedFromBWD with name Second D. is being destroyed.
  BaseWithDefect with name Second BWD. is being destroyed.
*/
