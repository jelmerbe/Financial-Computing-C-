//
// Created by Jelmer Bennema on 12/22/23.
//

#include "Practical02/ComplexNumber.hpp"

// implement constructor(s)
ComplexNumber::ComplexNumber() : dIm_(0.0), dRe_(0.0) {}
ComplexNumber::ComplexNumber(double dReArg, double dImArg) :  dRe_(dReArg), dIm_(dImArg){}

// implement member functions
/* this ** always points to the instance of the class the member function is working on */

ComplexNumber & ComplexNumber::operator+=(const ComplexNumber & cnArg){
    dIm_ += cnArg.dIm_;
    dRe_ += cnArg.dRe_;
    return *this;
}

ComplexNumber & ComplexNumber::operator-=(const ComplexNumber & cnArg){
    dIm_ -= cnArg.dIm_;
    dRe_ -= cnArg.dRe_;
    return *this;
}
ComplexNumber & ComplexNumber::operator*=(const ComplexNumber & cnArg){
    dRe_ = cnArg.dRe_ * cnArg.dRe_ - cnArg.dIm_ * cnArg.dIm_;
    dRe_ = cnArg.dRe_ * cnArg.dIm_ + cnArg.dRe_ * cnArg.dIm_;
    return *this;
}
ComplexNumber & ComplexNumber::operator/=(const ComplexNumber & cnArg){
    operator*=(ComplexNumber(cnArg.dRe_,-1.0*cnArg.dIm_));
    operator/=(cnArg.dRe_*cnArg.dRe_+cnArg.dIm_*cnArg.dIm_);
    return *this;
}

ComplexNumber & ComplexNumber::operator+=(const double & Arg){
    dRe_ += Arg;
    return *this;
}
ComplexNumber & ComplexNumber::operator-=(const double & Arg){
    dRe_ -= Arg;
    return *this;
}
ComplexNumber & ComplexNumber::operator*=(const double & Arg){
    dRe_ *= Arg;
    dIm_ *= Arg;
    return *this;
}
ComplexNumber & ComplexNumber::operator/=(const double & Arg){
    dRe_ /= Arg;
    dIm_ /= Arg;
    return *this;
}

// implement print function to support ostream operator
std::ostream & ComplexNumber::print(std::ostream & os) const{
    return os << "(" << dRe_ << ", " << dIm_ << "i)";
}

// implement ostream operator

std::ostream & operator<<(std::ostream & os, const ComplexNumber & cnArg){
    return cnArg.print(os);
}


// implement non-members functions (based on member functions)

ComplexNumber operator+(const ComplexNumber & Arg1,const ComplexNumber & Arg2){
    ComplexNumber Res(Arg1);
    return Res+=Arg2;
}

ComplexNumber operator-(const ComplexNumber & Arg1,const ComplexNumber & Arg2){
    ComplexNumber Res(Arg1);
    return Res-=Arg2;
}

ComplexNumber operator*(const ComplexNumber & Arg1,const ComplexNumber & Arg2){
    ComplexNumber Res(Arg1);
    return Res*=Arg2;
}

ComplexNumber operator/(const ComplexNumber & Arg1,const ComplexNumber & Arg2){
    ComplexNumber Res(Arg1);
    return Res/=Arg2;
}

ComplexNumber operator+(const ComplexNumber & Arg1,const double & Arg2){
    ComplexNumber Res(Arg1);
    return Res+=Arg2;
}

ComplexNumber operator-(const ComplexNumber & Arg1,const double & Arg2){
    ComplexNumber Res(Arg1);
    return Res-=Arg2;
}

ComplexNumber operator*(const ComplexNumber & Arg1,const double & Arg2){
    ComplexNumber Res(Arg1);
    return Res*=Arg2;
}

ComplexNumber operator/(const ComplexNumber & Arg1,const double & Arg2){
    ComplexNumber Res(Arg1);
    return Res/=Arg2;
}

ComplexNumber operator+(const double & Arg1,const ComplexNumber & Arg2){
    ComplexNumber Res(Arg2);
    return Res+=Arg1;
}

ComplexNumber operator-(const double & Arg1,const ComplexNumber & Arg2){
    ComplexNumber Res(Arg1);
    return Res-=Arg2;
}

ComplexNumber operator*(const double & Arg1,const ComplexNumber & Arg2){
    ComplexNumber Res(Arg2);
    return Res*=Arg1;
}

ComplexNumber operator/(const double & Arg1,const ComplexNumber & Arg2){
    ComplexNumber Res(Arg1);
    return Res/=Arg2;
}



