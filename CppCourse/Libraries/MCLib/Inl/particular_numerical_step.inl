//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.

template<class VF>
typename pmc::num::euler_numerical_step<VF>::path_piece_out &
	pmc::num::euler_numerical_step<VF>::operator()(const mc::dyadic & dyArg,
										  mc::scalar sArg,
										  const typename pmc::num::euler_numerical_step<VF>::path_piece_in & ppiArg,
										  typename pmc::num::euler_numerical_step<VF>::path_piece_out & ppoArgIn)
{

	path_piece_out ppoTempIn(ppoArgIn);
	static path_piece_out ppoTemp;
	size_t n=std::max(vfContainer_.size(),ppiArg.size());
	for(size_t i=0; i<n; ++i)
	{
		vfContainer_[i].operator()(ppoTempIn, ppoTemp);
		ppoArgIn+=ppoTemp*ppiArg[i];
	}
	return ppoArgIn;
}

template<class VF>
typename pmc::num::predictor_corrector_numerical_step<VF>::path_piece_out &
	pmc::num::predictor_corrector_numerical_step<VF>::operator()(const mc::dyadic & dyArg,
		mc::scalar sArg,
		const typename pmc::num::predictor_corrector_numerical_step<VF>::path_piece_in & ppiArg,
		typename pmc::num::predictor_corrector_numerical_step<VF>::path_piece_out & ppoArgIn)
{

	path_piece_out ppoPredictor(ppoArgIn);
	static path_piece_out ppoTemp;
	size_t n=std::max(vfContainer_.size(),ppiArg.size());
	for(size_t i=0; i<n; ++i)
	{
		vfContainer_[i].operator()(ppoArgIn, ppoTemp);
		ppoPredictor+=ppoTemp*ppiArg[i];
	}
	for(size_t i=0; i<n; ++i)
	{
		vfContainer_[i].operator()(ppoPredictor, ppoTemp);
		ppoArgIn+=ppoTemp*ppiArg[i];
	}
	ppoArgIn/=mc::scalar(2);
	ppoArgIn+=ppoPredictor/mc::scalar(2);
	return ppoArgIn;
}

template<class VF>
typename pmc::num::gbm_1d_exact_numerical_step<VF>::path_piece_out &
	pmc::num::gbm_1d_exact_numerical_step<VF>::operator()(const mc::dyadic & dyArg,
		mc::scalar sArg,
		const typename pmc::num::gbm_1d_exact_numerical_step<VF>::path_piece_in & ppiArg,
		typename pmc::num::gbm_1d_exact_numerical_step<VF>::path_piece_out & ppoArgIn)
{

	static path_piece_out ppoUnit(boost::numeric::ublas::unit_vector<mc::scalar>(1));
	static path_piece_out ppoTemp1, ppoTemp2;
	vfContainer_[0].operator()(ppoUnit, ppoTemp1);
	vfContainer_[1].operator()(ppoUnit, ppoTemp2);
	ppoArgIn*=std::exp(ppiArg[0]*(ppoTemp1[0]-ppoTemp2[0]*ppoTemp2[0]/mc::scalar(2))
						+ppiArg[1]*ppoTemp2[0]);
	return ppoArgIn;
}

template<class VF>
typename pmc::num::milstein_1d_numerical_step<VF>::path_piece_out &
	pmc::num::milstein_1d_numerical_step<VF>::operator()(const mc::dyadic & dyArg,
		mc::scalar sArg,
		const typename pmc::num::milstein_1d_numerical_step<VF>::path_piece_in & ppiArg,
		typename pmc::num::milstein_1d_numerical_step<VF>::path_piece_out & ppoArgIn)
{

	path_piece_out ppoTempIn(ppoArgIn);
	static path_piece_out ppoTemp;
	mc::scalar dt(ppiArg[0]);
	mc::scalar dB(ppiArg[1]);
	//V_0
	vfContainer_[0].operator()(ppoTempIn, ppoTemp);
	ppoArgIn+=ppoTemp*dt;
	//V_1
	vfContainer_[1].operator()(ppoTempIn, ppoTemp);
	ppoArgIn+=ppoTemp*dB;
	//correction term
	vfCorrectionTerm_.operator()(ppoTempIn, ppoTemp);
	ppoArgIn+=ppoTemp*(dB*dB-dt)/mc::scalar(2);

	return ppoArgIn;
}

