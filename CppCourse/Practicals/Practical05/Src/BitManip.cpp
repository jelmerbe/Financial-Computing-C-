//
// Created by Jelmer Bennema on 11/22/23.
//

#include "Practical05/Practical05Exercises.hpp"
#include "Utils/UtilityFunctions.hpp"

unsigned int exercises::subtract(unsigned int a, unsigned int b){
    while (b != 0) {
        // Borrow contains common set bits of A and ~B
        unsigned int borrow = (~a) & b;

        // Subtraction of bits
        a = a ^ b;

        // Borrow is shifted by one so that subtracting it from A gives the required difference
        b = borrow << 1;
    }
    return a;
}

/** Swaps the values of two arguments using bitmanipulation operations only,
 * and without any additional temp variables.
 * @param a
 * @param b
 */
void swap(unsigned int & a, unsigned int & b){
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}
