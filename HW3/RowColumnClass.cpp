#include "RowColumnClass.h"
#include "constants.h"
#include <istream>
#include <ostream>

/*
 * File: RowColumnClass.cpp
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 *
 * Purpose:
 *   Implementation of RowColumnClass. Represents a row/column 2D position.
 */

// Constructors
RowColumnClass::RowColumnClass()
  // Default
  : rowIndex(DEFAULT_INDEX), columnIndex(DEFAULT_INDEX)
{
}

// With Values
RowColumnClass::RowColumnClass(int inRow, int inCol)
  : rowIndex(inRow), columnIndex(inCol)
{
}

// Setter functions
// Set row and column to given values
void RowColumnClass::setRowCol(int inRow, int inCol)
{
  rowIndex = inRow;
  columnIndex = inCol;
}

// Set row
void RowColumnClass::setRow(int inRow)
{
  rowIndex = inRow;
}

// Set col
void RowColumnClass::setCol(int inCol)
{
  columnIndex = inCol;
}

// Getter functions
// Return row value
int RowColumnClass::getRow() const
{
  return rowIndex;
}

// Return column value
int RowColumnClass::getCol() const
{
  return columnIndex;
}

// Add offsets (dRow, dCol) to current position (no clipping here).
void RowColumnClass::addRowCol(int dRow, int dCol)
{
  rowIndex += dRow;
  columnIndex += dCol;
}

// Exact equality on both coordinates.
bool RowColumnClass::isEqual(const RowColumnClass &rhs) const
{
  return (rowIndex == rhs.rowIndex) && (columnIndex == rhs.columnIndex);
}

// Stream I/O
// Reads two ints: row col. Returns true on success, false on failure.
bool RowColumnClass::readFrom(std::istream &in)
{
  int r;
  int c;
  if (!(in >> r >> c))
  {
    // leave object unchanged
    return false; 
  }

  rowIndex = r;
  columnIndex = c;
  return true;
}

// Writes "row col".
void RowColumnClass::writeTo(std::ostream &out) const
{
  out << rowIndex << ' ' << columnIndex;
}
