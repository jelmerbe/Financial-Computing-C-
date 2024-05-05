//
// Created by Jelmer Bennema on 10/27/23.
//

#include "Practical03/Practical03Exercises.hpp"

/** Returns the value stored in the last node of a given list.
   * @param l linked list
   * @return the int value from the last node.
   */
int exercises::lastElement(const LinkedList03 &l) {
    const LinkedList03 *current = &l;

    while(current -> hasNext()){
        current = current -> getNext();
    }

    // return integer value in last element
    return current->getData();
}

/** Returns the value stored in the last node of a given list using a recursive algorithm.
 * @param l linked list
 * @return the int value from the last node.
 */
int exercises::lastElementRecursive(const LinkedList03 &l) {
    if(l.hasNext()){
        return exercises::lastElementRecursive(*l.getNext());
    }

    return l.getData();
}