#include "ExamQ1/Exam2023Q1Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;
using namespace exercises;
using namespace utils;

void testMeanStdevRate(MyStream & mystream);
void testBondPrice(MyStream & mystream);
void testBondOptionMonteCarlo(MyStream & mystream);

const string fileName = (string)COURSE_OUTPUT_DIR + "/Exam/ExamQ1/ExamQ1_output.txt";
int main()
{
    cout << "Output being written to: " << fileName << "\n";
    fstream myfile;
    myfile.open (fileName, ios::in | ios::out | ios::trunc);
    MyStream mystream(myfile);
    mystream << "\n";
    mystream << "\n";

    testMeanStdevRate(mystream);
    testBondPrice(mystream);
    testBondOptionMonteCarlo(mystream);

    myfile.close();
    return 0;
}

double discount_fn(double t)
{
    const double initial_flat_rate = 0.03;
    return std::exp(-t * initial_flat_rate);
}

void testMeanStdevRate(MyStream & mystream){
    
    mystream<< "\n";
    mystream<< "*****************************" << "\n";
    mystream<< "*   Testing MeanStdevRate   *" << "\n";
    mystream<< "*****************************" << "\n";

    std::vector<double> as {0.0, 0.01, 0.1};
    std::vector<double> sigmas {0.05, 0.1};
    std::vector<double> Ts {0.5, 1.75};

    for( auto const& a : as)
    {
        for( auto const& sigma : sigmas)
        {
            for( auto const& T : Ts)
            {
                mystream << "Parameters: ";
                mystream << "\t a: " << a << "\t sigma: " << sigma << "\t T: "<< T << "\n";
                RateParameters params{a, sigma, discount_fn};
                auto res = MeanStdevRate(params, T);
                mystream << "Results:\t Mean: " << res.first << "\t Stdev: " << res.second << "\n";
            }
        }
    }

    mystream << "\n";
}

void testBondPrice(MyStream & mystream)
{
    mystream<< "\n";
    mystream<< "*****************************" << "\n";
    mystream<< "*     Testing BondPrice     *" << "\n";
    mystream<< "*****************************" << "\n";

    std::vector<double> as {0.0, 0.01};
    std::vector<double> sigmas {0.05, 0.1};
    std::vector<double> T1s {0.5, 1.75};
    std::vector<double> T2s {2.0, 3.0};
    std::vector<double> rs {0.02, 0.04};

    for( auto const& a : as)
    {
        for( auto const& sigma : sigmas)
        {
            for( auto const& T1 : T1s)
            {
                for( auto const& T2 : T2s)
                {
                    mystream << "Parameters: ";
                    mystream << "\t a: " << a << "\t sigma: " << sigma << "\t T1: " << T1 << "\t T2: " << T2
                             << "\n";
                    RateParameters rate_params{a, sigma, discount_fn};
                    BondParameters bond_params{T1, T2};
                    mystream << "Results: ";
                    for( auto const& r : rs) {

                        auto res = BondPrice(r, bond_params, rate_params);
                        mystream << " r: " << r << " bond price: " << res << ";";
                    }
                    mystream << "\n";
                }
            }
        }
    }

    mystream << "\n";
}

double bond_option_formula(
        const RateParameters& rateParameters,
        const BondParameters & bondParameters,
        double strike
        )
{
    const RateParameters& rp = rateParameters;
    const BondParameters& bp = bondParameters;
    const double P1 = rp.discountFunction(bp.T1);
    const double P2 = rp.discountFunction(bp.T2);
    double B, sigmaTemp;
    if(rp.beta <= 1.0e-14)
    {
        B = bp.T2 - bp.T1;
        sigmaTemp = bp.T1;
    }
    else
    {
        B = (1.0 - std::exp(-rp.beta*(bp.T2 - bp.T1))) / rp.beta;
        sigmaTemp = 0.5 * (1.0 - std::exp(-2.0 * rp.beta * bp.T1)) / rp.beta;
    }
    const double sigma_p = rp.sigma * std::sqrt(sigmaTemp) * B;
    const double h = (1.0 / sigma_p) * std::log(P2 / (P1 * strike))
            + 0.5 * sigma_p;
    return utils::normcf(h) * P2 - strike * utils::normcf(h - sigma_p) * P1;
}

void testBondOptionMonteCarlo(MyStream & mystream) {
    mystream << "\n";
    mystream << "********************************" << "\n";
    mystream << "* Testing BondOptionMonteCarlo *" << "\n";
    mystream << "********************************" << "\n";

    std::vector<double> as{0.0, 0.01};
    std::vector<double> sigmas{0.05, 0.1};
    std::vector<double> T1s{0.5, 1.75};
    std::vector<double> T2s{2.0, 3.0};
    unsigned int sample_size = 10000;
    const double strike = 0.8;
    auto bond_option_payoff = [&strike](double bond_price)-> double
                                                    { return std::max(bond_price - strike, 0.0); };
    for (auto const &a: as) {
        for (auto const &sigma: sigmas) {
            for (auto const &T1: T1s) {
                for (auto const &T2: T2s) {
                    mystream << "Parameters: ";
                    mystream << "\t a: " << a << "\t sigma: " << sigma << "\t T1: " << T1 << "\t T2: " << T2
                             << "\n";
                    RateParameters rate_params{a, sigma, discount_fn};
                    BondParameters bond_params{T1, T2};
                    auto res = BondOptionMonteCarlo(rate_params, bond_params, bond_option_payoff, sample_size);
                    const double closed_form_price = bond_option_formula(rate_params, bond_params, strike);
                    mystream << "Results:\t MCMean: " << res.first << "\t MCStdev: " << res.second;
                    mystream << "\t exact price for reference: " << closed_form_price << "\n";
                }
            }
        }
    }
    mystream << "\n";
}