//************************************************************
//simple_mc_factory implementation
//************************************************************
template<class VO_setup>
typename pmc::simple_mc_factory<VO_setup>::path_in
	pmc::simple_mc_factory<VO_setup>::GetNewPathIn(unsigned int iAccuracyLimit, mc::scalar sT)
{
	path_generator_ptr PathGenPtr(new particular_path_generator(iDim_,iAccuracyLimit,nrgRandomGenerator_));
	return path_in(PathGenPtr,sT);
}

template<class VO_setup>
typename pmc::simple_mc_factory<VO_setup>::path_in_ptr
	pmc::simple_mc_factory<VO_setup>::GetNewPathInPtr(unsigned int iAccuracyLimit, mc::scalar sT)
{
	return path_in_ptr(new path_in(GetNewPathIn(iAccuracyLimit, sT)));
}

template<class VO_setup>
typename pmc::simple_mc_factory<VO_setup>::path_out
		pmc::simple_mc_factory<VO_setup>::GetNewPathOut(unsigned int iAccuracyLimit,
						unsigned int iGlobalAccuracy,
						typename pmc::simple_mc_factory<VO_setup>::path_piece_out ppoArg,
						mc::scalar sT)
{

	if(iGlobalAccuracy>iAccuracyLimit)
		throw mc::error_accuracy_mismatch();
	else
	{
		//setting up input path
		path_in_ptr PathInPtr(GetNewPathInPtr(iAccuracyLimit,sT));

		return GetNewPathOut(PathInPtr,
							iAccuracyLimit,
							iGlobalAccuracy,
							ppoArg,
							sT);
	}
}

template<class VO_setup>
typename pmc::simple_mc_factory<VO_setup>::path_out
		pmc::simple_mc_factory<VO_setup>::GetNewPathOut(
						typename pmc::simple_mc_factory<VO_setup>::path_in_ptr pipArg,
						unsigned int iAccuracyLimit,
						unsigned int iGlobalAccuracy,
						typename pmc::simple_mc_factory<VO_setup>::path_piece_out ppoArg,
						mc::scalar sT)
{

	//if the input path cannot support the accuracy need of the output path, an error is thrown
	if(pipArg->MaxAccuracy()<iAccuracyLimit || iGlobalAccuracy>iAccuracyLimit)
		throw mc::error_accuracy_mismatch();
	else
	{
		//setting up particular numerical_step
		numerical_step_ptr nsNumPtr(new particular_numerical_step(voEquation_));

		//setting up strategy
		strategy_ptr stStratPtr(new particular_strategy(iGlobalAccuracy,iAccuracyLimit));

		//setting up solution_path_generator
		path_generator_out_ptr pgopGen(new solution_path_generator(pipArg,stStratPtr,nsNumPtr));

		// setting up a path_out
		return path_out(pgopGen,sT,ppoArg);
	}
}


//************************************************************
//general_mc_factory implementation
//************************************************************
template<class PPI,
		 class PPO,
		 class PPathGen,
		 class VO_setup,
		 class PNumStep,
		 class PStrategy,
		 class PMO,
		 class PMI>
typename pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::path_in
	pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::
		GetNewPathIn(unsigned int iAccuracyLimit, mc::scalar sT)
{
	path_generator_ptr PathGenPtr(new particular_path_generator(iDim_,iAccuracyLimit,nrgRandomGenerator_));
	return path_in(PathGenPtr,sT);
}

template<class PPI,
		 class PPO,
		 class PPathGen,
		 class VO_setup,
		 class PNumStep,
		 class PStrategy,
		 class PMO,
		 class PMI>
typename pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::path_in_ptr
	pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::
		GetNewPathInPtr(unsigned int iAccuracyLimit, mc::scalar sT)
{
	return path_in_ptr(new path_in(GetNewPathIn(iAccuracyLimit, sT)));
}

template<class PPI,
		 class PPO,
		 class PPathGen,
		 class VO_setup,
		 class PNumStep,
		 class PStrategy,
		 class PMO,
		 class PMI>
typename pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::path_out
		pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::
			GetNewPathOut(unsigned int iAccuracyLimit,
						unsigned int iGlobalAccuracy,
						typename pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::
							path_piece_out ppoArg,
						mc::scalar sT)
{

	if(iGlobalAccuracy>iAccuracyLimit)
		throw mc::error_accuracy_mismatch();
	else
	{
		//setting up input path
		path_in_ptr PathInPtr(GetNewPathInPtr(iAccuracyLimit,sT));

		return GetNewPathOut(PathInPtr,
							iAccuracyLimit,
							iGlobalAccuracy,
							ppoArg,
							sT);
	}
}

template<class PPI,
		 class PPO,
		 class PPathGen,
		 class VO_setup,
		 class PNumStep,
		 class PStrategy,
		 class PMO,
		 class PMI>
typename pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::path_out
		pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::GetNewPathOut(
						typename pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::
							path_in_ptr pipArg,
						unsigned int iAccuracyLimit,
						unsigned int iGlobalAccuracy,
						typename pmc::general_mc_factory<PPI,PPO,PPathGen,VO_setup,PNumStep,PStrategy,PMO,PMI>::
							path_piece_out ppoArg,
						mc::scalar sT)
{

	//if the input path cannot support the accuracy need of the output path, an error is thrown
	if(pipArg->MaxAccuracy()<iAccuracyLimit || iGlobalAccuracy>iAccuracyLimit)
		throw mc::error_accuracy_mismatch();
	else
	{
		//setting up particular numerical_step
		numerical_step_ptr nsNumPtr(new particular_numerical_step(voEquation_));

		//setting up strategy
		strategy_ptr stStratPtr(new particular_strategy(iGlobalAccuracy,iAccuracyLimit));

		//setting up solution_path_generator
		path_generator_out_ptr pgopGen(new solution_path_generator(pipArg,stStratPtr,nsNumPtr));

		// setting up a path_out
		return path_out(pgopGen,sT,ppoArg);
	}
}
