#include <iostream>

void Example3()
{
  header(3);
 
 
 
 

  enum Month{jan=1, feb, mar, apr, may, jun,
	     jul, aug, sep, oct, nov, dec};
  std::cout << "Please type in the current " << 
     "month (in form of an integer)!" << std::endl;
  int iInput;
  std::cin >> iInput;
  Month mInput=Month(iInput);

  switch(mInput){
    case jan: case mar: case may: case jul:
    case aug: case oct: case dec:
      std::cout<< "There are 31 days in this month."<< std::endl;
      break;
    case apr: case jun: case sep: case nov:
      std::cout<< "There are 30 days in this month."<< std::endl;
      break;
    case feb:
      std::cout << "There are 28 days in this month, " <<
	"unless it's a leap year." << std::endl;
      break;
    default:
      std::cout << "That's not a month." << std::endl;
      break;
  }
}
