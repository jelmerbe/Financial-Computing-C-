#ifndef __BIT_MANIP_UNIT_TEST_HPP__
#define __BIT_MANIP_UNIT_TEST_HPP__

#include "gtest/gtest.h"
#include "bitManipulationExamples.hpp"

TEST(AdditionTest, ZeroZero){
  EXPECT_EQ(0,add(0,0)); // expected vs returned
}

TEST(AdditionTest, ZeroOther){
  for(unsigned int i(0); i<1000; i++)
    EXPECT_EQ(i,add(0,i));
}

TEST(AdditionTest, OtherOther){
  for(unsigned int i(1); i<200; i++)
    for(unsigned int j(1); j<200; j++)
      EXPECT_EQ(i+j, add(i,j));
}

TEST(NumberOfOnes, Zero){
  EXPECT_EQ(0,numberOfOnes(0));
}

TEST(NumberOfOnes, One){
  EXPECT_EQ(1,numberOfOnes(1));
}

TEST(NumberOfOnes, PowersOfTwo) {
  for(unsigned int i(1); i<31; i++)
    EXPECT_EQ(1, numberOfOnes(1<<i));
}

TEST(NumberOfOnes, PowersOfTwoMinusOne) {
  for(unsigned int i(1); i<31; i++)
    EXPECT_EQ(i, numberOfOnes((1<<i)-1));
}

TEST(NumberOfOnes, General) {
  EXPECT_EQ(2, numberOfOnes(3));
  EXPECT_EQ(2, numberOfOnes(5));
  EXPECT_EQ(2, numberOfOnes(6));
  EXPECT_EQ(2, numberOfOnes(12));
}

#endif
