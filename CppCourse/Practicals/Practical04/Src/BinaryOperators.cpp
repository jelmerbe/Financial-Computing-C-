//
// Created by Jelmer Bennema on 12/26/23.
//

#include "Practical04/BinaryOperators.hpp"
#include <cmath>
using namespace exercises;

double DF2Yield::operator()(const double dDiscountFactor, const double dTimeToMaturity) const {
    double Yield = -std::log(dDiscountFactor) / (dTimeToMaturity);
    return Yield;
}

double Yield2DF::operator()(const double dYield, const double dTimeToMaturity) const{
    return std::exp(-dTimeToMaturity * dYield);
}

double DF2Libor::operator()(const double dDiscountFactor, const double dTimeToMaturity) const{
    return (1.0/dDiscountFactor - 1.0)/dTimeToMaturity;
}

double Libor2DF::operator()(const double dLibor, const double dTimeToMaturity) const{
    return 1.0/(1.0 + dTimeToMaturity * dLibor);
}


