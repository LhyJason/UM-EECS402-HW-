#include "SortedListClass.h"
#include <iostream>
using namespace std;

/*
 * File: SortedListClass.cpp
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/17/2025
 *
 * Purpose:
 *   Implementation of SortedListClass.
 *   Provides an always-sorted doubly-linked list storing ints.
 *   Supports insertion in sorted order, removal from front/back,
 *   full deep copying, element lookup, and formatted printing.
 */

// Constructors / Destructor / Assignment
// Default constructor:
// Initialize empty list.
SortedListClass::SortedListClass()
{
  head = 0;
  tail = 0;
}

// Copy constructor:
// Produce a deep copy of rhs.
SortedListClass::SortedListClass(const SortedListClass &rhs)
{
  head = 0;
  tail = 0;

  // Traverse rhs and insert values one by one.
  LinkedNodeClass *cur = rhs.head;
  while (cur != 0)
  {
    insertValue(cur->getValue());
    cur = cur->getNext();
  }
}

// Destructor:
// Free all nodes.
SortedListClass::~SortedListClass()
{
  clear();
}

// Assignment operator:
SortedListClass& SortedListClass::operator=(const SortedListClass &rhs)
{
  if (this == &rhs)
  {
    return *this; // Self-assignment check
  }

  // Clear existing content
  clear();

  // Deep-copy rhs
  LinkedNodeClass *cur = rhs.head;
  while (cur != 0)
  {
    insertValue(cur->getValue());
    cur = cur->getNext();
  }

  return *this;
}

// Mutators

// Remove all nodes and reset to empty list.
void SortedListClass::clear()
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

// Insert value into correct sorted position.
// Duplicates go AFTER existing ones.
void SortedListClass::insertValue(const int &valToInsert)
{
  // Case 1: empty list
  if (head == 0)
  {
    LinkedNodeClass *newNode = new LinkedNodeClass(0, valToInsert, 0);
    head = newNode;
    tail = newNode;
    return;
  }

  // Find insertion point
  LinkedNodeClass *cur = head;
  while (cur != 0 && cur->getValue() <= valToInsert)
  {
    cur = cur->getNext();
  }

  // Case 2: insert at END
  if (cur == 0)
  {
    LinkedNodeClass *newNode = new LinkedNodeClass(tail, valToInsert, 0);
    newNode->setBeforeAndAfterPointers(); // update tail->next
    tail = newNode;
    return;
  }

  // Case 3: insert BEFORE 'cur' (middle or head)

  // Insert at HEAD
  if (cur == head)
  {
    LinkedNodeClass *newNode = new LinkedNodeClass(0, valToInsert, head);
    newNode->setBeforeAndAfterPointers(); // update head->prev
    head = newNode;
    return;
  }

  // Insert in MIDDLE
  LinkedNodeClass *prevNode = cur->getPrev();
  LinkedNodeClass *newNode = new LinkedNodeClass(prevNode, valToInsert, cur);
  newNode->setBeforeAndAfterPointers();
}

// Print from head → tail.
void SortedListClass::printForward() const
{
  cout << "Forward List Contents Follow:" << endl;
  LinkedNodeClass *cur = head;

  while (cur != 0)
  {
    cout << "  " << cur->getValue() << endl;
    cur = cur->getNext();
  }

  cout << "End Of List Contents" << endl;
}

// Print from tail → head.
void SortedListClass::printBackward() const
{
  cout << "Backward List Contents Follow:" << endl;
  LinkedNodeClass *cur = tail;

  while (cur != 0)
  {
    cout << "  " << cur->getValue() << endl;
    cur = cur->getPrev();
  }

  cout << "End Of List Contents" << endl;
}

// Remove front node.
// Return true if success, false if empty.
bool SortedListClass::removeFront(int &theVal)
{
  if (head == 0)
  {
    return false;
  }

  theVal = head->getValue();

  // Only one element
  if (head == tail)
  {
    delete head;
    head = 0;
    tail = 0;
    return true;
  }

  // More than one
  LinkedNodeClass *oldHead = head;
  head = head->getNext();
  head->setPreviousPointerToNull();
  delete oldHead;

  return true;
}

// Remove last node.
// Return true if success, false if empty.
bool SortedListClass::removeLast(int &theVal)
{
  if (tail == 0)
  {
    return false;
  }

  theVal = tail->getValue();

  // Only one node
  if (head == tail)
  {
    delete tail;
    head = 0;
    tail = 0;
    return true;
  }

  // More than one
  LinkedNodeClass *oldTail = tail;
  tail = tail->getPrev();
  tail->setNextPointerToNull();
  delete oldTail;

  return true;
}

// Accessors
// Return number of nodes.
int SortedListClass::getNumElems() const
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

// Get element by 0-based index.
// Return true if valid, false if out-of-range.
bool SortedListClass::getElemAtIndex(const int index, int &outVal) const
{
  if (index < 0)
  {
    return false;
  }

  int count = 0;
  LinkedNodeClass *cur = head;

  while (cur != 0)
  {
    if (count == index)
    {
      outVal = cur->getValue();
      return true;
    }

    count++;
    cur = cur->getNext();
  }

  return false;
}
