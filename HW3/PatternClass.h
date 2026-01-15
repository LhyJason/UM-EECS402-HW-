#ifndef PATTERNCLASS_H
#define PATTERNCLASS_H

#include <iosfwd>
#include "RowColumnClass.h"
#include "ColorClass.h"

/*
 * File: PatternClass.h
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 *
 * Purpose:
 *   Stores a binary pattern (0 = off, 1 = on) as a 2D dynamic array.
 *   Can be applied onto a ColorImageClass by painting pixels where
 *   the pattern has 1's, offset by a specified top-left location.
 */

class ColorImageClass;

class PatternClass
{
private:
  // Data Members
  int numRows;
  int numCols;
  // mask[row][col], values are 0 or 1
  int **mask;          

  // Allocate rows x cols (uninitialized). Returns false on failure.
  bool allocMask(int rows, int cols);

  // Release storage and reset to empty.
  void freeMask();

  // Validate that rows and cols are within [MIN_DIMENSION, MAX_DIMENSION].
  bool validSize(int rows, int cols) const;

  // Deep copy from src (this must be empty beforehand).
  bool deepCopyFrom(const PatternClass &src);

public:
  // Default
  // empty pattern: 0x0, mask==NULL
  PatternClass();   

  // Deep copy                      
  PatternClass(const PatternClass &rhs);

  // Copy assignment
  PatternClass &operator=(const PatternClass &rhs);

  // Destructor
  ~PatternClass();

  // Getter Functions
  // Return number of rows
  int getRows() const;

  // Return number of columns
  int getCols() const;

  // If is empty return true; else return false
  bool isEmpty() const;

  // Initialization / I/O
  // Initialize as rows x cols and fill with fillVal (0 or 1). False on fail.
  bool initializeTo(int rows, int cols, int fillVal);

  // Read: expects "rows cols" then rows*cols integers (0 or 1).
  // On success replace current content; on failure leave unchanged.
  bool readFrom(std::istream &in);

  // Write: rows cols then the grid.
  void writeTo(std::ostream &out) const;

  // Accessors
  // Returns true if (row,col) inside the pattern.
  bool isInBounds(const RowColumnClass &relLoc) const;

  // Get value at relative location (0/1). Returns false if out of bounds.
  bool getValueAt(const RowColumnClass &relLoc, int &outVal) const;

  // Paints 'color' on every 1-cell of the pattern placed with its top-left
  // at 'topLeft' in the image. Returns true if at least one pixel is painted.
  bool applyToImage(ColorImageClass &image, const RowColumnClass &topLeft,
      const ColorClass &color) const;

  // Clear to empty.
  void clear();
};

#endif // PATTERNCLASS_H
