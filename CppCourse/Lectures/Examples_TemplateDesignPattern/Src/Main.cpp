#include "Examples_TemplateDesignPattern/Integrator.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <iomanip>

using namespace integrator;
using namespace std;


void testIntegrators();

int main()
{
	testIntegrators();
	return 0;
}

template<class Integrator>
void testSolver(
    vector<double> const& ts,
    vector<double> const& ks,
    vector<pair<double, double> > testTs,
    string const& label
    )
{

    cout << "********* Test case *********" << endl;
    cout << "Integrator: " << label << endl;
    cout << "ts: " << std::fixed << std::setprecision(1);
    copy(ts.cbegin(), ts.cend(), ostream_iterator<double>(cout, ", "));
    cout << endl;

    cout << "ks: " << std::fixed << std::setprecision(1);
    copy(ks.cbegin(), ks.cend(), ostream_iterator<double>(cout, ", "));
    cout << endl;

    Integrator integrator(ts, ks);

    for(const auto& p : testTs)
    {
        cout << std::fixed << std::setprecision(2) << "S:t " << p.first << ", T: " << p.second <<
            ", integral(S,T): " << std::setprecision(5) << integrator(p.first, p.second) << endl;
    }

    cout << "********* End of test case *********" << endl;

}

void testIntegrators(){

    vector<double> ts1{ 1.0, 1.5, 2.5 };
    vector<pair<double, double> > testTs1
        { {0.5, 0.5}, {0.5, 0.75}, {0.5, 1.0},  {0.5, 1.2}, {0.5, 1.5}, {0.5, 2.0}, {0.5, 2.5}, {0.5, 3.0},
          {1.0, 1.0}, {1.0, 1.2},  {1.0, 1.5},  {1.0, 1.75}, {1.0, 2.5}, {1.0, 3.0},
          {1.2, 1.2}, {1.2, 1.4},  {1.2, 1.5},  {1.2, 2.0},  {1.2, 2.5}, {1.2, 3.0},
          {1.5, 1.5}, {1.5, 2.0},  {1.5, 2.5},  {1.5, 3.0},
          {1.75, 1.75}, {1.75, 2.0}, {1.75, 2.5}, {1.75, 3.0},
          {2.5, 2.5}, {2.5, 3.0},
          {3.0, 3.0}, {3.0, 4.0},
          {1.0, 0.5}, {1.5, 1.0}, {2.0, 1.75}, {3.0, 0.5}
          };
    std::vector<vector<double>> kss1{
            { 2.0, 2.0, 2.0},
            { 2.0, 4.0, 3.0},
            { 3.0, 4.0, 2.0}
        };

    vector<double> ts2{ 1.0 };
    std::vector<vector<double>> kss2{ {5.0} };
    vector<pair<double, double> > testTs2
        {{0.0, 0.5}, {0.0, 1.0}, {0.0, 2.0},
         {1.0, 1.0}, {1.0, 2.0}, {2.0, 2.0}, {2.0, 3.0},
         {0.5, 0.0}, {1.0, 0.5}, {2.0, 1.0}, {2.0, 0.0}};
  
    cout<< endl;
    cout<< "******************************************" << endl;
    cout<< "*   Testing PieceWiseConstFnIntegrator   *" << endl;
    cout<< "******************************************" << endl;
    string label = "PieceWiseConstFnIntegrator";
    for(auto const& ks : kss1)
    {
        testSolver<PieceWiseConstFnIntegrator>(ts1, ks, testTs1, label);
    }
    for(auto const& ks : kss2)
    {
        testSolver<PieceWiseConstFnIntegrator>(ts2, ks, testTs2, label);
    }

    cout<< endl;
    cout<< "******************************************" << endl;
    cout<< "*   Testing PieceWiseLinearFnIntegrator  *" << endl;
    cout<< "******************************************" << endl;
    label = "PieceWiseConstFnIntegrator";
    for(auto const& ks : kss1)
    {
        testSolver<PieceWiseLinearFnIntegrator>(ts1, ks, testTs1, label);
    }
    for(auto const& ks : kss2)
    {
        testSolver<PieceWiseLinearFnIntegrator>(ts2, ks, testTs2, label);
    }

    cout << endl;
}

