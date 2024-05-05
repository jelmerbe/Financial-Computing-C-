#include "SampleExam2015MTQ1/SampleExam2015Q1Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace exercises;
using namespace utils;

void testBondPrice(MyStream & mystream);
void testExpectationAndStdev(MyStream & mystream);
void testMonteCarlo(unsigned int sampleSize, MyStream & mystream);
double callAt99(double);
double callAt95(double);
double callAt90(double);
double BondCallOption(double r0, double kappa, double phi, double sigma, double maturityOfBond, double maturityOfOption, double strike);

const string fileName = (string)COURSE_OUTPUT_DIR + "/SampleExam2015/SampleExam2015MTQ1/SampleExamQ1_output.txt";

int main()
{
  cout << "Output being written to: " << fileName << "\n";
  fstream myfile;
  myfile.open (fileName, ios::in | ios::out | ios::trunc);
  MyStream mystream(myfile);
  mystream << "\n";
  mystream << sMyName << "\n";
  mystream << "\n";

  testBondPrice(mystream);
  testExpectationAndStdev(mystream);
  testMonteCarlo(10000, mystream);

  myfile.close();
  return 0;
}

void testBondPrice(MyStream & mystream){

  mystream<< "\n";
  mystream<< "**********************************************" << "\n";
  mystream<< "*       Testing the bond price function       *" << "\n";
  mystream<< "**********************************************" << "\n";
  
  double t(0.5), T, kappa(0.2), phi(0.015), sigma(0.1);

  mystream << "The parameters are: " << "\n";
  mystream << "\tt: "     << t     << "\n";
  mystream << "\tkappa: " << kappa << "\n";
  mystream << "\tphi: "   << phi   << "\n";
  mystream << "\tsigma: " << sigma << "\n";

  double r0(0.005), diff(0.005);
  for(unsigned int i=0; i<5; i++, r0 += diff) {
    T = t;
    mystream << "The price of the bond with maturity " << T << " and at r0=" << r0 << 
      " is " << bondPrice(r0, t, T, kappa, phi, sigma) << "\n";
    T+=0.1;
    mystream << "The price of the bond with maturity " << T << " and at r0=" << r0 << 
      " is " << bondPrice(r0, t, T, kappa, phi, sigma) << "\n";
    T+=1.5;
    mystream << "The price of the bond with maturity " << T << " and at r0=" << r0 << 
      " is " << bondPrice(r0, t, T, kappa, phi, sigma) << "\n";    
  }
  mystream << "\n";
}


void testExpectationAndStdev(MyStream & mystream){

  mystream<< "\n";
  mystream<< "**********************************************" << "\n";
  mystream<< "*      Testing the expectation and stdev      *" << "\n";
  mystream<< "**********************************************" << "\n";
  
  double r0(0.01), kappa(0.2), phi(0.015), sigma(0.1);

  mystream << "The parameters are: " << "\n";
  mystream << "\tr0: "    << r0    << "\n";
  mystream << "\tkappa: " << kappa << "\n";
  mystream << "\tphi: "   << phi   << "\n";
  mystream << "\tsigma: " << sigma << "\n";

  double t(0.0), diff(0.1);
  for(unsigned int i=0; i<10; i++, t+=diff) {
    mystream << "The expected value of the instantaneous rate at t=" << t << 
      " is " << expectedValueOfR(r0,t,kappa,phi) << "\n";
    mystream << "The standard deviation of the instantaneous rate at t=" << t << 
      " is " << standardDeviationOfR(t,kappa,sigma) << "\n";
  }
  mystream << "\n";
}


void testMonteCarlo(unsigned int sampleSize, MyStream & mystream){

  mystream<< "\n";
  mystream<< "**********************************************" << "\n";
  mystream<< "*     Testing the Monte Carlo estimation     *" << "\n";
  mystream<< "**********************************************" << "\n";
  
  double r0(0.01), maturityOfOption(0.5), maturityOfBond(1.5), kappa(0.2), phi(0.015), sigma(0.1);

  mystream << "The parameters are: " << "\n";
  mystream << "\tr0: "    << r0    << "\n";
  mystream << "\tkappa: " << kappa << "\n";
  mystream << "\tphi: "   << phi   << "\n";
  mystream << "\tsigma: " << sigma << "\n";
  mystream << "\tmaturity of option: " << maturityOfOption << "\n";
  mystream << "\tmaturity of bond: " << maturityOfBond << "\n";
  mystream << "\tsample size: " << sampleSize << "\n";

  std::vector<MCResults> res;
  res.push_back(MonteCarloBond(r0,kappa,phi,sigma,maturityOfBond,maturityOfOption,sampleSize,callAt99));
  res.push_back(MonteCarloBond(r0,kappa,phi,sigma,maturityOfBond,maturityOfOption,sampleSize,callAt95));
  res.push_back(MonteCarloBond(r0,kappa,phi,sigma,maturityOfBond,maturityOfOption,sampleSize,callAt90));
  std::vector<double> strikes;
  strikes.push_back(0.99);
  strikes.push_back(0.95);
  strikes.push_back(0.9);

  for(unsigned int i=0; i<res.size(); i++){
    mystream << "At strike " << strikes[i] << "\n";
    mystream << "\t The MC estimated bond option price: " << res[i].mean << "\n";
    mystream << "\t The estimated stdev of the MC: " << res[i].stdev_of_mc_estimate << "\n";
    mystream << "\t The price by the exact formula for reference (based on your implementation of the bond price function): " << 
      BondCallOption(r0,kappa,phi,sigma,maturityOfBond,maturityOfOption,strikes[i]) << "\n";
  }
  mystream<< "\n";
}

double callAt99(double P){
  return P > 0.99 ? P - 0.99 : 0.0;
}

double callAt95(double P){
  return P > 0.95 ? P - 0.95 : 0.0;
}

double callAt90(double P){
  return P > 0.9 ? P - 0.9 : 0.0;
}


#include <cmath>


double BondCallOption(double r0, double kappa, double phi, double sigma, double maturityOfBond, double maturityOfOption, double strike){
  double B = (1/kappa)*(1.0 - exp(-kappa*(maturityOfBond-maturityOfOption)));
  double sigmaP = sigma * sqrt((1.0 - exp(-2.0*kappa*maturityOfOption))/(2.0*kappa)) * B;
  double P1 = bondPrice(r0, 0.0, maturityOfOption, kappa, phi, sigma);
  double P2 = bondPrice(r0, 0.0, maturityOfBond, kappa, phi, sigma);
  double h = (1.0/sigmaP) * log(P2 / (P1*strike)) + sigmaP * 0.5;
  return P2 * normcf(h) - P1 * strike * normcf(h-sigmaP);
}
