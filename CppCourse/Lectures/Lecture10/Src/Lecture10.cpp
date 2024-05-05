#include "Lecture10/BitManipTests.hpp"
#include "Lecture10/ExampleTests.hpp"
#include "Lecture10/Examples.hpp"

int main(int argc, char **argv) {
  
  callThirdOfSecondElementExample();

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/*
$  ../bin/./Lecture10 --gtest_filter=NumberOfOnes*
Note: Google Test filter = NumberOfOnes*
[==========] Running 5 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 5 tests from NumberOfOnes
[ RUN      ] NumberOfOnes.Zero
[       OK ] NumberOfOnes.Zero (0 ms)
[ RUN      ] NumberOfOnes.One
[       OK ] NumberOfOnes.One (0 ms)
[ RUN      ] NumberOfOnes.PowersOfTwo
[       OK ] NumberOfOnes.PowersOfTwo (0 ms)
[ RUN      ] NumberOfOnes.PowersOfTwoMinusOne
[       OK ] NumberOfOnes.PowersOfTwoMinusOne (0 ms)
[ RUN      ] NumberOfOnes.General
[       OK ] NumberOfOnes.General (0 ms)
[----------] 5 tests from NumberOfOnes (0 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 5 tests.
*/
