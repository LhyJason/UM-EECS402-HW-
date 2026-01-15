#ifndef FIFOQUEUECLASS_H
#define FIFOQUEUECLASS_H

#include <iostream>
#include "LinkedNodeClass.h"

/*
 * File: FIFOQueueClass.h
* Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 12/1/2025
 * (Templated version for Project 5)
 *
 * Purpose:
 *   Class representing a simple first-in-first-out (FIFO) queue
 *   using a doubly-linked list of LinkedNodeClass<T> nodes. Supports
 *   enqueue at the back and dequeue from the front, along with
 *   printing, counting elements, and clearing the queue.
 */

template <class T>
class FIFOQueueClass
{
private:
  // Pointer to first node in the queue (NULL if empty).
  // This is the next node that would be dequeued.
  LinkedNodeClass<T> *head;

  // Pointer to last node in the queue (NULL if empty).
  // New nodes are enqueued at the tail.
  LinkedNodeClass<T> *tail;

public:
  // Constructors / Destructor

  // Default constructor:
  // Initialize an empty queue.
  FIFOQueueClass();

  // NOTE: Copy constructor and assignment operator are NOT defined.
  // Using them would result in shallow copies and is not supported.

  // Destructor:
  // Frees all nodes in the queue.
  ~FIFOQueueClass();

  // Mutators

  // Insert a value at the back of the queue.
  void enqueue(const T &newItem);

  // Attempt to remove the front value from the queue.
  // On success: outItem receives the value, function returns true.
  // If the queue is empty: function returns false, outItem undefined.
  bool dequeue(T &outItem);

  // Print the queue contents on one line.
  // Values printed in order of next-to-be-dequeued first.
  // Separated by single spaces, then a newline at the end.
  void print() const;

  // Return the number of elements (nodes) in the queue.
  int getNumElems() const;

  // Clear the queue to an empty state, deleting all nodes.
  void clear();
};

#include "FIFOQueueClass.inl"

#endif // FIFOQUEUECLASS_H
