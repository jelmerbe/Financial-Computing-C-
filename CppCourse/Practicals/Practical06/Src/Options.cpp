//
// Created by Jelmer Bennema on 11/22/23.
//

#include "Practical06/Practical06Exercises.hpp"
#include <algorithm> // for max_element
#include <numeric> // for accumulate
#include "Practical06/Function.hpp"

using namespace exercises;
using namespace std;

/** SpreadOption spread option  payoff
  * @param dK1 defines the strike of the first call
  * @param dW1 defines weight of the first call
  * @param dK2 defines the strike of the second call
  * @param dW2 defines weight of the second call
  * @param index defines the index of the relevant underlying
  * @return Function, such that its operator()(bvArg) returns dW1*max(0.0,bvArg[index]-dK1)+dW2*max(0.0,bvArg[index]-dK2);
  */

class ISpreadOption : public IFunction
{
public:
    ISpreadOption(double dK1, double dW1, double dK2, double dW2, BVector::size_type index)
            :   dK1_(dK1), dW1_(dW1), dK2_(dK2), dW2_(dW2), index_(index) {}

    double operator()(const BVector &bvArg) const  {

        double payoff = dW1_*max(bvArg[index_]-dK1_,0.0)+dW2_*max(bvArg[index_]-dK2_,0.0);

        return payoff;
    }

private:
    double dK1_;
    double dW1_;
    double dK2_;
    double dW2_;
    BVector::size_type index_;
};


Function exercises::SpreadOption(double dK1, double dW1, double dK2, double dW2, BVector::size_type index) {

    return Function(make_shared<ISpreadOption>(dK1, dW1, dK2, dW2, index));
}


/** StraddleOption straddle option  payoff
  * @param dK1 defines the strike of the call
  * @param dW1 defines weight of the call
  * @param dK2 defines the strike of the put
  * @param dW2 defines weight of the put
  * @param index defines the index of the relevant underlying
  * @return Function, such that its operator()(bvArg) returns dW1*max(0.0,bvArg[index]-dK1)+dW2*max(0.0,dK2-bvArg[index]);
  */

class IStraddleOption : public IFunction {
public:
    //constructor (order matters...)
    IStraddleOption(double dK1, double dW1, double dK2, double dW2, BVector::size_type index)
    : _dK1(dK1), _dW1(dW1), _dK2(dK2), _dW2(dW2), _index(index)  {}

    //operator
    double operator()(const BVector &bvArg) const {
        double payoff =  _dW1*max(bvArg[_index]-_dK1,0.0)+_dW2*max(_dK2-bvArg[_index],0.0);
        return payoff;
    };

private:
    double _dW1; double _dW2;
    double _dK1; double _dK2;
    BVector::size_type _index;

};

Function exercises::StraddleOption(double dK1, double dW1, double dK2, double dW2, BVector::size_type index) {

    return Function(make_shared<IStraddleOption>(dK1, dW1, dK2, dW2, index));
}

/** BasketPayoff basket option  payoff
  * @return Function, such that its operator()(bvArg) returns the entry of bvArg with max value
  */

class IBasketPayoff : public IFunction{
public:
    //operator
    double operator()(const BVector &bvArg) const {
        return *std::max_element(bvArg.begin(), bvArg.end());
    }

};

Function exercises::BasketPayoff() {
    return Function(make_shared<IBasketPayoff>());
}

/** AveragePayoff average payoff
  * @return Function, such that its operator()(bvArg) returns the mean of the entries of bvArg
  */

class IAveragePayoff : public IFunction {
public:
    // constructor
    IAveragePayoff() = default;

    double operator()(const BVector &bvArg) const{
        double n = bvArg.size();

        return std::accumulate(bvArg.begin(), bvArg.end(), 0.0) / n;
    }
};

Function exercises::AveragePayoff(){
    return Function(make_shared<IAveragePayoff>());
}

/** SumOfSquares sum of squares
  * @return Function, such that its operator()(bvArg) returns the sum of squares of the entries of bvArg
  */

class ISumOfSquares : public IFunction{
public:
    ISumOfSquares() = default;

    double operator()(const BVector &bvArg) const{
        //square all entries
        BVector squared(bvArg);
        std::transform(bvArg.begin(), bvArg.end(), squared.begin(),
                       [](double x) {return x * x;});

        // return sum of all squared entries
        return std::accumulate(squared.begin(), squared.end(), 0.0);
    }
};

Function exercises::SumOfSquares(){
    return Function(make_shared<ISumOfSquares>());
}

/** InnerProduct sum of squares
  * @param bvBase boost vector
  * @return Function, such that its operator()(bvArg) returns the inner product of bvBase and bvArg
  */

class IInnerProduct : public IFunction{
public:
    //constructor
    explicit IInnerProduct(const BVector & bvBase) : bvBase_(bvBase) {};

    // operator
    double operator()(const BVector & bvArg) const {
        return std::inner_product(bvArg.begin(), bvArg.end(), bvBase_.begin(), 0.0);
    }

private:
    BVector bvBase_;
};


Function exercises::InnerProduct(const BVector & bvBase){
    return Function(make_shared<IInnerProduct>(bvBase));
}