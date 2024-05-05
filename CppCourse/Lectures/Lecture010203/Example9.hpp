typedef double (*MyFunType)(double);

// function declarations
double fn1(double);
double fn2(double);

void Example9() {
  header(9);
  MyFunType fnPtr1=&fn1; //fn1 has been declared, can be used
  MyFunType fnPtr2=fn2;  //fn2 has been declared, can be used
  std::cout << "fnPtr1 evaluated at 3.0: "
	    << fnPtr1(3.0) << std::endl;
  std::cout << "fnPtr2 evaluated at 3.0: "
	    << fnPtr2(3.0) << std::endl;
}

// function implementation
double fn1(double dArg){
  return dArg+2.0;}
double fn2(double dArg){
  return dArg*dArg;}

/*
  fnPtr1 evaluated at 3.0: 5
  fnPtr2 evaluated at 3.0: 9
*/
