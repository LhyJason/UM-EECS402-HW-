#include "FIFOQueueClass.h"
#include <iostream>
using namespace std;

/*
 * File: FIFOQueueClass.cpp
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/17/2025
 *
 * Purpose:
 *   Implementation of FIFOQueueClass.
 *   Provides a basic first-in-first-out queue of ints using
 *   LinkedNodeClass nodes. Enqueue adds to the tail, dequeue
 *   removes from the head.
 */

// Constructors / Destructor
// Default constructor:
// Initialize an empty queue.
FIFOQueueClass::FIFOQueueClass()
{
  head = 0;
  tail = 0;
}

// Destructor:
// Free all nodes.
FIFOQueueClass::~FIFOQueueClass()
{
  clear();
}

// Mutators

// Insert a value at the back of the queue.
void FIFOQueueClass::enqueue(const int &newItem)
{
  // Case 1: empty queue
  if (head == 0)
  {
    head = new LinkedNodeClass(0, newItem, 0);
    tail = head;
    return;
  }

  // Case 2: non-empty, add after tail
  LinkedNodeClass *newNode = new LinkedNodeClass(tail, newItem, 0);
  newNode->setBeforeAndAfterPointers(); // update old tail->next
  tail = newNode;
}

// Attempt to remove the front value from the queue.
bool FIFOQueueClass::dequeue(int &outItem)
{
  if (head == 0)
  {
    // Empty queue
    return false;
  }

  outItem = head->getValue();

  // Only one node
  if (head == tail)
  {
    delete head;
    head = 0;
    tail = 0;
    return true;
  }

  // More than one node
  LinkedNodeClass *oldHead = head;
  head = head->getNext();
  head->setPreviousPointerToNull();
  delete oldHead;

  return true;
}

// Print queue contents on one line.
// Next-to-be-dequeued printed first.
void FIFOQueueClass::print() const
{
  LinkedNodeClass *cur = head;
  bool first = true;

  while (cur != 0)
  {
    if (!first)
    {
      cout << ' ';
    }
    cout << cur->getValue();
    first = false;
    cur = cur->getNext();
  }

  cout << '\n';
}

// Return number of nodes in the queue.
int FIFOQueueClass::getNumElems() const
{
  int count = 0;
  LinkedNodeClass *cur = head;

  while (cur != 0)
  {
    count++;
    cur = cur->getNext();
  }

  return count;
}


// Clear the queue, deleting all nodes.
void FIFOQueueClass::clear()
{
  LinkedNodeClass *cur = head;
  while (cur != 0)
  {
    LinkedNodeClass *toDelete = cur;
    cur = cur->getNext();
    delete toDelete;
  }

  head = 0;
  tail = 0;
}



