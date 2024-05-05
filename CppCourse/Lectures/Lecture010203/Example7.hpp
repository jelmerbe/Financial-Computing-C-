#include <iostream>

void Example7()
{
  header(7);

  int a(1);
  int * ptr1=&a;   //the address of 'a' is taken
  std::cout<< "Value of 'a' after first assignment: " 
	   << a << std::endl;
  std::cout<< "Value of 'a' accessed through its address: "
	   << *ptr1 << std::endl;
  *ptr1+=2;   //value of 'a' is changed
  std::cout<< "Changing the value of 'a' through its "
	   << "address: " << a << std::endl;
  int * ptr2=new int(3);   //new variable on the heap
  std::cout<< "The value stored at the address ptr2: " 
	   << *ptr2 << std::endl;
  delete ptr2;   //must be deleted at some point
  std::cout<< "The value stored at the address ptr2 "
	   << "after releasing memory: " << *ptr2 << std::endl;

}

/*
  Value of 'a' after first assignment: 1
  Value of 'a' accessed through its address: 1
  Changing the value of 'a' through its address: 3
  The value stored at the address ptr2: 3
  The value stored at the address ptr2 after 
  releasing memory: 3
*/
