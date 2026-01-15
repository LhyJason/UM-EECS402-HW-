#ifndef COLORCLASS_H
#define COLORCLASS_H

#include <iosfwd>
#include "constants.h"

/*
 * File: ColorClass.h
 * Name: 
 * UniqueID: 
 * UMID: 
 * Date: 11/13/2025
 *
 * Purpose:
 * Class representing an RGB color with integer numbers.
 * Colors valid range [MIN_COLOR_VALUE, MAX_COLOR_VALUE].
 * This class handles reading/writing its own RGB triple for PPM pixel I/O.
 */

class ColorClass
{
private:
  // Data members
  int redVal;
  int greenVal;
  int blueVal;

public:
  // Constructors
  // Default 
  ColorClass();

  // With Values
  ColorClass(const int inRed, const int inGreen, const int inBlue);

  // Standard colors
  // Full black RGB(0, 0, 0)
  void setToBlack();

  // Full red RGB(255, 0, 0) 
  void setToRed();

  // Full green RGB(0, 255, 0)  
  void setToGreen();

  // Full blue RGB(0, 0, 255) 
  void setToBlue();

  // Full white RGB(255, 255, 255)  
  void setToWhite();

  // Mutators
  // Set to provided values
  // Set to (r, g, b) with clipping;
  // returns true (clipping applied if needed)
  bool setTo(const int inRed, const int inGreen, const int inBlue);

  // Copy from other ColorClass (always succeeds);
  // returns true.
  bool setTo(const ColorClass &inColor);

  // Add given value(rhs) to rgb, if out of bound clipping will happen;
  // returns true (clipping applied if needed)
  bool addColor(const ColorClass &rhs);

  // Multiply given value (adjFactor) to rgb, if out of bound clipping will 
  // happen; return true (clipping applied if needed).
  bool adjustBrightness(const double adjFactor);

  // Accessors
  // Return red values
  int getRed() const;

  // Return green values
  int getGreen() const;

  // Return blue values
  int getBlue() const;

  // Comparison color A equals to color B or not;
  // return true if color is the same
  bool isEqual(const ColorClass &rhs) const;

  // Pixel I/O
  // Read 3 ints r g b; 
  // returns true on success, false on fail
  bool readFrom(std::istream &in);

  // Write "r g b"
  void writeTo(std::ostream &out) const;
};

#endif // COLORCLASS_H
