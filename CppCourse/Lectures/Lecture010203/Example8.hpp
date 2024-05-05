#include <iostream>

#if __cplusplus >= 201402L  || (defined(_MSC_VER) && _MSC_VER >= 1916)
    #include <memory> // c++11
    namespace ptrnamespace = std;
#else
    #include <boost/shared_ptr.hpp> // boost
    namespace ptrnamespace = boost;
#endif

// ptrnamespce = std if c++11 supported, otherwise ptrnamespce = boost

typedef ptrnamespace::shared_ptr<int> int_ptr;
//defining an alternative name for the type name

int_ptr returnPointer(int Arg){
   //int_ptr pVal(new int(Arg)); // works, but... 
   int_ptr pVal(ptrnamespace::make_shared<int>(Arg)); // safer way 
   return pVal;
}

void Example8() {
  header(8);
  int_ptr pTemp=returnPointer(1);
  std::cout<< "Value: " << *pTemp << std::endl;
}  // 'pTemp' is out of scope and automatically deleted here

