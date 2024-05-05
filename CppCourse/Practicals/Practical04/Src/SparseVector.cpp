#include "Practical04/SparseVector.hpp"

using namespace exercises;
using namespace std;

std::ostream & exercises::operator<<(std::ostream & os, const SparseVector & svArg)
{
	os << "{"; 
	SparseVector::const_iterator svIter=svArg.begin();
	SparseVector::const_iterator sveIter=svArg.end();
	for(;svIter!=sveIter; ++svIter) 
		os << "[" << svIter->first << "] " << svIter->second << "  ";

	os<< "}";

	return os;
}

SparseVector & exercises::operator+=(SparseVector & svArg1, 
					const SparseVector & svArg2)
{
	auto sv2Iter=svArg2.begin();
	auto sv2eIter=svArg2.end();

	for( ;sv2Iter!=sv2eIter; ++sv2Iter) 
	{
		auto sv1Iter=svArg1.find(sv2Iter->first);
		//alternative code for line 26:
		//SparseVector::iterator sv1Iter=svArg1.find((*sv2Iter).first);
		
		//checking if entry does not exist
		if(sv1Iter==svArg1.end() && (sv2Iter->second)!=0.0)
			svArg1.insert(*sv2Iter);
		//alternative code for line 32:
		//svArg1.insert(std::make_pair(sv2Iter->first,sv2Iter->second));
		else if(sv1Iter!=svArg1.end()) //if entry exist, then update
		{
			sv1Iter->second+=sv2Iter->second;
			if(sv1Iter->second==0.0) //if entry becomes zero, then remove
				svArg1.erase(sv1Iter);
		}
	}
	//return reference to first argument
	return svArg1;
}



SparseVector exercises::operator+(const SparseVector & svArg1, 
			const SparseVector & svArg2)
{
	SparseVector res;

    // add elements from the first vector
    auto Iter1 = svArg1.begin();
    auto Iter1e =svArg1.end();

    for (; Iter1 != Iter1e; Iter1++){
        res.insert(std::make_pair(Iter1->first,Iter1->second));
    }

    // add elements from the second vector
    auto Iter2 = svArg2.begin();
    auto Iter2e =svArg2.end();

    for (; Iter2 != Iter2e; Iter2++){

        auto Ires = res.find(Iter2 -> first);

        // if entry does not exist (and vector 2 has non zero element)
        if (Ires == res.end() &&  Iter2 -> second != 0.0) {
            res.insert(std::make_pair(Iter2->first, Iter2->second));
        }

        // if entry already exists
        else if(Ires != res.end())
        {
            Ires->second += Iter2->second;

            if(Ires->second==0.0) //if entry becomes zero, then remove
                res.erase(Ires);
        }
    }
	return res;
}

SparseVector & exercises::operator-=(SparseVector & svArg1, const SparseVector & svArg2)
{
    auto sv2Iter=svArg2.begin();

    for( ;sv2Iter!=svArg2.end(); ++sv2Iter)
    {
        auto sv1Iter=svArg1.find(sv2Iter->first);

        //checking if entry does not exist
        if(sv1Iter==svArg1.end() && (sv2Iter->second)!=0.0)
            svArg1.insert(std::make_pair(sv2Iter->first,-(sv2Iter->second)));

        else if(sv1Iter!=svArg1.end()) //if entry exist, then update
        {
            sv1Iter->second-=sv2Iter->second;
            if(sv1Iter->second==0.0) //if entry becomes zero, then remove
                svArg1.erase(sv1Iter);
        }
    }
    //return reference to first argument
    return svArg1;
}


SparseVector exercises::operator-(const SparseVector & svArg1, const SparseVector & svArg2)
{
	SparseVector res;

    // add first vector
    auto sv1Iter = svArg1.begin();

    for (;sv1Iter != svArg1.end(); sv1Iter++){
        res.insert(std::make_pair(sv1Iter -> first, sv1Iter -> second));
    }

    // subtract second vector
    auto sv2Iter = svArg2.begin();

    for(; sv2Iter != svArg2.end(); sv2Iter++ ){

        auto Ires = res.find(sv2Iter -> first);

        // does not exist yet
        if (Ires == res.end()) {
            res.insert(std::make_pair(sv2Iter->first, (-1) * sv2Iter->second));
        }

        // already exists
        else if (Ires != res.end() && sv2Iter -> second != 0.0){
            Ires -> second -= sv2Iter -> second;

            // if entry becomes zero, delete
            if (Ires -> second == 0.0){
                res.erase(Ires -> first);
            }
        }
    }

	return res;
}


SparseVector & exercises::operator*=(SparseVector & svArg, const double dArg)
{
	auto svIter = svArg.begin();

    for (;svIter != svArg.end();){
        svIter -> second *= dArg;

        // check if zero
        if (svIter -> second == 0.0){
            svIter = svArg.erase(svIter);
        }
        else {svIter++; }
    }

	return svArg;
}

SparseVector exercises::operator*(const SparseVector & svArg, const double dArg)
{
	SparseVector res;

    auto svIter = svArg.begin();

    for (;svIter != svArg.end(); svIter++) {

        auto result = res.insert(std::make_pair(svIter -> first, svIter -> second * dArg));

        // check if zero
        if (result.first -> second  == 0.0){
            result.first = res.erase(result.first);
        }
    }

	return res;
}

SparseVector exercises::operator*(const double dArg, const SparseVector & svArg)
{
    SparseVector res;

    auto svIter = svArg.begin();

    for (;svIter != svArg.end(); svIter++) {
        auto Ires = res.find(svIter -> first);

        Ires -> second = svIter -> second * dArg;

        // check if zero
        if (Ires -> second == 0.0){
            res.erase(Ires);
        }
    }

    return res;
}


