#ifndef COLORIMAGECLASS_H
#define COLORIMAGECLASS_H

#include <iosfwd>
#include "constants.h"
#include "ColorClass.h"
#include "RowColumnClass.h"

/*
 * File: ColorImageClass.h
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 *
 * Purpose:
 *   Stores a PPM image (P3 format) as a 2D dynamic array of ColorClass
 *   objects. Provides pixel-level access, bounds checks, and PPM I/O.
 */

class ColorImageClass
{
private:
  // Data Members
  int numRows;
  int numCols;
  // pixels[row][col]
  ColorClass **pixels;  

  // Allocate a rows x cols 2D array (uninitialized). Returns false on failure.
  bool allocPixels(int rows, int cols);

  // Release and reset to empty.
  void freePixels();

  // Disable zero/negative sizes quickly.
  bool validSize(int rows, int cols) const;

  // Copy from another image (assumes this is already empty).
  bool deepCopyFrom(const ColorImageClass &src);

public:
  // Default
  // empty image: 0x0, pixels==NULL
  ColorImageClass();    

  // Deep copy                  
  ColorImageClass(const ColorImageClass &rhs);

  // Copy assignment (deep copy; self-assignment safe)
  ColorImageClass &operator=(const ColorImageClass &rhs); 

  // Destructor
  ~ColorImageClass();

  // Getter Functions
  int getRows() const;
  int getCols() const;

  // If is empty return true; else return false
  bool isEmpty() const; 

  // Initializes all pixels to given value
  bool initializeTo(int rows, int cols, const ColorClass &fillColor);

  // Boundary check
  bool isInBounds(const RowColumnClass &loc) const;

  // Set the pixel at inRowCol to inColor;
  // return false if it is out of bounds
  bool setColorAtLocation(const RowColumnClass &loc, const ColorClass &inColor);

  // Get the pixel at inRowCol into outColor;
  // return false if it is out of bounds
  bool getColorAtLocation(const RowColumnClass &loc, 
    ColorClass &outColor) const;

  // PPM I/O
  // Read image from stream containing a P3 PPM.
  // Fails if header invalid, sizes out of range, max color != 255, or stream
  // extraction fails. On success replaces current image.
  bool readFromPPM(std::istream &in);

  // Write as P3 PPM to stream. Returns false if image is empty or stream bad.
  bool writeToPPM(std::ostream &out) const;

  // Utilities for operations to come (rect/pattern/insert)
  // Safe helper to paint a single pixel if in-bounds; returns true if painted.
  bool paintIfInBounds(const RowColumnClass &loc, const ColorClass &color);

  // Clear to empty (0x0, pixels==NULL).
  void clear();
};

#endif // COLORIMAGECLASS_H
