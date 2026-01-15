#include "LinkedNodeClass.h"

/*
 * File: LinkedNodeClass.cpp
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/17/2025
 *
 * Purpose:
 *   Implementation of LinkedNodeClass.
 *   Represents a single node in a doubly-linked data structure,
 *   storing one int value and pointers to previous and next nodes.
 */

// Constructors
// The ONLY constructor:
// Initializes this node's previous pointer, value, and next pointer.
LinkedNodeClass::LinkedNodeClass(
  LinkedNodeClass *inPrev,
  const int &inVal,
  LinkedNodeClass *inNext
)
{ // Initializes this node's previous pointer, value, and next pointer.
  prevNode = inPrev;
  nodeVal = inVal;
  nextNode = inNext;
}

// Accessors
// Return the value stored in this node.
int LinkedNodeClass::getValue() const
{
  return nodeVal;
}

// Return pointer to next node in the structure.
LinkedNodeClass* LinkedNodeClass::getNext() const
{
  return nextNode;
}

// Return pointer to previous node in the structure.
LinkedNodeClass* LinkedNodeClass::getPrev() const
{
  return prevNode;
}

// Mutators
// Set this node's next pointer to NULL.
void LinkedNodeClass::setNextPointerToNull()
{
  nextNode = 0;
}

// Set this node's previous pointer to NULL.
void LinkedNodeClass::setPreviousPointerToNull()
{
  prevNode = 0;
}

// Update neighboring nodes so they point to this node.
// If prevNode is not NULL, make its "next" pointer refer to this node.
// If nextNode is not NULL, make its "prev" pointer refer to this node.
// This node's own prevNode/nextNode pointers are not modified.
void LinkedNodeClass::setBeforeAndAfterPointers()
{
  if (prevNode != 0)
  {
    prevNode->nextNode = this;
  }

  if (nextNode != 0)
  {
    nextNode->prevNode = this;
  }
}
