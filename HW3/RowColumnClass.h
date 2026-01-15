#ifndef ROWCOLUMNCLASS_H
#define ROWCOLUMNCLASS_H

#include <iosfwd>
#include "constants.h"

/*
 * File: RowColumnClass.h
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 *
 * Purpose:
 *   Represents a 2D location using row and column indices.
 *   Used for addressing pixels and placing patterns.
 */

class RowColumnClass
{
private:
  // Data Members
  int rowIndex;
  int columnIndex;

public:
  // Constructors
  // Default 
  RowColumnClass();
  // With Values
  RowColumnClass(int inRow, int inCol);

  // Setter functions
  // Set row and column to given values
  void setRowCol(int inRow, int inCol);

  // Set row to given values
  void setRow(int inRow);

  // Set column to given values
  void setCol(int inCol);

  // Getter functions
  // Return row value
  int getRow() const;

  // Return column value
  int getCol() const;

  // Utilities
  // Add offsets (dr, dc) to current position (no clipping here).
  void addRowCol(int dRow, int dCol);

  // Exact equality on both coordinates.
  bool isEqual(const RowColumnClass &rhs) const;

  // Stream I/O
  // Reads two ints: row col. Returns true on success, false on failure.
  bool readFrom(std::istream &in);

  // Writes "row col".
  void writeTo(std::ostream &out) const;
};

#endif // ROWCOLUMNCLASS_H
