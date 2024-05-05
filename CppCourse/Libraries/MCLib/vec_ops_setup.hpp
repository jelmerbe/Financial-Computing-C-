//Copyright (c) Lajos Gergely Gyurko, 2023. All rights reserved.
#pragma once

#ifndef _VEC_OP_SETUP_HPP___
#define _VEC_OP_SETUP_HPP___


#include "MCLib/vec_ops.hpp"

namespace vecop
{

class equation_setup
{
public:
    typedef vec_coefficient_function Vec_ops;

	virtual ~equation_setup(){};
	virtual vec_coefficient_function operator()()=0;
	unsigned int GetDim() {return iDim_;}

protected:
	unsigned int iDim_;
};


class geometricBM1D_setup : public equation_setup
{
public:

	geometricBM1D_setup(scalar mu, scalar sigma) :
	mu_(mu), sigma_(sigma)  {iDim_=1;}


	vec_coefficient_function operator()(){return GeometricBM1D(mu_, sigma_);}

private:
	scalar mu_;
	scalar sigma_;
};


class geometricBMnAverage1D_setup : public equation_setup
{
public:

	geometricBMnAverage1D_setup(scalar mu, scalar sigma) :
	mu_(mu), sigma_(sigma) {iDim_=1;}

	vec_coefficient_function operator()(){	return GeometricBMnAverage1D(mu_, sigma_);}

private:
	scalar mu_;
	scalar sigma_;
};

class geometricBM2D_setup : public equation_setup
{
public:

	geometricBM2D_setup(scalar mu1, scalar sigma1, scalar mu2, scalar sigma2, scalar rho) :
				mu1_(mu1), sigma1_(sigma1), mu2_(mu2), sigma2_(sigma2), rho_(rho) {iDim_=2;}

	vec_coefficient_function operator()(){	return GeometricBM2D(mu1_, sigma1_, mu2_, sigma2_, rho_);}
private:
	scalar mu1_;
	scalar sigma1_;
	scalar mu2_;
	scalar sigma2_;
	scalar rho_;
};


class stochasticCEVVol1D_setup : public equation_setup
{
public:

	stochasticCEVVol1D_setup(scalar mu, scalar sigma, scalar a, scalar b, scalar c, scalar rho,
							scalar e) :
				mu_(mu), sigma_(sigma), a_(a), b_(b), c_(c), rho_(rho), e_(e){iDim_=2;}

	vec_coefficient_function operator()(){return StochasticCEVVol1D(mu_, sigma_, a_, b_, c_, rho_, e_);}
private:
	scalar mu_;
	scalar sigma_;
	scalar a_;
	scalar b_;
	scalar c_;
	scalar rho_;
	scalar e_;
};


class stochasticCEVVolnAverage1D_setup : public equation_setup
{
public:

	stochasticCEVVolnAverage1D_setup(scalar mu, scalar sigma, scalar a, scalar b, scalar c, scalar rho,
							scalar e) :
				mu_(mu), sigma_(sigma), a_(a), b_(b), c_(c), rho_(rho), e_(e) {iDim_=2;}

	vec_coefficient_function operator()(){	return StochasticCEVVolnAverage1D(mu_, sigma_, a_,
                                                                                b_, c_, rho_, e_);}
private:
	scalar mu_;
	scalar sigma_;
	scalar a_;
	scalar b_;
	scalar c_;
	scalar rho_;
	scalar e_;
};

}
#endif //_VEC_OP_SETUP_HPP___
