
//**************************************************************
//**************************************************************
// Implementations
//**************************************************************
//**************************************************************

//**************************************************************
// Members of european_option_pricer
//**************************************************************
template<typename PPI,typename F>
pmc::european_option_pricer<PPI,F>::european_option_pricer(const std::vector<path_piece_out> & factorsAt0,
											unsigned int iAccuracy,
											mc::scalar sT,
											mc::scalar sR,
											factory & ParticularFactory,
											payoff & ParticularPayoff,
											const fvector & testFunctions)
											: m_TestFunctions(testFunctions)
{
	typename std::vector<path_piece_out>::size_type n(factorsAt0.size());
	std::vector<mc::bvector> yVals(n);
	for(unsigned int i=0; i<n; ++i)
	{
		path_out Path=ParticularFactory.GetNewPathOut(iAccuracy,0,factorsAt0[i],sT);
		ParticularPayoff(Path,yVals[i])*=std::exp(-sR*sT);
	}
	m_Coefficients=this->Regression(yVals,factorsAt0,m_TestFunctions);
}


template<typename PPI, typename F>
mc::bvector & pmc::european_option_pricer<PPI,F>::operator()(const path_piece_out & factorAt0, mc::bvector & bvOut)
{
	return this->Projection(factorAt0,m_TestFunctions,m_Coefficients,bvOut);
}


//**************************************************************
// Members of bermudan_option_pricer
//**************************************************************
template<typename PPI, typename F>
pmc::bermudan_option_pricer<PPI,F>
::bermudan_option_pricer(const std::vector<path_piece_out> & factorsAt0,
			 unsigned int iNumericalSDEAccuracy,
			 unsigned int iBermudanScaleAccuracy,
			 mc::scalar sT,
			 mc::scalar sR,
			 factory & ParticularFactory,
			 time_dependent_payoff & ParticularTimedependentPayoff,
			 const fvector & testFunctions)
  : m_TestFunctions(testFunctions)
{
  typename std::vector<path_piece_out>::size_type n(factorsAt0.size());
	
	//simulating trajectories and discounted terminal value
  std::vector<path_out> trajectories;
  trajectories.reserve(n);
  std::vector<mc::bvector> yVals(n);
  mc::dyadic dyTime((1<<iBermudanScaleAccuracy)-1,iBermudanScaleAccuracy);//[(2^M-1)*2^(-M),1]
  for(unsigned int i=0; i<n; ++i){
		//path_out pathTemp=ParticularFactory.GetNewPathOut(iNumericalSDEAccuracy,iBermudanScaleAccuracy,factorsAt0[i],sT);
    trajectories.push_back(ParticularFactory.GetNewPathOut(iNumericalSDEAccuracy,
							   iBermudanScaleAccuracy,
							   factorsAt0[i],
							   sT));
    ParticularTimedependentPayoff(trajectories.back(),dyTime,yVals[i]) *= 
      std::exp(-sR*sT);
  }
	//backward induction
  std::vector<path_piece_out> factorsAtT(n);
  mc::bvector tempExercise(ParticularTimedependentPayoff.SizePayoff());
  mc::bvector tempContinuation(ParticularTimedependentPayoff.SizePayoff());

  auto maxOp =
        [](mc::scalar x, mc::scalar y){return std::max<mc::scalar>(x,y);};

  --dyTime;
  for(int j=0; j < (1<<iBermudanScaleAccuracy)-1 ; ++j, --dyTime ){
		// accessing factor values at time dyTime
    for(unsigned int i=0; i<n; ++i)
      factorsAtT[i]=trajectories[i].find(dyTime)->second;
		
		// regression for continuation value
    m_Coefficients=this->Regression(yVals,factorsAtT,m_TestFunctions);

    // dynamic programming principle for value
   // working out new values comparing continuation and exercise values
    for(unsigned int i=0; i<n; ++i){
      // continuation value
      this->Projection(factorsAtT[i],m_TestFunctions,m_Coefficients,tempContinuation);
      // exercise value
      mc::scalar sTTemp=dyTime.GetLength()*mc::scalar(dyTime.Position()+1)*sT;

      ParticularTimedependentPayoff(trajectories[i],dyTime,tempExercise) *= 
	std::exp(-sR*sTTemp);
      //new values
      std::transform(tempExercise.begin(),tempExercise.end(),
		     tempContinuation.begin(),yVals[i].begin(), maxOp);
    }
  }
  // last step - regression at time 0 (no payoff assumed at initial time)
  m_Coefficients=this->Regression(yVals,factorsAt0,m_TestFunctions);
}

template<typename PPI, typename F>
mc::bvector & pmc::bermudan_option_pricer<PPI,F>
::operator()(const path_piece_out & factorAt0, mc::bvector & bvOut)
{
  return this->Projection(factorAt0,m_TestFunctions,m_Coefficients,bvOut);
}



