/*
 * File: LinkedNodeClass.inl
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 12/01/2025
 *
 * Purpose:
 *   Template implementation file for LinkedNodeClass.
 *   Contains definitions of all templated member functions.
 *   Included at the end of LinkedNode.h.
 */

// LinkedNodeClass.inl
// Implementation of templated LinkedNodeClass methods.

#ifndef LINKEDNODECLASS_INL
#define LINKEDNODECLASS_INL


template <class T>
LinkedNodeClass<T>::LinkedNodeClass(
  LinkedNodeClass<T> *inPrev,
  const T &inVal,
  LinkedNodeClass<T> *inNext
)
{
  prevNode = inPrev;
  nodeVal = inVal;
  nextNode = inNext;
}

// Accessors
// Return the value stored in this node.
template <class T>
T LinkedNodeClass<T>::getValue() const
{
  return nodeVal;
}

// Return pointer to next node in the structure.
template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getNext() const
{
  return nextNode;
}

// Return pointer to previous node in the structure.
template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getPrev() const
{
  return prevNode;
}

// Mutators
// Set this node's next pointer to NULL.
template <class T>
void LinkedNodeClass<T>::setNextPointerToNull()
{
  nextNode = 0;
}

// Set this node's previous pointer to NULL.
template <class T>
void LinkedNodeClass<T>::setPreviousPointerToNull()
{
  prevNode = 0;
}

// Update neighboring nodes so they point to this node.
// If prevNode is not NULL, make its "next" pointer refer to this node.
// If nextNode is not NULL, make its "prev" pointer refer to this node.
// This node's own prevNode/nextNode pointers are not modified.
template <class T>
void LinkedNodeClass<T>::setBeforeAndAfterPointers()
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

#endif // LINKEDNODECLASS_INL