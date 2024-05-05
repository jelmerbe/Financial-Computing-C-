#include <iostream>

void Example6()
{
  header(6);

  int a; // 'a' plain simple variable
  int & b=a; // 'b' is a reference to 'a'

  a=1;
  std::cout << "After a=1, a: " << a << " b: " << b << std::endl;
	
  b=2;
  std::cout << "After b=2, a: " << a << " b: " << b << std::endl;
}

/* 
  After a=1, a: 1 b: 1
  After b=2, a: 2 b: 2
*/
