#ifndef __EXAMPLES_HPP__
#define __EXAMPLES_HPP__

#include <vector>
#include <cassert> // required for assert

// macro definitions
// alternative names for assert to emphasise purpose within context
#define PRECONDITION assert
#define POSTCONDITION assert
#define ASSERT assert

typedef std::vector<double> dVector;

double thirdOfSecondElement(const dVector &);

double thirdOfSecondElementWithBoundCheck(const dVector &);

void callThirdOfSecondElementExample();

#endif
