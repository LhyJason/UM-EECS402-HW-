#ifndef SORTEDLISTCLASS_H
#define SORTEDLISTCLASS_H

#include <iostream>
#include "LinkedNodeClass.h"

/*
 * File: SortedListClass.h
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 12/1/2025
 * (Templated version for Project 5)
 *
 * Purpose:
 *   Class representing a sorted doubly-linked list storing values of
 *   templated type T.
 *   The list maintains ascending order automatically on insert.
 *   Duplicate values are allowed, and new duplicates are inserted
 *   AFTER existing values. Supports insertion, removal from front
 *   or back, traversal, indexed access, and deep copying.
 */

template <class T>
class SortedListClass
{
private:
  // Pointer to first node in the list (NULL if empty)
  LinkedNodeClass<T> *head;

  // Pointer to last node in the list (NULL if empty)
  LinkedNodeClass<T> *tail;

public:
  // Constructors / Destructor / Assignment

  // Default constructor:
  // Initialize an empty list.
  SortedListClass();

  // Copy constructor:
  // Performs a deep copy of another SortedListClass.
  SortedListClass(const SortedListClass<T> &rhs);

  // Destructor:
  // Frees all dynamically allocated nodes.
  ~SortedListClass();

  // Assignment operator:
  // Deep-copy assignment from another list.
  SortedListClass<T>& operator=(const SortedListClass<T> &rhs);

  // Mutators

  // Remove all nodes; reset to empty list.
  void clear();

  // Insert a value into its appropriate sorted position.
  // New duplicate values go AFTER existing ones.
  void insertValue(const T &valToInsert);

  // Print contents from head → tail with required formatting.
  void printForward() const;

  // Print contents from tail → head with required formatting.
  void printBackward() const;

  // Remove the front node.
  // Return true on success; false if empty.
  bool removeFront(T &theVal);

  // Remove the last node.
  // Return true on success; false if empty.
  bool removeLast(T &theVal);

  // Return number of elements in the list.
  int getNumElems() const;

  // Get element at 0-based index "index".
  // Return true if valid; false if out of range.
  bool getElemAtIndex(const int index, T &outVal) const;
};

#include "SortedListClass.inl"

#endif // SORTEDLISTCLASS_H
