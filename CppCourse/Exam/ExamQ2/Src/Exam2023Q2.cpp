#include "ExamQ2/Exam2023Q2Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace exercises;
using namespace utils;

void testGaussianIntegrals(MyStream & mystream);

const string fileName = (string)COURSE_OUTPUT_DIR + "/Exam/ExamQ2/ExamQ2_output.txt";
int main()
{
    cout << "Output being written to: " << fileName << "\n";
    fstream myfile;
    myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
    mystream << "\n";
    mystream << "\n";

    testGaussianIntegrals(mystream);

    myfile.close();
    return 0;
}


void testGaussianIntegrals(MyStream & mystream){
    
    mystream<< "\n";
    mystream<< "*****************************" << "\n";
    mystream<< "* Testing GaussianIntegrals *" << "\n";
    mystream<< "*****************************" << "\n";

    const double inf = std::numeric_limits<double>::infinity();

    //std::vector<double> lambdas {1.5, 0.0, -1.5};
    std::vector<double> lambdas {1.0, 2.0, 0.0};
    std::vector<double> left_xs {-inf, -1.5, 0.0};
    std::vector<double> right_xs { 0.0, 1.5, inf};
    std::vector<unsigned int> exponents {4, 3, 2, 1, 0};

    for( auto const& left_x : left_xs)
    {
        for( auto const& right_x : right_xs)
        {
            for( auto const& lambda : lambdas)
            {
                mystream << "Computing E[lambda * xi * indicator{left_x <= lambda * xi <= right_x]\n";
                GaussianIntegrals g(left_x, right_x, lambda);
                for(auto const& i : exponents)
                {
                    double res = g(i);
                    mystream << "left_x: "     << left_x
                             << "\tright_x: "  << right_x
                             << "\tlambda: "   << lambda
                             << "\texponent: " << i
                             << "\tresult: " << res
                             << "\n";
                }
            }
        }
    }

    mystream << "\n";
}


