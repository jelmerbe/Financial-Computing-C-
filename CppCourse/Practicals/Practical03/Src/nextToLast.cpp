//
// Created by Jelmer Bennema on 11/4/23.
//

#include "Practical03/Practical03Exercises.hpp"

/** Returns the value stored in the next to last node of a given list.
   * @param l linked list
   * @return the int value from the next to last node assuming the list has at least two nodes.
   */
int exercises::nextToLast(const LinkedList03 &l) {

    const LinkedList03 *current = &l;
    const LinkedList03 *prev    = nullptr;

    while(current->hasNext()){
        prev = current;
        current = current->getNext();
    }

    return prev->getData();
}

/** Returns the value stored in the next to last node of a given list using a recursive algorithm.
 * @param l linked list
 * @return the int value from the next to last node assuming the list has at least two nodes.
 */
int exercises::nextToLastRecursive(const LinkedList03 & l){

    if (!l.getNext()->hasNext())
        return l.getData();

    return exercises::nextToLastRecursive( *l.getNext());
}