#include "Lecture10/bitManipulationExamples.hpp"

// adds two unsigned ints without using +,-,* or /
unsigned int add(unsigned int a , unsigned int b){
	// 0 ^ 0 = 0, 1 ^ 0 = 1
	// 0 ^ 1 = 1, 1 ^ 1 = 0
  unsigned int c = a ^ b;
  unsigned int d = (a & b) << 1; // carry when 1 + 1
  if (d == 0)
    return c;
  else 
    return add(c,d);
}

unsigned int numberOfOnes(unsigned int a){
  unsigned int res = a & 1;
  while(a != 0){
    a >>= 1;
    res += a & 1;
  }
  return res;
}
