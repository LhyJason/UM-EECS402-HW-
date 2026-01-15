#ifndef LIFOSTACKCLASS_H
#define LIFOSTACKCLASS_H

#include "LinkedNodeClass.h"

/*
 * File: LIFOStackClass.h
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/17/2025
 *
 * Purpose:
 *   Class representing a simple last-in-first-out (LIFO) stack
 *   using a doubly-linked list of LinkedNodeClass nodes. Supports
 *   push onto the top, pop from the top, printing, counting elements,
 *   and clearing the stack.
 */

class LIFOStackClass
{
private:
  // Pointer to the top node of the stack (NULL if empty).
  // This is the next node that would be popped.
  LinkedNodeClass *head;

  // Pointer to the bottom node of the stack (NULL if empty).
  LinkedNodeClass *tail;

public:
  // Constructors / Destructor

  // Default constructor:
  // Initialize an empty stack.
  LIFOStackClass();

  // NOTE: Copy constructor and assignment operator are NOT defined.
  // Using them would result in shallow copies and is not supported.

  // Destructor:
  // Frees all nodes in the stack.
  ~LIFOStackClass();

  // Mutators

  // Push a value onto the top of the stack.
  void push(const int &newItem);

  // Attempt to pop the top value from the stack.
  // On success: outItem receives the value, function returns true.
  // If the stack is empty: function returns false, outItem undefined.
  bool pop(int &outItem);

  // Print the stack contents on one line.
  // Values printed such that the next-to-be-popped value appears first.
  // Separated by single spaces, then a newline at the end.
  void print() const;

  // Return the number of elements (nodes) in the stack.
  int getNumElems() const;

  // Clear the stack to an empty state, deleting all nodes.
  void clear();
};

#endif // LIFOSTACKCLASS_H
