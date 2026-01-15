#include "ColorClass.h"
#include "clipIntToRange.h"
#include "constants.h"
#include <iostream>
using namespace std;

/*
 * File: ColorClass.cpp
 * Name: 
 * UniqueID: 
 * UMID: 
 * Date: 11/13/2025
 *
 * Purpose:
 *   Implementation of ColorClass. Keeps channels in
 *   [MIN_COLOR_VALUE, MAX_COLOR_VALUE] via clipIntToRange().
 */

// Constructors
// Default
ColorClass::ColorClass()
  : redVal(MAX_COLOR_VALUE), greenVal(MAX_COLOR_VALUE), blueVal(MAX_COLOR_VALUE)
{
}

// With Values
ColorClass::ColorClass(int inRed, int inGreen, int inBlue)
{
  setTo(inRed, inGreen, inBlue);
}

// Standard colors
// Full black RGB(0, 0, 0)
void ColorClass::setToBlack()
{
  redVal = MIN_COLOR_VALUE;
  greenVal = MIN_COLOR_VALUE;
  blueVal = MIN_COLOR_VALUE;
}

// Full red RGB(255, 0, 0)
void ColorClass::setToRed()
{
  redVal = MAX_COLOR_VALUE;
  greenVal = MIN_COLOR_VALUE;
  blueVal = MIN_COLOR_VALUE;
}

// Full green RGB(0, 255, 0)
void ColorClass::setToGreen()
{
  redVal = MIN_COLOR_VALUE;
  greenVal = MAX_COLOR_VALUE;
  blueVal = MIN_COLOR_VALUE;
}

// Full blue RGB(0, 0, 255)
void ColorClass::setToBlue()
{
  redVal = MIN_COLOR_VALUE;
  greenVal = MIN_COLOR_VALUE;
  blueVal = MAX_COLOR_VALUE;
}

// Full white RGB(255, 255, 255)
void ColorClass::setToWhite()
{
  redVal = MAX_COLOR_VALUE;
  greenVal = MAX_COLOR_VALUE;
  blueVal = MAX_COLOR_VALUE;
}

// Mutators
// Set to provided values
// Set to (r, g, b) with clipping;
// returns true (clipping applied if needed)
bool ColorClass::setTo(const int inRed, const int inGreen, const int inBlue)
{
  redVal = clipIntToRange(inRed, MIN_COLOR_VALUE, MAX_COLOR_VALUE);
  greenVal = clipIntToRange(inGreen, MIN_COLOR_VALUE, MAX_COLOR_VALUE);
  blueVal = clipIntToRange(inBlue, MIN_COLOR_VALUE, MAX_COLOR_VALUE);
  return true;
}

// Copy from other ColorClass (always succeeds);
// returns true.
bool ColorClass::setTo(const ColorClass &inColor)
{
  redVal = inColor.redVal;
  greenVal = inColor.greenVal;
  blueVal = inColor.blueVal;
  return true;
}

// Add given value(rhs) to rgb, if out of bound clipping will happen;
// returns true (clipping applied if needed)
bool ColorClass::addColor(const ColorClass &rhs)
{
  redVal = clipIntToRange(redVal + rhs.redVal, 
    MIN_COLOR_VALUE, MAX_COLOR_VALUE);
  greenVal = clipIntToRange(greenVal + rhs.greenVal,
    MIN_COLOR_VALUE, MAX_COLOR_VALUE);
  blueVal = clipIntToRange(blueVal + rhs.blueVal,
    MIN_COLOR_VALUE, MAX_COLOR_VALUE);
  return true;
}

// Multiply given value (adjFactor) to rgb, if out of bound clipping will 
// happen; return true (clipping applied if needed).
bool ColorClass::adjustBrightness(const double adjFactor)
{
  // Scale then clip; truncation via static_cast<int>.
  int newRed = static_cast<int>(redVal * adjFactor);
  int newGreen = static_cast<int>(greenVal * adjFactor);
  int newBlue = static_cast<int>(blueVal * adjFactor);

  redVal = clipIntToRange(newRed, MIN_COLOR_VALUE, MAX_COLOR_VALUE);
  greenVal = clipIntToRange(newGreen, MIN_COLOR_VALUE, MAX_COLOR_VALUE);
  blueVal = clipIntToRange(newBlue, MIN_COLOR_VALUE, MAX_COLOR_VALUE);
  return true;
}

// Accessors
// Return red values
int ColorClass::getRed() const
{
  return redVal;
}

// Return green values
int ColorClass::getGreen() const
{
  return greenVal;
}

// Return blue values
int ColorClass::getBlue() const
{
  return blueVal;
}

// Comparison color A equals to color B or not;
// return true if color is the same
bool ColorClass::isEqual(const ColorClass &rhs) const
{
  return (redVal == rhs.redVal) && (greenVal == rhs.greenVal)
    && (blueVal == rhs.blueVal);
}

// Pixel I/O
// Read 3 ints r g b; 
// returns true on success, false on fail
bool ColorClass::readFrom(std::istream &in)
{
  int r;
  int g;
  int b;
  if (!(in >> r >> g >> b))
  {
    // Check if pixel data exists and can be read
    cout << "Error: Unexpected end-of-file or none integer data\n";
    return false;
  }
  // Validate color component range
  if (r < MIN_COLOR_VALUE || r > MAX_COLOR_VALUE 
    || g < MIN_COLOR_VALUE || g > MAX_COLOR_VALUE 
    || b < MIN_COLOR_VALUE || b > MAX_COLOR_VALUE)
  {
    cout << "Error: Pixel component out of range\n";
    return false;
  }
  setTo(r, g, b);
  return true;
}

// Write "r g b"
void ColorClass::writeTo(std::ostream &out) const
{
  out << redVal << ' ' << greenVal << ' ' << blueVal;
}
