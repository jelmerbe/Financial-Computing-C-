//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PARTICULAR_NUMERICAL_STEP_H__
#define _PARTICULAR_NUMERICAL_STEP_H__

#include "MCLib/type_definitions.hpp"
#include "MCLib/base_schemes.hpp"
#include <cmath>

namespace pmc
{

namespace num //! namespace holding particular numerical_step classes
{

/** \class euler_numerical_step
	\brief euler_numerical_step is a particular numerical step

	euler_numerical_step is built around a container of vector fields. It is assumed
	that the container supports operator[].
*/
template<class VF>
class euler_numerical_step : public pmc::numerical_step<mc::bvector, mc::bvector>
{
public:
	typedef VF vector_fields;//!<container of vector fields/coefficient functions

	/** constructor
	* @param vfArg sets the container of the vector fields
	*/
	euler_numerical_step(const vector_fields & vfArg) : vfContainer_(vfArg){};

	/** operator() - takes one numerical step
	* @param dyArg dyadic interval, step taken on
	* @param sArg scaling factor
	* @param ppiArg input noise
	* @param ppoArgIn initial condition, the result also will be written into this
	* @return reference to oppArgIn
	*/
	path_piece_out & operator()(const mc::dyadic & dyArg,
						mc::scalar sArg,
						const path_piece_in & ppiArg,
						path_piece_out & ppoArgIn);

private:
	vector_fields vfContainer_;//!< container holding the vector field defining the Ito SDE

};

/** \class predictor_corrector_numerical_step
	\brief predictor_corrector_numerical_step is a particular numerical step

	predictor_corrector_numerical_step is built around a container of vector fields. It is assumed
	that the container supports operator[]. Stratonovich SDE assumed
*/
template<class VF>
class predictor_corrector_numerical_step : public pmc::numerical_step<mc::bvector, mc::bvector>
{
public:
	typedef VF vector_fields;//!<container of vector fields/coefficient functions

	/** constructor
	* @param vfArg sets the container of the vector fields
	*/
	predictor_corrector_numerical_step(const vector_fields & vfArg) : vfContainer_(vfArg){};

	/** operator() - takes one numerical step
	* @param dyArg dyadic interval, step taken on
	* @param sArg scaling factor
	* @param ppiArg input noise
	* @param ppoArgIn initial condition, the result also will be written into this
	* @return reference to oppArgIn
	*/
	path_piece_out & operator()(const mc::dyadic & dyArg,
						mc::scalar sArg,
						const path_piece_in & ppiArg,
						path_piece_out & ppoArgIn);

private:
	vector_fields vfContainer_;//!< container holding the vector field defining the Ito SDE

};

/** \class gbm_1d_exact_numerical_step
	\brief gbm_1d_exact_numerical_step is a particular numerical step

	gbm_1d_exact_numerical_step is built around a container of vector fields. It is assumed
	that the container supports operator[]. Two 1d linear vector fields assumed V_0 and V_1. 
*/
template<class VF>
class gbm_1d_exact_numerical_step : public pmc::numerical_step<mc::bvector, mc::bvector>
{
public:
	typedef VF vector_fields;//!<container of vector fields/ coefficient functions

	/** constructor
	* @param vfArg sets the container of the vector fields
	*/
	gbm_1d_exact_numerical_step(const vector_fields & vfArg) : vfContainer_(vfArg){};

	/** operator() - takes one numerical step
	* @param dyArg dyadic interval, step taken on
	* @param sArg scaling factor
	* @param ppiArg input noise
	* @param ppoArgIn initial condition, the result also will be written into this
	* @return reference to oppArgIn
	*/
	path_piece_out & operator()(const mc::dyadic & dyArg,
						mc::scalar sArg,
						const path_piece_in & ppiArg,
						path_piece_out & ppoArgIn);

private:
	vector_fields vfContainer_;//!< container holding the vector field defining the Ito SDE

};

/** \class milstein_1d_numerical_step
	\brief milstein_1d_numerical_step is a particular numerical step

	milstein_1d_numerical_step is built around a container of vector fields. It is assumed
	that the container supports operator[], operator* and TruncateByLength() (e.g. DOPlib differential
	operators satisfies these.)
	Two vector fields V_0 and V_1 assumed.
*/
template<class VF>
class milstein_1d_numerical_step : public pmc::numerical_step<mc::bvector, mc::bvector>
{
public:
	typedef VF vector_fields;//!<container of vector fields/coefficient functions
	typedef typename vector_fields::value_type vf_value_type;//!<vector field type

	/** constructor
	* @param vfArg sets the container of the vector fields
	*/
	milstein_1d_numerical_step(const vector_fields & vfArg) : vfContainer_(vfArg)
		, vfCorrectionTerm_((vfContainer_[1]*vfContainer_[1]).TruncateByLength(size_t(1)))
	{}

	/** operator() - takes one numerical step
	* @param dyArg dyadic interval, step taken on
	* @param sArg scaling factor
	* @param ppiArg input noise
	* @param ppoArgIn initial condition, the result also will be written into this
	* @return reference to oppArgIn
	*/
	path_piece_out & operator()(const mc::dyadic & dyArg,
						mc::scalar sArg,
						const path_piece_in & ppiArg,
						path_piece_out & ppoArgIn);

private:
	vector_fields vfContainer_;//!< container holding the vector field defining the Ito SDE
	vf_value_type vfCorrectionTerm_;//!<correction term
};




}
}

#include "MCLib/Inl/particular_numerical_step.inl"

#endif //_PARTICULAR_NUMERICAL_STEP_H__
