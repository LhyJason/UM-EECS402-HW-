#include "LIFOStackClass.h"
#include <iostream>
using namespace std;

/*
 * File: LIFOStackClass.cpp
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/17/2025
 *
 * Purpose:
 *   Implementation of LIFOStackClass.
 *   Provides a basic last-in-first-out stack of ints using
 *   LinkedNodeClass nodes. push adds to the top (head), pop
 *   removes from the top (head).
 */

// Constructors / Destructor

// Default constructor:
// Initialize an empty stack.
LIFOStackClass::LIFOStackClass()
{
  head = 0;
  tail = 0;
}

// Destructor:
// Free all nodes.
LIFOStackClass::~LIFOStackClass()
{
  clear();
}

// Push a value onto the top of the stack (at head).
void LIFOStackClass::push(const int &newItem)
{
  // Case 1: empty stack
  if (head == 0)
  {
    LinkedNodeClass *newNode = new LinkedNodeClass(0, newItem, 0);
    head = newNode;
    tail = newNode;
    return;
  }

  // Case 2: non-empty, insert before head
  LinkedNodeClass *newNode = new LinkedNodeClass(tail, newItem, 0);
  newNode->setBeforeAndAfterPointers(); // update old head->prev
  tail = newNode;
}

// Attempt to pop the top value from the stack.
bool LIFOStackClass::pop(int &outItem)
{
  if (head == 0)
  {
    // Empty stack
    return false;
  }

  outItem = tail->getValue();

  // Only one node
  if (head == tail)
  {
    delete tail;
    head = 0;
    tail = 0;
    return true;
  }

  // More than one node
  LinkedNodeClass *oldTail = tail;
  tail = tail->getPrev();
  tail->setNextPointerToNull();
  delete oldTail;

  return true;
}

// Print stack contents on one line.
// Next-to-be-popped printed first.
void LIFOStackClass::print() const
{
  LinkedNodeClass *cur = tail;
  bool first = true;

  while (cur != 0)
  {
    if (!first)
    {
      cout << ' ';
    }
    cout << cur->getValue();
    first = false;
    cur = cur->getPrev();
  }

  cout << '\n';
}

// Return number of nodes in the stack.
int LIFOStackClass::getNumElems() const
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

// Clear the stack, deleting all nodes.
void LIFOStackClass::clear()
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

