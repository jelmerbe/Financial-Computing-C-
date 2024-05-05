//
// Created by Jelmer Bennema on 10/27/23.
//

#include "Practical03/Practical03Exercises.hpp"

/** Computes the length of a linked list.
   * @param l linked list
   * @return length of l
   */
unsigned int exercises::length(const LinkedList03 & l){
    unsigned int count = 1.0;
    const LinkedList03* current = &l;

    while(current -> hasNext()){
        ++count;
        current = current -> getNext();
    }
    return count;
}

/** Computes the length of a linked list using recursive algorithm.
   * @param l linked list
   * @return length of l
   */
unsigned int exercises::lengthRecursive(const LinkedList03 & l){

    if(!l.hasNext())
        return 1;

    else
        return 1 + exercises::lengthRecursive(*l.getNext());
}

