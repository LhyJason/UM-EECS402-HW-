#ifndef LINKEDNODECLASS_H
#define LINKEDNODECLASS_H

/*
 * File: LinkedNodeClass.h
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/17/2025
 *
 * Purpose:
 * Class representing a single node in a doubly-linked data structure.
 * Each node stores one int value and pointers to the previous and
 * next nodes in the structure. This node class does not know about
 * any particular list/queue/stack type that uses it.
 */

class LinkedNodeClass
{
private:
  // Data members
  // Pointer to node that comes before this one (NULL if first)
  LinkedNodeClass *prevNode;

  // Value stored in this node
  int nodeVal;

  // Pointer to node that comes after this one (NULL if last)
  LinkedNodeClass *nextNode;

public:
  // Constructors
  // The ONLY constructor:
  // Initializes this node's previous pointer, value, and next pointer.
  LinkedNodeClass(
    LinkedNodeClass *inPrev,
    const int &inVal,
    LinkedNodeClass *inNext
  );

  // Accessors
  // Return the value stored in this node.
  int getValue() const;

  // Return pointer to next node in the structure.
  LinkedNodeClass* getNext() const;

  // Return pointer to previous node in the structure.
  LinkedNodeClass* getPrev() const;

  // Mutators
  // Set this node's next pointer to NULL.
  void setNextPointerToNull();

  // Set this node's previous pointer to NULL.
  void setPreviousPointerToNull();

  // Update neighboring nodes so they point to this node:
  // If prevNode is not NULL, set its next pointer to this.
  // If nextNode is not NULL, set its prev pointer to this.
  // This node's own pointers are NOT modified.
  void setBeforeAndAfterPointers();
};

#endif // LINKEDNODECLASS_H
