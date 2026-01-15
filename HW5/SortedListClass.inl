/*
 * File: SortedListClass.inl
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 12/01/2025
 *
 * Purpose:
 *   Template implementation file for SortedListClass.
 *   Contains definitions of all templated member functions.
 *   Included at the end of SortedListClass.h.
 */

// SortedListClass.inl
// Implementation of templated SortedListClass methods.

#ifndef SORTEDLISTCLASS_INL
#define SORTEDLISTCLASS_INL

// Default constructor:
// Initialize empty list.
template <class T>
SortedListClass<T>::SortedListClass()
{
  head = 0;
  tail = 0;
}

// Copy constructor:
// Produce a deep copy of rhs.
template <class T>
SortedListClass<T>::SortedListClass(const SortedListClass<T> &rhs)
{
  head = 0;
  tail = 0;

  // Traverse rhs and insert values one by one.
  LinkedNodeClass<T> *cur = rhs.head;
  while (cur != 0)
  {
    insertValue(cur->getValue());
    cur = cur->getNext();
  }
}

// Destructor:
// Free all nodes.
template <class T>
SortedListClass<T>::~SortedListClass()
{
  clear();
}

// Assignment operator:
template <class T>
SortedListClass<T>& SortedListClass<T>::operator=(const SortedListClass<T> &rhs)
{
  if (this == &rhs)
  {
    return *this; // Self-assignment check
  }

  // Clear existing content
  clear();

  // Deep-copy rhs
  LinkedNodeClass<T> *cur = rhs.head;
  while (cur != 0)
  {
    insertValue(cur->getValue());
    cur = cur->getNext();
  }

  return *this;
}

// Remove all nodes and reset to empty list.
template <class T>
void SortedListClass<T>::clear()
{
  LinkedNodeClass<T> *cur = head;
  while (cur != 0)
  {
    LinkedNodeClass<T> *toDelete = cur;
    cur = cur->getNext();
    delete toDelete;
  }

  head = 0;
  tail = 0;
}

// Insert value into correct sorted position.
// Duplicates go AFTER existing ones.
template <class T>
void SortedListClass<T>::insertValue(const T &valToInsert)
{
  // Case 1: empty list
  if (head == 0)
  {
    LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(0, valToInsert, 0);
    head = newNode;
    tail = newNode;
    return;
  }

  // Find insertion point
  // We use <= so that duplicates are inserted AFTER existing ones.
  LinkedNodeClass<T> *cur = head;
  while (cur != 0 && cur->getValue() <= valToInsert)
  {
    // condition equivalent to (cur->getValue() <= valToInsert)
    cur = cur->getNext();
  }

  // Case 2: insert at END
  if (cur == 0)
  {
    LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(tail, valToInsert, 0);
    newNode->setBeforeAndAfterPointers(); // update tail->next
    tail = newNode;
    return;
  }

  // Case 3: insert BEFORE 'cur' (middle or head)

  // Insert at HEAD
  if (cur == head)
  {
    LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(0, valToInsert, head);
    newNode->setBeforeAndAfterPointers(); // update head->prev
    head = newNode;
    return;
  }

  // Insert in MIDDLE
  LinkedNodeClass<T> *prevNode = cur->getPrev();
  LinkedNodeClass<T> *newNode = 
    new LinkedNodeClass<T>(prevNode, valToInsert, cur);
  newNode->setBeforeAndAfterPointers();
}

// Print from head → tail.
template <class T>
void SortedListClass<T>::printForward() const
{
  std::cout << "Forward List Contents Follow:" << std::endl;
  LinkedNodeClass<T> *cur = head;

  while (cur != 0)
  {
    std::cout << "  " << cur->getValue() << std::endl;
    cur = cur->getNext();
  }

  std::cout << "End Of List Contents" << std::endl;
}

// Print from tail → head.
template <class T>
void SortedListClass<T>::printBackward() const
{
  std::cout << "Backward List Contents Follow:" << std::endl;
  LinkedNodeClass<T> *cur = tail;

  while (cur != 0)
  {
    std::cout << "  " << cur->getValue() << std::endl;
    cur = cur->getPrev();
  }

  std::cout << "End Of List Contents" << std::endl;
}

// Remove front node.
// Return true if success, false if empty.
template <class T>
bool SortedListClass<T>::removeFront(T &theVal)
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
  LinkedNodeClass<T> *oldHead = head;
  head = head->getNext();
  head->setPreviousPointerToNull();
  delete oldHead;

  return true;
}

// Remove last node.
// Return true if success, false if empty.
template <class T>
bool SortedListClass<T>::removeLast(T &theVal)
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
  LinkedNodeClass<T> *oldTail = tail;
  tail = tail->getPrev();
  tail->setNextPointerToNull();
  delete oldTail;

  return true;
}

// Return number of nodes.
template <class T>
int SortedListClass<T>::getNumElems() const
{
  int count = 0;
  LinkedNodeClass<T> *cur = head;

  while (cur != 0)
  {
    count++;
    cur = cur->getNext();
  }

  return count;
}

// Get element by 0-based index.
// Return true if valid, false if out-of-range.
template <class T>
bool SortedListClass<T>::getElemAtIndex(const int index, T &outVal) const
{
  if (index < 0)
  {
    return false;
  }

  int count = 0;
  LinkedNodeClass<T> *cur = head;

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

#endif // SORTEDLISTCLASS_INL
