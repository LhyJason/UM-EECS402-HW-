#include "RectangleClass.h"
#include "ColorImageClass.h"
#include "constants.h"
/*
 * File: RectangleClass.cpp
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 *
 * Purpose:
 *   Implementation of RectangleClass. Draws filled or outline rectangles
 *   on a ColorImageClass using safe pixel painting.
 */

// Private helpers
// Valid if lowerRight is at or after upperLeft.
bool RectangleClass::isValidRectangle() const
{
  // lowerRight must be at or below and at or to the right of upperLeft
  if (lowerRight.getRow() < upperLeft.getRow())
  {
    return false;
  }
  if (lowerRight.getCol() < upperLeft.getCol())
  {
    return false;
  }
  return true;
}

// Constructors
// Default constructor
RectangleClass::RectangleClass()
  : upperLeft(DEFAULT_LOCATION, DEFAULT_LOCATION), 
    lowerRight(DEFAULT_LOCATION, DEFAULT_LOCATION), rectColor(), filled(false)
{
}

// Construct with given corners and color
RectangleClass::RectangleClass(const RowColumnClass &inUpperLeft, 
  const RowColumnClass &inLowerRight, const ColorClass &inColor, bool inFilled)
  : upperLeft(inUpperLeft), lowerRight(inLowerRight), rectColor(inColor), 
    filled(inFilled)
{
}

// Setters
// Set corners to location
void RectangleClass::setCorners(const RowColumnClass &inUpperLeft, 
  const RowColumnClass &inLowerRight)
{
  upperLeft = inUpperLeft;
  lowerRight = inLowerRight;
}

// Set color to given color
void RectangleClass::setColor(const ColorClass &inColor)
{
  rectColor = inColor;
}

// Set rectangle as filled
void RectangleClass::setFilled(bool inFilled)
{
  filled = inFilled;
}

// Accessors
// Return upper left
RowColumnClass RectangleClass::getUpperLeft() const
{
  return upperLeft;
}

// Return lower right
RowColumnClass RectangleClass::getLowerRight() const
{
  return lowerRight;
}

// Return color
ColorClass RectangleClass::getColor() const
{
  return rectColor;
}

// Return true if filled, else return false
bool RectangleClass::isFilled() const
{
  return filled;
}

// Draw rectangle onto image. Returns true if any pixel drawn.
bool RectangleClass::drawOnImage(ColorImageClass &image) const
{
  if (!isValidRectangle())
  {
    // Invalid geometry: nothing drawn.
    return false;
  }

  bool paintedAny = false;

  // Coordinates (inclusive)
  int topRow = upperLeft.getRow();
  int leftCol = upperLeft.getCol();
  int botRow = lowerRight.getRow();
  int rightCol = lowerRight.getCol();

  if (filled)
  {
    // Paint all pixels in the rectangle area
    for (int r = topRow; r <= botRow; r++)
    {
      for (int c = leftCol; c <= rightCol; c++)
      {
        RowColumnClass loc(r, c);
        if (image.paintIfInBounds(loc, rectColor))
        {
          paintedAny = true;
        }
      }
    }
  }
  else
  {
    // Outline: paint top and bottom edges
    int c;

    // Top edge
    int rTop = topRow;
    for (c = leftCol; c <= rightCol; c++)
    {
      RowColumnClass loc(rTop, c);
      if (image.paintIfInBounds(loc, rectColor))
      {
        paintedAny = true;
      }
    }

    // Bottom edge (only if height >= 1)
    int rBot = botRow;
    if (rBot != rTop)
    {
      for (c = leftCol; c <= rightCol; c++)
      {
        RowColumnClass loc(rBot, c);
        if (image.paintIfInBounds(loc, rectColor))
        {
          paintedAny = true;
        }
      }
    }

    // Left and right edges
    int cLeft = leftCol;
    int cRight = rightCol;

    for (int r = topRow; r <= botRow; r++)
    {
      // Left edge
      RowColumnClass locL(r, cLeft);
      if (image.paintIfInBounds(locL, rectColor))
      {
        paintedAny = true;
      }

      // Right edge (only if width >= 1)
      if (cRight != cLeft)
      {
        RowColumnClass locR(r, cRight);
        if (image.paintIfInBounds(locR, rectColor))
        {
          paintedAny = true;
        }
      }
    }
  }

  return paintedAny;
}
