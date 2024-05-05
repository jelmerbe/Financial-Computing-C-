//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.


template<class PPI, class PPO, class PMO, class PMI>
typename pmc::strat::equal_step_strategy<PPI,PPO,PMO,PMI>::const_iterator
pmc::strat::equal_step_strategy<PPI,PPO,PMO,PMI>::operator()(typename pmc::strat::equal_step_strategy<PPI,PPO,PMO,PMI>::numerical_step & nsArg,
				typename  pmc::strat::equal_step_strategy<PPI,PPO,PMO,PMI>::path_in & piArg,
				const mc::dyadic & dyArg,
				mc::scalar sArg,
				typename pmc::strat::equal_step_strategy<PPI,PPO,PMO,PMI>::path_map_out & pmArg,
				const typename pmc::strat::equal_step_strategy<PPI,PPO,PMO,PMI>::path_piece_out & ppoArg)
{
	//This strategy does not store increments but value at time t, generated at
	//a given fine scale (determined by iLocalAccuracy_)
	// time t is passed as the right end of a dyadic.
	mc::dyadic dyTemp;
	if(dyArg.Accuracy()<iGlobalAccuracy_)
		dyTemp=dyArg.IncreaseAccuracyRight(iGlobalAccuracy_-dyArg.Accuracy());
	else
		dyTemp=dyArg;

	const_iterator pmIter=pmArg.find(dyTemp);
	const_iterator eIter=pmArg.end();

	if(pmIter!=eIter)
		return pmIter;
	else if(dyArg.Accuracy()>iGlobalAccuracy_)// does not return elements on scale finer than iGlobalAccuracy
		return eIter;
	else
	{	//dyArg hasn't been found in the map.
		//look up (generate) the previous element and take a num step

		// initial condition (previous element)
		path_piece_out ppoTemp;
		mc::dyadic dyTempM(dyTemp-1);
		if(dyTemp==dyTempM) //if dyTemp is the left most
			ppoTemp=ppoArg; //us the global initial condition
		else
			ppoTemp=this->operator ()( nsArg,
										piArg,
										dyTempM,
										sArg,
										pmArg,
										ppoArg)->second;//otherwise call op() recursively on the precious dyad



		//defining dyadics for local steps
		unsigned int iAccuracySur=iLocalStepAccuracy_-dyTemp.Accuracy();
		mc::dyadic dyStep=dyTemp.IncreaseAccuracyLeft(iAccuracySur);
		//then take the local steps
		unsigned int iTwoToiAccuracy=(1<<iAccuracySur);
		for(unsigned int i=0; i<iTwoToiAccuracy; ++i, ++dyStep)
		{
			//generating input path piece
			typename path_in::const_iterator piIter=piArg.find(dyStep);
			//checking if the generation was successful
			if(piIter==piArg.end())
				return pmArg.end(); //returns end if not successful
			else
				nsArg(dyStep, sArg, piIter->second,ppoTemp);//otherwise takes a local step

		}
		std::pair<const_iterator,bool> insertPair=pmArg.insert(std::make_pair(dyArg,ppoTemp));
		return insertPair.first;
	}
}

