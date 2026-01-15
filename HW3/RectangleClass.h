#ifndef RECTANGLECLASS_H
#define RECTANGLECLASS_H

#include "ColorClass.h"
#include "RowColumnClass.h"
class ColorImageClass;

/*
 * File: RectangleClass.h
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 *
 * Purpose:
 *   Represents a rectangular region defined by top-left and bottom-right
 *   coordinates, and provides methods to draw the rectangle (outline or filled)
 *   onto a ColorImageClass object.
 */

class RectangleClass
{
private:
  // Top-left corner
  RowColumnClass upperLeft;
  
  // Bottom-right corner  
  RowColumnClass lowerRight;
  
  // Rectangle color
  ColorClass rectColor;   
  
  // Return true if filled, else outline only
  bool filled;                 

  // Valid if lowerRight is at or after upperLeft.
  bool isValidRectangle() const;

public:
  // Default constructor
  RectangleClass();

  // Construct with given corners and color
  RectangleClass(const RowColumnClass &inUpperLeft, 
    const RowColumnClass &inLowerRight, const ColorClass &inColor, 
    bool inFilled);

  // Setters
  // Set corners to location
  void setCorners(const RowColumnClass &inUpperLeft, 
    const RowColumnClass &inLowerRight);
  
  // Set color to given color
  void setColor(const ColorClass &inColor);

  // Set rectangle as filled
  void setFilled(bool inFilled);

  // Draw rectangle onto image. Returns true if any pixel drawn.
  bool drawOnImage(ColorImageClass &image) const;

  // Accessors
  // Return upper left
  RowColumnClass getUpperLeft() const;

  // Return lower right
  RowColumnClass getLowerRight() const;

  // Return color
  ColorClass getColor() const;

  // Return true if filled, else return false
  bool isFilled() const;
};

#endif // RECTANGLECLASS_H
