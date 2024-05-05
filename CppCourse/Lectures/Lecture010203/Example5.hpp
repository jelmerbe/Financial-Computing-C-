#include <iostream>

typedef double (*MyFunType)(double);


double myFun1(double dArg)
{ return dArg+2.0;}
double myFun2(double dArg)
{ return dArg*dArg;}



void Example5()
{
  header(5);
 
 
 
 

  MyFunType fnPtr1=&myFun1;
  MyFunType fnPtr2=myFun2;

  std::cout << "fnPtr1 evaluated at 3.0: " << fnPtr1(3.0) << std::endl;
  std::cout << "fnPtr2 evaluated at 3.0: " << fnPtr2(3.0) << std::endl;
}
