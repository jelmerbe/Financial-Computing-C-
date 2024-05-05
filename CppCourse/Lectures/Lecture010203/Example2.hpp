#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>

void Example2()
{

  header(2);




  double dMark;
  std::vector<double> vMarks;
  std::cout << "Please, type in your marks." << std::endl;

  while(std::cin >> dMark)
    vMarks.push_back(dMark);

	// this is a bit technical, required to restore the input stream
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	// end of technical part

  double dAverage(0);
  std::vector<double>::size_type MarksSize=vMarks.size(), i;

  for(i=0; i<MarksSize; ++i)
    dAverage+=vMarks[i];
	
  dAverage/=MarksSize;

  std::sort(vMarks.begin(), vMarks.end());
  double median=vMarks[MarksSize/2];

  std::cout<< "The median is " << median <<
    " and the average is: " << std::setprecision(4)
	   << dAverage << std::endl;
}
