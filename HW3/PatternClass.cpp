#include "PatternClass.h"
#include "ColorImageClass.h"   
#include "constants.h"         
#include <iostream>
#include <new>
using namespace std;

/*
 * File: PatternClass.cpp
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 *
 * Purpose:
 *   Implementation of PatternClass. Stores a binary (0/1) 2D mask and
 *   applies it to an image with bounds-safe painting.
 */

// Private helpers
// Allocate rows x cols (uninitialized). Returns false on failure.
bool PatternClass::allocMask(int rows, int cols)
{
  mask = new (std::nothrow) int *[rows];
  if (mask == NULL)
  {
    return false;
  }

  for (int r = 0; r < rows; r++)
  {
    mask[r] = new (std::nothrow) int[cols];
    if (mask[r] == NULL)
    {
      for (int i = 0; i < r; i++)
      {
        delete [] mask[i];
      }
      delete [] mask;
      mask = NULL;
      return false;
    }
  }
  return true;
}

// Release storage and reset to empty.
void PatternClass::freeMask()
{
  if (mask != NULL)
  {
    for (int r = 0; r < numRows; r++)
    {
      delete [] mask[r];
    }
    delete [] mask;
  }
  mask = NULL;
  numRows = DEFAULT_INDEX;
  numCols = DEFAULT_INDEX;
}

// Validate that rows and cols are within [MIN_DIMENSION, MAX_DIMENSION].
bool PatternClass::validSize(int rows, int cols) const
{
  if (rows < MIN_DIMENSION || rows > MAX_DIMENSION)
  {
    return false;
  }
  if (cols < MIN_DIMENSION || cols > MAX_DIMENSION)
  {
    return false;
  }
  return true;
}

// Deep copy from src (this must be empty beforehand).
bool PatternClass::deepCopyFrom(const PatternClass &src)
{
  // Treat any missing storage or non-positive size as empty.
  if (src.mask == NULL || src.numRows <= DEFAULT_INDEX 
    || src.numCols <= DEFAULT_INDEX)
  {
    freeMask();
    return true;
  }

  if (!allocMask(src.numRows, src.numCols))
  {
    return false;
  }
  numRows = src.numRows;
  numCols = src.numCols;

  for (int r = 0; r < numRows; r++)
  {
    for (int c = 0; c < numCols; c++)
    {
      mask[r][c] = src.mask[r][c];
    }
  }
  return true;
}

// Default
// empty pattern: 0x0, mask==NULL
PatternClass::PatternClass()
{
  numRows = DEFAULT_INDEX;
  numCols = DEFAULT_INDEX;
  mask = NULL;
}

// Deep copy
PatternClass::PatternClass(const PatternClass &rhs)
{
  numRows = DEFAULT_INDEX;
  numCols = DEFAULT_INDEX;
  mask = NULL;
  (void)deepCopyFrom(rhs); // if alloc fails, remains empty
}

// Copy assignment
PatternClass &PatternClass::operator=(const PatternClass &rhs)
{
  if (this == &rhs)
  {
    return *this;
  }
  freeMask();
  if (!deepCopyFrom(rhs))
  {
    // leave as empty on failure
  }
  return *this;
}

// Destructor
PatternClass::~PatternClass()
{
  freeMask();
}

// Getter Functions
// Return number of rows
int PatternClass::getRows() const
{
  return numRows;
}

// Return number of columns
int PatternClass::getCols() const
{
  return numCols;
}

// If is empty return true; else return false
bool PatternClass::isEmpty() const
{
  return (mask == NULL) || (numRows == DEFAULT_INDEX) 
    || (numCols == DEFAULT_INDEX);
}

// Initialization / I/O
// Initialize as rows x cols and fill with fillVal (0 or 1). False on fail.
bool PatternClass::initializeTo(int rows, int cols, int fillVal)
{
  if (!validSize(rows, cols))
  {
    return false;
  }
  if (!(fillVal == FILL_VALUE_ZERO || fillVal == FILL_VALUE_ONE))
  {
    return false;
  }

  freeMask();
  if (!allocMask(rows, cols))
  {
    return false;
  }
  numRows = rows;
  numCols = cols;

  for (int r = 0; r < numRows; r++)
  {
    for (int c = 0; c < numCols; c++)
    {
      mask[r][c] = fillVal;
    }
  }
  return true;
}

// Read: expects "rows cols" then rows*cols integers (0 or 1).
// On success replace current content; on failure leave unchanged.
bool PatternClass::readFrom(std::istream &in)
{
    // Check if the input stream is valid/open
  if (!in.good())
  {
    cout << "Error: input pattern is not open\n";
    return false;
  }
  // Read header (rows cols) into locals, leave object unchanged on failure.
  int rows;
  int cols;
  if (!(in >> cols >> rows))
  {
    cout << "Error: Failed to read pattern dimensions\n";
    return false;
  }
  if (!validSize(rows, cols))
  {
    cout << "Error: Invalid pattern dimensions\n";
    return false;
  }

  // Allocate temporary storage
  PatternClass tmp;
  if (!tmp.allocMask(rows, cols))
  {
    cout << "Error: Failed to allocate for pattern of size\n";
    return false;
  }

  int **newMask = new (std::nothrow) int *[rows];
  if (newMask == NULL)
  {
    return false;
  }

  for (int r = 0; r < rows; r++)
  {
    newMask[r] = new (std::nothrow) int[cols];
    if (newMask[r] == NULL)
    {
      for (int i = 0; i < r; i++)
      {
        delete [] newMask[i];
      }
      delete [] newMask;
      return false;
    }
  }

  // Read rows*cols integers (must be 0 or 1)
  for (int r = 0; r < rows; r++)
  {
    for (int c = 0; c < cols; c++)
    {
      int val;
      if (!(in >> val))
      {
        // rollback temp
        cout << "Error: Pattern file ended or contained none integer data\n";
        for (int i = 0; i < rows; i++)
        {
          delete [] newMask[i];
        }
        delete [] newMask;
        return false;
      }
      if (!(val == FILL_VALUE_ZERO || val == FILL_VALUE_ONE))
      {
        cout << "Error: Pattern value not zero or one\n";
        for (int i = 0; i < rows; i++)
        {
          delete [] newMask[i];
        }
        delete [] newMask;
        return false;
      }
      newMask[r][c] = val;
    }
  }

  // Check for extra pixel data beyond expected count
  int extraInt;
  if (in >> extraInt)
  {
    cout << "Error: Extra pixel data in pattern after expected\n";
    return false;
  }

  // Check for unreadable garbage data near EOF
  if (!in.eof())
  {
    cout << "Error: Unreadable extra data in pattern\n";
    return false;
  }

  // Commit: replace current content
  freeMask();
  mask = newMask;
  numRows = rows;
  numCols = cols;
  return true;
}

// Write: rows cols then the grid.
void PatternClass::writeTo(std::ostream &out) const
{
  out << numCols << ' ' << numRows << '\n';

  for (int r = 0; r < numRows; r++)
  {
    for (int c = 0; c < numCols; c++)
    {
      out << mask[r][c];
      if (c < numCols - 1)
      {
        out << ' ';
      }
    }
    out << '\n';
  }
}

// Accessors
// Returns true if (row,col) inside the pattern.
bool PatternClass::isInBounds(const RowColumnClass &relLoc) const
{
  int r = relLoc.getRow();
  int c = relLoc.getCol();
  if (r < DEFAULT_INDEX || r >= numRows)
  {
    return false;
  }
  if (c < DEFAULT_INDEX || c >= numCols)
  {
    return false;
  }
  return true;
}

// Get value at relative location (0/1). Returns false if out of bounds.
bool PatternClass::getValueAt(const RowColumnClass &relLoc, int &outVal) const
{
  if (!isInBounds(relLoc))
  {
    return false;
  }
  outVal = mask[relLoc.getRow()][relLoc.getCol()];
  return true;
}

// Paints 'color' on every 1-cell of the pattern placed with its top-left
// at 'topLeft' in the image. Returns true if at least one pixel is painted.
bool PatternClass::applyToImage(ColorImageClass &image,
    const RowColumnClass &topLeft, const ColorClass &color) const
{
  if (isEmpty())
  {
    return false;
  }

  bool paintedAny = false;
  for (int r = 0; r < numRows; r++)
  {
    for (int c = 0; c < numCols; c++)
    {
      if (mask[r][c] == FILL_VALUE_ONE)
      {
        RowColumnClass loc = topLeft;
        loc.addRowCol(r, c);
        if (image.paintIfInBounds(loc, color))
        {
          paintedAny = true;
        }
      }
    }
  }
  return paintedAny;
}

// Clear to empty.
void PatternClass::clear()
{
  freeMask();
}
