#include <iostream>
#include <string>
#include "Lecture010203/header.hpp"

void Example1()
{

  header(1);



 
  std::cout << "Please tell me your first " <<
    "name and your age." << std::endl;

  std::string sFirstName;
  int iAge;

  std::cin >> sFirstName;
  std::cin >> iAge;
  std::cout << "Hi, " << sFirstName << "! " ;
	
  if( iAge<30 )
    std::cout<< "Five years from now, " <<
      "you'll be only " << iAge+5 << ".\n";
  else 
    std::cout << "No offense, but you're old. "
         "Five years from now, you'll be "
	      << iAge+5 << "." << std::endl;
}

/*

   Please tell me your first name and your age.
   Greg
   33
   Hi, Greg! No offense, but you're old. Five years 
   from now, you'll be 38.

   Please tell me your first name and your age.
   Felix
   6
   Hi, Felix! Five years from now, you'll be only 11.

*/
