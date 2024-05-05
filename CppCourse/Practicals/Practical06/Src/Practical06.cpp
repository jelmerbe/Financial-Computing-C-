#include "Practical06/Function.hpp"
#include "Practical06/Practical06Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <iostream>
#include <fstream>

using namespace exercises;
using namespace std;
using namespace utils;

const string fileName = (string)COURSE_OUTPUT_DIR + "/Practicals/Practical06/Practical06_output.txt";
int main()
{
    cout << "Output being written to: " << fileName << endl;
	fstream myfile;
	myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
	mystream << "\n";
	mystream << "\n";
	
	BVector bvArg1(2);
	bvArg1[0]=0.7;
	bvArg1[1]=2.5;
	BVector bvArg2(1);
	bvArg2[0]=1.1;
	BVector bvArg3(1);
	bvArg3[0]=1.5;
	
	Function callPayoff=CallPayoff(1.0,0);
	Function putPayoff=PutPayoff(1.0,0);
	Function spreadPayoff=SpreadOption(0.8,1.0,1.2,-1.0,0);
	Function straddlePayoff=StraddleOption(0.8,1.0,1.2,1.0,0);
	Function basketPayoff=BasketPayoff();
	Function averagePayoff=AveragePayoff();
	Function sumOfSquares=SumOfSquares();
	BVector bvBase(2);
	bvBase[0]=2.5;
	bvBase[1]=3.5;
	Function innerProduct=InnerProduct(bvBase);
	mystream << "****************************" << "\n";
	mystream << "* Testing payoff functuons *" << "\n";
	mystream << "****************************" << "\n";
	mystream << "\n";
	mystream << "CallPayoff(1.0,0) applied to " << bvArg1 << " yields " << callPayoff(bvArg1) << "\n";
	mystream << "CallPayoff(1.0,0) applied to " << bvArg2 << " yields " << callPayoff(bvArg2) << "\n";
	mystream << "CallPayoff(1.0,0) applied to " << bvArg3 << " yields " << callPayoff(bvArg3) << "\n";
	mystream << "\n";
	mystream << "PutPayoff(1.0,0) applied to " << bvArg1 << " yields " << putPayoff(bvArg1) << "\n";
	mystream << "PutPayoff(1.0,0) applied to " << bvArg2 << " yields " << putPayoff(bvArg2) << "\n";
	mystream << "PutPayoff(1.0,0) applied to " << bvArg3 << " yields " << putPayoff(bvArg3) << "\n";
	mystream << "\n";
	mystream << "SpreadPayoff(0.8,1.0,1.2,-1.0,0) applied to " << bvArg1 << " yields " << spreadPayoff(bvArg1) << "\n";
	mystream << "SpreadPayoff(0.8,1.0,1.2,-1.0,0) applied to " << bvArg2 << " yields " << spreadPayoff(bvArg2) << "\n";
	mystream << "SpreadPayoff(0.8,1.0,1.2,-1.0,0) applied to " << bvArg3 << " yields " << spreadPayoff(bvArg3) << "\n";
	mystream << "\n";
	mystream << "StraddlePayoff(0.8,1.0,1.2,1.0,0) applied to " << bvArg1 << " yields " << straddlePayoff(bvArg1) << "\n";
	mystream << "StraddlePayoff(0.8,1.0,1.2,1.0,0) applied to " << bvArg2 << " yields " << straddlePayoff(bvArg2) << "\n";
	mystream << "StraddlePayoff(0.8,1.0,1.2,1.0,0) applied to " << bvArg3 << " yields " << straddlePayoff(bvArg3) << "\n";
	mystream << "\n";
	mystream << "BasketPayoff applied to " << bvArg1 << " yields " << basketPayoff(bvArg1) << "\n";
	mystream << "AveragePayoff applied to " << bvArg1 << " yields " << averagePayoff(bvArg1) << "\n";
	mystream << "SumOfSquares applied to " << bvArg1 << " yields " << sumOfSquares(bvArg1) << "\n";
	mystream << "InnerProduct initialized with " << bvBase << " and applied to " << bvArg1 << " yields " << innerProduct(bvArg1) << "\n";
	mystream << "\n";

	myfile.close();
	return 0;
}

