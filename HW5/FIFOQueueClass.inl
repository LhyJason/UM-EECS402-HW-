/*
 * File: FIFOQueueClass.inl
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 12/01/2025
 *
 * Purpose:
 *   Template implementation file for FIFOQueueClass.
 *   Included by FIFOQueueClass.h.
 */

// FIFOQueueClass.inl
// Implementation of templated FIFOQueueClass methods.

#ifndef FIFOQUEUECLASS_INL
#define FIFOQUEUECLASS_INL

// Default constructor:
// Initialize an empty queue.
template <class T>
FIFOQueueClass<T>::FIFOQueueClass()
{
  head = 0;
  tail = 0;
}

// Destructor:
// Free all nodes.
template <class T>
FIFOQueueClass<T>::~FIFOQueueClass()
{
  clear();
}

// Insert a value at the back of the queue.
template <class T>
void FIFOQueueClass<T>::enqueue(const T &newItem)
{
  // Case 1: empty queue
  if (head == 0)
  {
    head = new LinkedNodeClass<T>(0, newItem, 0);
    tail = head;
    return;
  }

  // Case 2: non-empty, add after tail
  LinkedNodeClass<T> *newNode = new LinkedNodeClass<T>(tail, newItem, 0);
  newNode->setBeforeAndAfterPointers(); // update old tail->next
  tail = newNode;
}

// Attempt to remove the front value from the queue.
template <class T>
bool FIFOQueueClass<T>::dequeue(T &outItem)
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
  LinkedNodeClass<T> *oldHead = head;
  head = head->getNext();
  head->setPreviousPointerToNull();
  delete oldHead;

  return true;
}

// Print queue contents on one line.
// Next-to-be-dequeued printed first.
template <class T>
void FIFOQueueClass<T>::print() const
{
  LinkedNodeClass<T> *cur = head;
  bool first = true;

  while (cur != 0)
  {
    if (!first)
    {
      std::cout << ' ';
    }
    std::cout << cur->getValue();
    first = false;
    cur = cur->getNext();
  }

  std::cout << '\n';
}

// Return number of nodes in the queue.
template <class T>
int FIFOQueueClass<T>::getNumElems() const
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

// Clear the queue, deleting all nodes.
template <class T>
void FIFOQueueClass<T>::clear()
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

#endif // FIFOQUEUECLASS_INL
