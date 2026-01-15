#ifndef SORTEDLISTCLASS_H
#define SORTEDLISTCLASS_H

#include "LinkedNodeClass.h"

/*
 * File: SortedListClass.h
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/17/2025
 *
 * Purpose:
 *   Class representing a sorted doubly-linked list storing ints.
 *   The list maintains ascending order automatically on insert.
 *   Duplicate values are allowed, and new duplicates are inserted
 *   AFTER existing values. Supports insertion, removal from front
 *   or back, traversal, indexed access, and deep copying.
 */

class SortedListClass
{
private:
  // Pointer to first node in the list (NULL if empty)
  LinkedNodeClass *head;

  // Pointer to last node in the list (NULL if empty)
  LinkedNodeClass *tail;

public:
  // Constructors / Destructor / Assignment

  // Default constructor:
  // Initialize an empty list.
  SortedListClass();

  // Copy constructor:
  // Performs a deep copy of another SortedListClass.
  SortedListClass(const SortedListClass &rhs);

  // Destructor:
  // Frees all dynamically allocated nodes.
  ~SortedListClass();

  // Assignment operator:
  // Deep-copy assignment from another list.
  SortedListClass& operator=(const SortedListClass &rhs);

  // Mutators

  // Remove all nodes; reset to empty list.
  void clear();

  // Insert a value into its appropriate sorted position.
  // New duplicate values go AFTER existing ones.
  void insertValue(const int &valToInsert);

  // Print contents from head → tail with required formatting.
  void printForward() const;

  // Print contents from tail → head with required formatting.
  void printBackward() const;

  // Remove the front node.
  // Return true on success; false if empty.
  bool removeFront(int &theVal);

  // Remove the last node.
  // Return true on success; false if empty.
  bool removeLast(int &theVal);

  // Return number of elements in the list.
  int getNumElems() const;

  // Get element at 0-based index "index".
  // Return true if valid; false if out of range.
  bool getElemAtIndex(const int index, int &outVal) const;
};

#endif // SORTEDLISTCLASS_H
