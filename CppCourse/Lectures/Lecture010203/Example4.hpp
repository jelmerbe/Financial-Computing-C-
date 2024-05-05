#include <iostream>

void swap1(int a, int b)
{
	int temp=a;
	a=b;
	b=temp;
}

void swap2(int & a, int & b)
{
	int temp=a;
	a=b;
	b=temp;
}

void swap3(int *a, int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void Example4()
{
  header(4);
 
 
 
 

  int a(1), b(2);
  std::cout<< "Before calling swap1 on a and b," << std::endl;
  std::cout<< "a: " << a << " b: " << b << std::endl;
  swap1(a,b);
  std::cout<< "After calling swap1 on a and b," << std::endl;
  std::cout<< "a: " << a << " b: " << b << std::endl;

	
  std::cout<< "Before calling swap2 on a and b," << std::endl;
  std::cout<< "a: " << a << " b: " << b << std::endl;
  swap2(a,b);
  std::cout<< "After calling swap2 on a and b," << std::endl;
  std::cout<< "a: " << a << " b: " << b << std::endl;

  std::cout<< "Before calling swap3 on a and b," << std::endl;
  std::cout<< "a: " << a << " b: " << b << std::endl;
  swap3(&a,&b); // note: addresses are passed
  std::cout<< "After calling swap3 on a and b," << std::endl;
  std::cout<< "a: " << a << " b: " << b << std::endl;
 
	//...
}

/*
   Before calling swap1 on a and b,
   a: 1 b: 2
   After calling swap1 on a and b,
   a: 1 b: 2
   Before calling swap2 on a and b,
   a: 1 b: 2
   After calling swap2 on a and b,
   a: 2 b: 1
   Before calling swap3 on a and b,
   a: 2 b: 1
   After calling swap3 on a and b,
   a: 1 b: 2
*/
