#ifndef __DERIVED_EXAMPLES_HPP__
#define __DERIVED_EXAMPLES_HPP__

#include <string>

class Base {
public:
  virtual ~Base(){}
  virtual void memberFn(Base & base) {
    std::cout << "virtual member of Base" << std::endl;
  }
};

class Derived : public Base
{
public:
  //overridden virtual function
  void memberFn(Base & base) { 
    std::cout << "overridden virtual of Derived" << std::endl;
  }
  //non-virtual member, overloads memberFn(),
  //feature in Derived only
  void memberFn(Derived & derived) {
    std::cout << "additional feature of Derived" << std::endl;
  }
};

class BaseWithDefect {
public:
  BaseWithDefect(std::string name) : m_name(name) {}
  ~BaseWithDefect(){
    std::cout << "BaseWithDefect with name " << m_name 
	      << " is being destroyed." << std::endl;
  }

private:
  std::string m_name;
};

class DerivedFromBWD : public BaseWithDefect {
public:
  DerivedFromBWD(std::string name1, std::string name2) : 
    BaseWithDefect(name1), m_name2(name2) {}
  ~DerivedFromBWD(){
    std::cout << "DerivedFromBWD with name " << m_name2 
	      << " is being destroyed." << std::endl;
  }

private:
  std::string m_name2;
};


#endif
