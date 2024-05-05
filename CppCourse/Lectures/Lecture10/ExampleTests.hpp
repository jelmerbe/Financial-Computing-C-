#ifndef __EXAMPLES_UNIT_TEST_HPP__
#define __EXAMPLES_UNIT_TEST_HPP__

#include "gtest/gtest.h"
#include "Examples.hpp"
#include <string>

TEST(thirdOfSecondElement, badInput){
  dVector vec(1,0.0);
  EXPECT_DEATH(thirdOfSecondElement(vec),"Assertion failed");
}

TEST(thirdOfSecondElement, validInput1){
  dVector vec(2,1.0);
  EXPECT_DOUBLE_EQ(1.0/3.0, thirdOfSecondElement(vec));
}

TEST(thirdOfSecondElement, validInput2){
  dVector vec(200,1.0);
  EXPECT_DOUBLE_EQ(1.0/3.0, thirdOfSecondElement(vec));
}

TEST(thirdOfSecondElementWithBoundCheck, badInput){
  dVector vec(1,0.0);
  EXPECT_THROW(thirdOfSecondElementWithBoundCheck(vec),std::string);
}

TEST(thirdOfSecondElementWithBoundCheck, validInput1){
  dVector vec(2,1.0);
  EXPECT_NEAR(1.0/3.0, thirdOfSecondElementWithBoundCheck(vec),1.0e-15);
}

TEST(thirdOfSecondElementWithBoundCheck, validInput2){
  dVector vec(200,1.0);
  EXPECT_NEAR(1.0/3.0, thirdOfSecondElementWithBoundCheck(vec),1.0e-15);
}


#endif
