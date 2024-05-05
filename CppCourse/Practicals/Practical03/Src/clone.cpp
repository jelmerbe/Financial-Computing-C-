//
// Created by Jelmer Bennema on 11/4/23.
//

#include "Practical03/Practical03Exercises.hpp"

/** Returns the clone of a given list.
   * @param l linked list
   * @return a new list l2 that has the same number of nodes as l,
             and the nth node in l2 contains the same int value as the
             nth node in l.
   */
LinkedList03 exercises::clone(const LinkedList03 & l){
    LinkedList03 *l2 = new LinkedList03(l.getData());
    const LinkedList03 *current = &l;

    while(current -> hasNext()){
        // increment current
        current = current -> getNext();

        l2 -> append(current ->getData());  // create new node
    }

    return *l2;
}