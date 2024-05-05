//
// Created by Jelmer Bennema on 10/27/23.
//

#include "Practical03/Practical03Exercises.hpp"

/** Checks if a list has a node that contains a given integer.
   * @param l linked list
   * @param i integer to look for
   * @return true if l has at least one node with value i, otherwise 0
   */
bool exercises::hasElement(const LinkedList03 & l, int i){
    const LinkedList03* current = &l;

    while(current != nullptr){

        if(current -> getData() == i)
            return true;

        // move to next node
        current = current -> getNext();
    }

    // int i is not found, return false
    return false;
}

/** Checks if a list has a node that contains a given integer using a recursive algorithm.
 * @param l linked list
 * @param i integer to look for
 * @return true if l has at least one node with value i, otherwise 0
 */
bool exercises::hasElementRecursive(const LinkedList03 & l, int i){

    if(l.getData() == i) {
        return true;
    }

    if (l.hasNext()) {
        return exercises::hasElementRecursive(*l.getNext(), i);
    }

    return false;
}