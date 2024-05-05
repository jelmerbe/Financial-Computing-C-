
#ifndef _PRACTICAL_03_EXERCISES_H__
#define _PRACTICAL_03_EXERCISES_H__

#include <string>
#include "LinkedLists.hpp"

namespace exercises
{



  /** Computes the length of a linked list.
   * @param l linked list
   * @return length of l
   */
  unsigned int length(const LinkedList03 & l);

  /** Computes the length of a linked list using recursive algorithm.
   * @param l linked list
   * @return length of l
   */
  unsigned int lengthRecursive(const LinkedList03 & l);

  /** Checks if a list has a node that contains a given integer.
   * @param l linked list
   * @param i integer to look for
   * @return true if l has at least one node with value i, otherwise 0
   */
  bool hasElement(const LinkedList03 & l, int i);

  /** Checks if a list has a node that contains a given integer using a recursive algorithm.
   * @param l linked list
   * @param i integer to look for
   * @return true if l has at least one node with value i, otherwise 0
   */
  bool hasElementRecursive(const LinkedList03 & l, int i);

  /** Returns the value stored in the last node of a given list.
   * @param l linked list
   * @return the int value from the last node.
   */
  int lastElement(const LinkedList03 & l);

  /** Returns the value stored in the last node of a given list using a recursive algorithm.
   * @param l linked list
   * @return the int value from the last node.
   */
  int lastElementRecursive(const LinkedList03 & l);

  /** Returns the value stored in the next to last node of a given list.
   * @param l linked list
   * @return the int value from the next to last node assuming the list has at least two nodes. 
   */  
  int nextToLast(const LinkedList03 & l);

  /** Returns the value stored in the next to last node of a given list using a recursive algorithm.
   * @param l linked list
   * @return the int value from the next to last node assuming the list has at least two nodes. 
   */  
  int nextToLastRecursive(const LinkedList03 & l);

  /** Returns the clone of a given list.
   * @param l linked list
   * @return a new list l2 that has the same number of nodes as l, 
             and the nth node in l2 contains the same int value as the 
             nth node in l.
   */
  LinkedList03 clone(const LinkedList03 & l);
  
}

#endif //_PRACTICAL_03_EXERCISES_H__
