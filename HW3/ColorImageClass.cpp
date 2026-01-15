#include "ColorImageClass.h"
#include <iostream>
#include <new> 
using namespace std;

/*
 * File: ColorImageClass.cpp
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 *
 * Purpose:
 *   Implementation of ColorImageClass using a 2D dynamic array of
 *   ColorClass. Supports P3 PPM I/O and pixel-level operations.
 */

// Private helpers
// Allocate a rows x cols 2D array (uninitialized). Returns false on failure.
bool ColorImageClass::allocPixels(int rows, int cols)
{
  // allocate row pointer array
  pixels = new (std::nothrow) ColorClass *[rows];
  if (pixels == NULL)
  {
    return false;
  }

  // allocate each row
  for (int r = 0; r < rows; r++)
  {
    pixels[r] = new (std::nothrow) ColorClass[cols];
    if (pixels[r] == NULL)
    {
      // clean up rows already allocated
      for (int i = 0; i < r; i++)
      {
        delete [] pixels[i];
      }
      delete [] pixels;
      pixels = NULL;
      return false;
    }
  }
  return true;
}

// Release and reset to empty.
void ColorImageClass::freePixels()
{
  if (pixels != NULL)
  {
    for (int r = 0; r < numRows; r++)
    {
      delete [] pixels[r];
    }
    delete [] pixels;
  }
  pixels = NULL;
  numRows = DEFAULT_INDEX;
  numCols = DEFAULT_INDEX;
}

// Disable zero/negative sizes quickly.
bool ColorImageClass::validSize(int rows, int cols) const
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

// Copy from another image (assumes this is already empty).
bool ColorImageClass::deepCopyFrom(const ColorImageClass &src)
{
  // copy an empty image
  if (src.pixels == NULL || src.numRows <= DEFAULT_INDEX 
    || src.numCols <= DEFAULT_INDEX)
  {
    // ensure this is empty
    freePixels();
    return true;
  }

  // allocate
  if (!allocPixels(src.numRows, src.numCols))
  {
    return false;
  }

  // now set dimensions and copy pixels
  numRows = src.numRows;
  numCols = src.numCols;

  for (int r = 0; r < numRows; r++)
  {
    for (int c = 0; c < numCols; c++)
    {
      pixels[r][c] = src.pixels[r][c];
    }
  }
  return true;
}

// Default
// empty image: 0x0, pixels==NULL
ColorImageClass::ColorImageClass()
{
  numRows = DEFAULT_INDEX;
  numCols = DEFAULT_INDEX;
  pixels = NULL;
}

// Deep copy
ColorImageClass::ColorImageClass(const ColorImageClass &rhs)
{
  numRows = DEFAULT_INDEX;
  numCols = DEFAULT_INDEX;
  pixels = NULL;
  // if alloc fails, remains empty
  (void)deepCopyFrom(rhs); 
}

// Copy assignment (deep copy; self-assignment safe)
ColorImageClass &ColorImageClass::operator=(const ColorImageClass &rhs)
{
  if (this == &rhs)
  {
    return *this;
  }

  // clear current storage then copy
  freePixels();
  if (!deepCopyFrom(rhs))
  {
    // on failure, leave as empty image
    // (numRows/numCols/pixels already reset by freePixels)
  }
  return *this;
}

// Destructor
ColorImageClass::~ColorImageClass()
{
  freePixels();
}

// Getter Functions
// Return number of rows
int ColorImageClass::getRows() const
{
  return numRows;
}

// Return number of columns
int ColorImageClass::getCols() const
{
  return numCols;
}

// If is empty return true; else return false
bool ColorImageClass::isEmpty() const
{
  return (pixels == NULL) || (numRows == DEFAULT_INDEX)
    || (numCols == DEFAULT_INDEX);
}

// Initializes all pixels to given value
bool ColorImageClass::initializeTo(int rows,
  int cols, const ColorClass &fillColor)
{
  if (!validSize(rows, cols))
  {
    return false;
  }

  // release old, allocate new
  freePixels();
  if (!allocPixels(rows, cols))
  {
    return false;
  }

  // set dimensions and fill
  numRows = rows;
  numCols = cols;

  for (int r = 0; r < numRows; r++)
  {
    for (int c = 0; c < numCols; c++)
    {
      pixels[r][c] = fillColor;
    }
  }
  return true;
}

// Boundary check
bool ColorImageClass::isInBounds(const RowColumnClass &loc) const
{
  int r = loc.getRow();
  int c = loc.getCol();
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

// Set the pixel at inRowCol to inColor;
// return false if it is out of bounds
bool ColorImageClass::setColorAtLocation(const RowColumnClass &loc,
  const ColorClass &inColor)
{
  if (!isInBounds(loc))
  {
    return false;
  }
  pixels[loc.getRow()][loc.getCol()] = inColor;
  return true;
}

// Get the pixel at inRowCol into outColor;
// return false if it is out of bounds
bool ColorImageClass::getColorAtLocation(const RowColumnClass &loc,
  ColorClass &outColor) const
{
  if (!isInBounds(loc))
  {
    return false;
  }
  outColor = pixels[loc.getRow()][loc.getCol()];
  return true;
}

// Safe helper to paint a single pixel if in-bounds; returns true if painted.
bool ColorImageClass::paintIfInBounds(const RowColumnClass &loc,
  const ColorClass &color)
{
  if (!isInBounds(loc))
  {
    return false;
  }
  pixels[loc.getRow()][loc.getCol()] = color;
  return true;
}

void ColorImageClass::clear()
{
  freePixels();
}

// PPM I/O
// Read image from stream containing a P3 PPM.
// Fails if header invalid, sizes out of range, max color != 255, or stream
// extraction fails. On success replaces current image.
bool ColorImageClass::readFromPPM(std::istream &in)
{
  // Check if the input stream is valid/open
  if (!in.good())
  {
    cout << "Error: input stream is not ready/open\n";
    return false;
  }

  // Always start by clearing current content
  freePixels();

  // Read and validate the magic number
  char magic[MAGIC_LENGTH];
  if (!(in >> magic))
  {
    cout << "Error: Failed to read magic number from PPM file\n";
    return false;
  }

  if (!(magic[MAGIC_INDEX_ZERO] == CHAR_P 
    && magic[MAGIC_INDEX_ONE] == CHAR_THREE 
    && magic[MAGIC_INDEX_TWO] == CHAR_END))
  {
    cout << "Error: Invalid magic number\n";

    return false;
  }

  // Read width and height
  int cols;
  int rows;
  in >> std::ws;
  if (!(in >> cols >> rows))
  {
    cout << "Error: Failed to read image width and height\n";
    return false;
  }

  // Validate dimension range (1,2000)
  if (!validSize(rows, cols))
  {
    cout << "Error: Invalid image dimensions\n";
    return false;
  }

  // Read and validate the max color value
  int maxColor;
  if (!(in >> maxColor))
  {
    cout << "Error: Failed to read max color value\n";
    return false;
  }
  if (maxColor != MAX_COLOR_VALUE)
  {
    cout << "Error: Invalid max color value\n";
    return false;
  }

  // Allocate dynamic memory for pixels
  if (!allocPixels(rows, cols))
  {
    cout << "Error: Unable to allocate memory for image of size\n";
    return false;
  }
  numRows = rows;
  numCols = cols;

  // read pixels row-major
  for (int r = 0; r < numRows; r++)
  {
    for (int c = 0; c < numCols; c++)
    {
      ColorClass tmp;

      if (!tmp.readFrom(in))
      {
        freePixels(); // rollback
        return false;
      }

      pixels[r][c] = tmp;
    }
  }

  // Check for extra pixel data beyond expected count
  int extraInt;
  if (in >> extraInt)
  {
    cout << "Error: Extra pixel data in PPM file after expected\n";
    freePixels();
    return false;
  }

  // Check for unreadable garbage data near EOF
  if (!in.eof())
  {
    cout << "Error: Unreadable extra data in PPM file near end-of-file\n";
    freePixels();
    return false;
  }

  return true;
}

// Write as P3 PPM to stream. Returns false if image is empty or stream bad.
bool ColorImageClass::writeToPPM(std::ostream &out) const
{
  if (isEmpty())
  {
    return false;
  }

  // header: P3\n<width> <height>\n<max>\n
  out << CHAR_P << CHAR_THREE << '\n';
  out << numCols << ' ' << numRows << '\n';
  out << MAX_COLOR_VALUE << '\n';

  // body
  for (int r = 0; r < numRows; r++)
  {
    for (int c = 0; c < numCols; c++)
    {
      pixels[r][c].writeTo(out);
      // Check the stream after writing
      if (out.fail())
      {
        cout << "Error: failed to write data\n";
      }

      if (c < numCols - 1)
      {
        out << ' ';
      }

      if (out.fail())
      {
        cout << "Error: Failed to write space after pixel\n";
        return false;
      }
    }

    out << '\n';
    if (out.fail())
    {
      cout << "Error: Failed to write newline after row\n";
      return false;
    }

  }
  return true;
}
