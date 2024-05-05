//Copyright (c) Lajos Gergely Gyurko, 2009. All rights reserved.
#ifndef _PARTICULAR_QUANTILE_STATISTICS_H__
#define _PARTICULAR_QUANTILE_STATISTICS_H__

namespace pmc
{


/** \class quantile_statistics
	\brief quantile_statistics is a particular class derived from statistics

	quantile_statistics computes running mean and variance
*/
template<bool Val>
class quantile_statistics : public mc::statistics
{
public:
	typedef std::multiset<mc::scalar> tail_container;//!<ordered container of values
	typedef std::vector<tail_container > vector_of_tail_containers;//!<vector of tails per factor component

	/** constructor
	  */
	quantile_statistics(unsigned int iNoElemStored) 
		: iCurrentNoSim_(0), iNoElemStored_(iNoElemStored)
	{}

	/** DumpOnePayoff()
	* @param bvArg the computed payoff is taken and statistics is updated
	  */
	void DumpOnePayoff(mc::bvector & bvArg);

	/** GetResults()
	  * @return the statistics computed so far
	 */
	std::vector<mc::bvector> GetStatistics();

private: 
	/** TestValue
	* @param 
	* @param
	* @return
	*/
	bool testValue(unsigned int, mc::scalar);

	/** getPosition
	* @param ind
	* @return
	*/
	tail_container::iterator getPosition(unsigned int ind); 

private:
	unsigned int iCurrentNoSim_;//!< keeps record of the number of paths simulated so far
	unsigned int iNoElemStored_;//!< number of elements stored
	vector_of_tail_containers vecTails_;//!<keeps record of the tails
	mc::bvector bvQuantiles_;//!<quantiles
};







//********************************************************************
// quantile_statistics implementation
//********************************************************************
template<bool Val>
void pmc::quantile_statistics<Val>::DumpOnePayoff(mc::bvector & bvArg)
{
	++iCurrentNoSim_;
	static unsigned int n=bvArg.size();
	if(iCurrentNoSim_==1)
	{
		//set up vecTails_;
		bvQuantiles_.resize(n);
		vecTails_.resize(n);
		mc::bvector::const_iterator iter=bvArg.begin();
		for(unsigned int i=0; i<n; ++i, ++iter)
		{
			tail_container tail;
			tail.insert(*iter);
			vecTails_[i]=tail;
			bvQuantiles_[i]=*iter;
		}
	}
	else if(iCurrentNoSim_<iNoElemStored_)
	{
		//insert elements into the tail conatiners
		mc::bvector::const_iterator iter=bvArg.begin();
		vector_of_tail_containers::iterator votIter=vecTails_.begin();
		for(unsigned int i=0; i<n; ++i, ++votIter)
		{
			(*votIter).insert(*iter);
			if(testValue(i,*iter))
			{
				bvQuantiles_[i]=*(getPosition(i));
			}
		}
	}
	else
	{
		//insert only if belongs to tail
		mc::bvector::const_iterator iter=bvArg.begin();
		vector_of_tail_containers::iterator votIter=vecTails_.begin();
		for(unsigned int i=0; i<n; ++i, ++iter, ++votIter)
		{
			if(testValue(i,*iter))
			{
				(*votIter).insert(*iter);
				(*votIter).erase(getPosition(i));
				bvQuantiles_[i]=*(getPosition(i));
			}
		}
	}
}

template<>
bool pmc::quantile_statistics<true>::testValue(unsigned int ind, mc::scalar sArg)
{
	return bvQuantiles_[ind]>sArg;
}

template<>
bool pmc::quantile_statistics<false>::testValue(unsigned int ind, mc::scalar sArg)
{
	return bvQuantiles_[ind]<sArg;
}

template<>
pmc::quantile_statistics<true>::tail_container::iterator pmc::quantile_statistics<true>::getPosition(unsigned int ind)
{
	return (--(vecTails_[ind]).end());		
}

template<>
pmc::quantile_statistics<false>::tail_container::iterator pmc::quantile_statistics<false>::getPosition(unsigned int ind)
{
	return (vecTails_[ind]).begin();		
}

template<bool Val>
std::vector<mc::bvector> pmc::quantile_statistics<Val>::GetStatistics()
{
	
	std::vector<mc::bvector> vRes;
	vRes.push_back(bvQuantiles_);
	return vRes;
}

}

#endif //_PARTICULAR_QUANTILE_STATISTICS_H__