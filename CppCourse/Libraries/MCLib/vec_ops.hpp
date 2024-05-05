//Copyright (c) Lajos Gergely Gyurko, 2023. All rights reserved.
#pragma once

#ifndef _VEC_OP_HPP___
#define _VEC_OP_HPP___

#include <vector>
#include <functional>
#include "MCLib/type_definitions.hpp"


namespace vecop
{
    typedef mc::bvector bvector;
    typedef mc::scalar scalar;
    typedef std::function<mc::scalar(bvector const& arg)> basis_function;
    typedef std::function<void(bvector const&, bvector&)> coefficient_function;
    typedef std::vector<coefficient_function> vec_coefficient_function; //!< Vector of operators, i.e. the type of the equation

/** \fn Vec_ops GeometricBM1D(scalar mu, scalar sigma, Degree maxDegree)
  * \brief Function setting vector fields for the 1D geometric Brownian motion.
  * - dX=mu X dt + sigma X dB
  * @param mu is the drift coefficient
  * @param sigma is the volatility
  */
    vec_coefficient_function GeometricBM1D(scalar mu, scalar sigma);

/** \fn Vec_ops GeometricBMnAverage1D(scalar mu, scalar sigma, Degree maxDegree)
  * \brief Function setting vector fields for the 1D geometric Brownian motion with a time average term.
  * - dX=mu X dt + sigma X dB.
  * - dA=X dt.
  * @param mu is the drift coefficient
  * @parma sigma is the volatility
  */
    vec_coefficient_function GeometricBMnAverage1D(scalar mu, scalar sigma);

/** \fn Vec_ops GeometricBM2D(scalar mu1, scalar sigma1, scalar mu2, scalar sigma2, scalar rho)
  * \brief Function setting vector fields for the 2D geometric Brownian motion with a time average term.
  * - dX1=mu1 X1 dt + sigma1 X1 dB1.
  * - dX2=mu2 X2 dt + sigma2 rho X2 dB1 + sigma2 sqrt(1-rho^2) X2 dB2
  * @param mu1 is the drift coefficient of X1
  * @param mu2 is the drift coefficient of X2
  * @parma sigma1 is the volatility of X1
  * @parma sigma2 is the volatility of X2
  * @parma rho the correlation of the driving Brownian motions
  */
    vec_coefficient_function GeometricBM2D(scalar mu1, scalar sigma1, scalar mu2,
					  scalar sigma2, scalar rho);

/** \fn Vec_ops StochasticCEVVol1D(scalar mu, scalar sigma, scalar a, scalar b, scalar c, scalar rho, Exponenet e)
  * \brief Function setting vector fields for the 2D geometric Brownian motion with a time average term.
  * - dX=mu X dt + sigma sqrt(V) X dB1.
  * - dV=a(b-V)dt + c V^e(rho dB1+sqrt(1-rho^2) dB2)
  * @param mu is the drift coefficient
  * @parma sigma is the volatility
  * @param a is the mean reverting speed of the vol
  * @param b is the mean reverting level of the vol
  * @param c is the volatility parameter of the vol
  * @param rho is the correlation of the driving Brownian motions
  * @param e is the exponent used in the vol of vol
  */
    vec_coefficient_function StochasticCEVVol1D(scalar mu, scalar sigma, scalar a, scalar b,
						   scalar c, scalar rho, scalar e);


/** \fn Vec_ops StochasticCEVVolnAverage1D(scalar mu, scalar sigma, scalar a, scalar b, scalar c, scalar rho, Exponenet e)
  * \brief Function setting vector fields for the 2D geometric Brownian motion with a time average term.
  * - dX=mu X dt + sigma sqrt(V) X dB1.
  * - dA=Xdt.
  * - dV=a(b-V)dt + c V^e(rho dB1+sqrt(1-rho^2) dB2).
  * @param mu is the drift coefficient
  * @parma sigma is the volatility
  * @param a is the mean reverting speed of the vol
  * @param b is the mean reverting level of the vol
  * @param c is the volatility parameter of the vol
  * @param rho is the correlation of the driving Brownian motions
  * @param e is the exponent used in the vol of vol
  */
    vec_coefficient_function StochasticCEVVolnAverage1D(scalar mu, scalar sigma, scalar a, scalar b,
						   scalar c, scalar rho, scalar e);



}

#endif //_VEC_OP_HPP___

