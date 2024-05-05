//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.

#ifdef MSC_VER
#pragma warning(disable:4996)
#endif 

#include <algorithm>
#include <functional>
#include <utility>
#include <cmath>


template<class RndGen>
typename pmc::bottom_up_generator<RndGen>::const_iterator pmc::bottom_up_generator<RndGen>::operator ()
	(const mc::dyadic & dyArg, path_map & pmArg, mc::scalar sArg, const path_piece & ppArg)
{
	//typedef typename path_map::key_type key_type;
	//typedef typename path_map::value_type value_type;

	path_map::const_iterator pmIter=pmArg.find(dyArg);

	if(pmIter!=pmArg.end())
	{//If already in the container, return it.
		return pmIter;
	}
	else if(dyArg.Accuracy()==iAccuracy_)
	{// If dyArg is at the finest level, generate an increment (independent from every other increment)

		mc::bvector bvec(iDim_+1);//create a vector of length iDim_+1
		mc::bvector::iterator Iter=bvec.begin();
		mc::bvector::iterator eIter=bvec.end();
		*Iter=sArg*dyArg.GetLength();//setting first entry to step length
		++Iter;
		rgRand_->operator()(Iter,eIter);//setting the rest of the entries to independent standard normals
		mc::scalar sArgSqrt=std::sqrt(sArg*dyArg.GetLength());
		std::transform(Iter,eIter,Iter,[sArgSqrt](double x){return x * sArgSqrt;}); //scaling

		std::pair<path_map::const_iterator,bool> insertPair=pmArg.insert(std::make_pair(dyArg,bvec));
		return insertPair.first;
	}
	else if(dyArg.Accuracy()<iAccuracy_)
	{// If dyArg is not at the finest level, call this function recursively

		mc::bvector bvec(operator()(dyArg.SmallLeft(), pmArg, sArg, ppArg)->second
							+ operator()(dyArg.SmallRight(), pmArg, sArg, ppArg)->second);

		std::pair<path_map::const_iterator,bool> insertPair=pmArg.insert(std::make_pair(dyArg,bvec));
		return insertPair.first;
	}
	else
	{// If increment is required on a scale finer than allowed, an error is thrown.
		return pmArg.end();
	}

}

template<class RndGen>
typename pmc::brownian_bridge_generator<RndGen>::const_iterator
	pmc::brownian_bridge_generator<RndGen>::operator ()
	(const mc::dyadic & dyArg, path_map & pmArg, mc::scalar sArg, const path_piece & ppArg)
{
	//typedef typename path_map::key_type key_type;
	//typedef typename path_map::value_type value_type;

	path_map::const_iterator pmIter=pmArg.find(dyArg);

	if(pmIter!=pmArg.end())
	{//If already in the container, return it.
		return pmIter;
	}

	//if not yet generated, check if it's at top level
	if(dyArg.Accuracy()==0)
	{
		mc::bvector bvec(iDim_+1);//create a vector of length iDim_+1
		mc::bvector::iterator Iter=bvec.begin();
		mc::bvector::iterator eIter=bvec.end();
		*Iter=sArg;//setting first entry to step length
		++Iter;
		rgRand_->operator()(Iter,eIter);//setting the rest of the entries to independent standard normals
		mc::scalar sArgSqrt(std::sqrt(sArg));
		std::transform(Iter,eIter,Iter,[sArgSqrt](double x){return x * sArgSqrt;}); //scaling

		std::pair<path_map::const_iterator,bool> insertPair=pmArg.insert(std::make_pair(dyArg,bvec));
		return insertPair.first;
	}
	else
	{
		//if not top level, step up, and use the coarse scale increment for
		//Brownian bridge generation

		//This function is called (recursively) to get the increment one level up
		const mc::bvector & bvBigInc(operator()(dyArg.BigLeft(), pmArg, sArg, ppArg)->second);

		//Now the condition is given. Let's construct the Brownian bridge.
		//Both the left and the right parts are constructed

		//generating the independent part
		mc::bvector bvec(iDim_+1);//create a vector of length iDim_+1
		mc::bvector::iterator Iter=bvec.begin();
		mc::bvector::iterator eIter=bvec.end();
		*Iter=mc::scalar(0);//setting first entry to step length
		++Iter;
		rgRand_->operator()(Iter,eIter);//setting the rest of the entries to independent standard normals
		mc::scalar sArgSqrt(std::sqrt(sArg*dyArg.GetHalfLength()));
		std::transform(Iter,eIter,Iter,[sArgSqrt](double x){return x * sArgSqrt;}); //scaling


		mc::dyadic dyLeft(dyArg), dyRight(dyArg);
		if(dyArg.IsLeft())
			++dyRight;
		else
			--dyLeft;
		mc::bvector bvIncLeft(bvec+bvBigInc/mc::scalar(2));
		mc::bvector bvIncRight(bvBigInc/mc::scalar(2)-bvec);

		std::pair<path_map::const_iterator,bool> insertPairLeft=
			pmArg.insert(std::make_pair(dyLeft,bvIncLeft));
		std::pair<path_map::const_iterator,bool> insertPairRight=
			pmArg.insert(std::make_pair(dyRight,bvIncRight));

		if(dyArg==dyLeft)
			return insertPairLeft.first;
		else
			return insertPairRight.first;
	}
}

