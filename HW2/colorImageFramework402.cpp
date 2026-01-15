#include <iostream>
using namespace std;

/*
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 09/28/2025
 *
 * Purpose:
 * This program implements a simple image framework with three classes:
 * 1. ColorClass: manages RGB values and color operations
 * 2. RowColumnClass: represents row/column coordinates
 * 3. ColorImageClass: manages a 10x18 image of ColorClass pixels
 * 
 * Then user can do operations on image each pixels, color arithmetic,
 * brightness adjustment, image addition, and printing.
 */

// Global constants
const int COLOR_MIN = 0;
const int COLOR_MAX = 1000;
const int IMAGE_NUM_ROWS = 10;
const int IMAGE_NUM_COLS = 18;
const char RED_ABBREV = 'R';
const char GREEN_ABBREV = 'G';
const char BLUE_ABBREV = 'B';
const int DEFAULT_VALUE = -99999;
const char* SYMBOL = "--";

// Global function prototypes

// Class definitions 
class ColorClass
{
  private:
    // Data Members
    int redVal;
    int greenVal;
    int blueVal;

    // Clipping. Smaller than min will be set to min, same as the max side.
    int clipToRange(int value) const;

    // Set to "clipped" (r, g, b). If clipping happened, use new (r, g, b),
    // else use original (r, g, b).
    // Return true if clipping happened.
    bool setAllClipped(const int r, const int g, const int b);

  public:
    // Constructors
    // Default 
    ColorClass();

    // With Values
    ColorClass(const int inRed, const int inGreen, const int inBlue);


    // Standardization of color
    // Full black RGB(0, 0, 0)
    void setToBlack();

    // Full red RGB(1000, 0, 0) 
    void setToRed();

    // Full green RGB(0, 1000, 0)  
    void setToGreen();

    // Full blue RGB(0, 0, 1000) 
    void setToBlue();

    // Full white RGB(1000, 1000, 1000)  
    void setToWhite();

    // Set to provided values
    // Set to (r, g, b) with clipping;
    // return true if clipping happened
    bool setTo(const int inRed, const int inGreen, const int inBlue);

    // Copy from other ColorClass
    // expected always return false
    bool setTo(const ColorClass &inColor);


    // Add given value(rhs) to rgb, if out of bound clipping will happen;
    // return true if clipping happened
    bool addColor(const ColorClass &rhs);

    // Subtract given value(rhs) to rgb, if it out of bound clipping will 
    // happen; return true if clipping happened
    bool subtractColor(const ColorClass &rhs);

    // Multiply given value(adjFactor) to rgb, if out of bound clipping will 
    // happen; return true
    bool adjustBrightness(const double adjFactor);

    // Output with format: "R: <red> G: <green> B: <blue>"
    void printComponentValues() const;

};

class RowColumnClass
{
  private:
    // Data Members
    int inRow;
    int inCol;

  public:
  // Constructors
  // Default 
  RowColumnClass();

  // With Values
  RowColumnClass(const int inRow, const int inCol);


  // Setter functions
  // Set row and column to given values
  void setRowCol(const int inRow, const int inCol);

  // Set row to given values
  void setRow(const int inRow);

  // Set column to given values
  void setCol(const int inCol);

  // Getter functions
  // Return row value
  int getRow() const;

  // Return column value
  int getCol() const;


  // Add row and column index values to its own (newRow = originRow + index)
  void addRowColTo(const RowColumnClass &inRowCol);

  // Print as [row,col] (no newline)
  void printRowCol() const;
};

class ColorImageClass
{
  private:
    // Data Members
    int numRows;
    int numCols;
    ColorClass img[IMAGE_NUM_ROWS][IMAGE_NUM_COLS];

  public:
  // Constructors
  // Default
  ColorImageClass();
  
  // Initializes all pixels to given value
  void initializeTo(const ColorClass &inColor);

  // Add rhs image to this;
  // return true if clipping happened
  bool addImageTo(const ColorImageClass &rhsImg);

  // Set this image to the sum of numImgsToAdd images;
  // return true if clipping happened
  bool addImages(const int numImgsToAdd, const ColorImageClass imagesToAdd []);

  // Set the pixel at inRowCol to inColor;
  // return false if it is out of bounds
  bool setColorAtLocation(const RowColumnClass &inRowCol,
    const ColorClass &inColor);

  // Get the pixel at inRowCol into outColor;
  // return false if it is out of bounds
  bool getColorAtLocation(const RowColumnClass &inRowCol, 
    ColorClass &outColor) const;

  // Print the entire image.
  void printImage() const;
};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);
  ColorImageClass testImage;
  ColorImageClass testImages[3];

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;

  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;

  //Test some basic ColorImageClass operations...
  testColor.setToRed();
  testImage.initializeTo(testColor);

  testRowCol.setRowCol(555, 5);
  cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  testRowCol.setRow(4);
  cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  //Set up an array of images of different colors
  testColor.setToRed();
  testColor.adjustBrightness(0.25);
  testImages[0].initializeTo(testColor);
  testColor.setToBlue();
  testColor.adjustBrightness(0.75);
  testImages[1].initializeTo(testColor);
  testColor.setToGreen();
  testImages[2].initializeTo(testColor);

  //Modify a few individual pixel colors
  testRowCol.setRowCol(4, 2);
  testColor.setToWhite();
  testImages[1].setColorAtLocation(testRowCol, testColor);

  testRowCol.setRowCol(2, 4);
  testColor.setToBlack();
  testImages[2].setColorAtLocation(testRowCol, testColor);

  //Add up all images in testImages array and assign result
  //to the testImage image
  testImage.addImages(3, testImages);
  
  //Check some certain values
  cout << "Added values:" << endl;
  for (int colInd = 0; colInd < 8; colInd += 2)
  {
    testRowCol.setRowCol(4, colInd);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  for (int rowInd = 0; rowInd < 8; rowInd += 2)
  {
    testRowCol.setRowCol(rowInd, 4);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  cout << "Printing entire test image:" << endl;
  testImage.printImage();

  return 0;
}

#endif

// Class method definitions
// 1. ColorClass 
// Clipping. Smaller than min will be set to min, same as the max side.
int ColorClass::clipToRange(int value) const
{
  if (value < COLOR_MIN)
  {
    return COLOR_MIN;
  }
  if (value > COLOR_MAX)
  {
    return COLOR_MAX;
  }
  return value;
}


// Set to "clipped" (r, g, b). If clipping happened, use new (r, g, b),
// else use original (r, g, b).
// Return true if clipping happened.
bool ColorClass::setAllClipped(const int r, const int g, const int b)
{
  int newRed = clipToRange(r);
  int newGreen = clipToRange(g);
  int newBlue = clipToRange(b);

  bool wasClipped = (r != newRed) || (g != newGreen) || (b != newBlue);

  redVal = newRed;
  greenVal = newGreen;
  blueVal = newBlue;

  return wasClipped;
}

// Default
ColorClass::ColorClass()
{
  // Initializes to white
  redVal = COLOR_MAX;
  greenVal = COLOR_MAX;
  blueVal = COLOR_MAX;
}

// With Values
ColorClass::ColorClass(const int inRed, const int inGreen, const int inBlue)
{
  redVal = clipToRange(inRed);
  greenVal = clipToRange(inGreen);
  blueVal = clipToRange(inBlue);
}

// Full black RGB(0, 0, 0)
void ColorClass::setToBlack()
{
  redVal = COLOR_MIN;
  greenVal = COLOR_MIN;
  blueVal = COLOR_MIN;
}

// Full red RGB(1000, 0, 0)
void ColorClass::setToRed()
{
  redVal = COLOR_MAX;
  greenVal = COLOR_MIN;
  blueVal = COLOR_MIN;
}

// Full green RGB(0, 1000, 0)
void ColorClass::setToGreen()
{
  redVal = COLOR_MIN;
  greenVal = COLOR_MAX;
  blueVal = COLOR_MIN;
}

// Full blue RGB(0, 0, 1000)
void ColorClass::setToBlue()
{
  redVal = COLOR_MIN;
  greenVal = COLOR_MIN;
  blueVal = COLOR_MAX;
}

// Full white RGB(1000, 1000, 1000)
void ColorClass::setToWhite()
{
  redVal = COLOR_MAX;
  greenVal = COLOR_MAX;
  blueVal = COLOR_MAX;
}

// Set to (r, g, b) with clipping; return true if clipping happened
bool ColorClass::setTo(const int inRed, const int inGreen, const int inBlue)
{
  return setAllClipped(inRed, inGreen, inBlue);
}

// Copy from other ColorClass; expected always return false
bool ColorClass::setTo(const ColorClass &inColor)
{
  redVal = inColor.redVal;
  greenVal = inColor.greenVal;
  blueVal = inColor.blueVal;

  return false;
}

// Add rhs; return true if clipping happened
bool ColorClass::addColor(const ColorClass &rhs)
{
  int addRed = redVal + rhs.redVal;
  int addGreen = greenVal + rhs.greenVal;
  int addBlue = blueVal + rhs.blueVal;

  return setAllClipped(addRed, addGreen, addBlue);
}

// Subtract rhs; return true if clipping happened
bool ColorClass::subtractColor(const ColorClass &rhs)
{
  int subRed = redVal - rhs.redVal;
  int subGreen = greenVal - rhs.greenVal;
  int subBlue = blueVal - rhs.blueVal;

  return setAllClipped(subRed, subGreen, subBlue);
}

// Multiply by adjFactor; return true if clipping happened
bool ColorClass::adjustBrightness(const double adjFactor)
{
  int newRed = static_cast<int>(redVal * adjFactor);
  int newGreen = static_cast<int>(greenVal * adjFactor);
  int newBlue = static_cast<int>(blueVal * adjFactor);
  
  return setAllClipped(newRed, newGreen, newBlue);
}

// Output: "R: <red> G: <green> B: <blue>" (no newline)
void ColorClass::printComponentValues() const
{
  cout << RED_ABBREV << ": " << redVal << " "
  << GREEN_ABBREV << ": " << greenVal << " "
  << BLUE_ABBREV << ": " << blueVal;
}



// 2. RowColumnClass
// Default
RowColumnClass::RowColumnClass()
{
  // Default values set as -99999
  inRow = DEFAULT_VALUE;
  inCol = DEFAULT_VALUE;
}

// With Values
RowColumnClass::RowColumnClass(const int inRow, const int inCol)
{
  this->inRow = inRow;
  this->inCol = inCol;
}

// Set row and column to given values
void RowColumnClass::setRowCol(const int inRow, const int inCol)
{
  this->inRow = inRow;
  this->inCol = inCol;
}

// Set row
void RowColumnClass::setRow(const int inRow)
{
  this->inRow = inRow;
}

// Set col
void RowColumnClass::setCol(const int inCol)
{
  this->inCol = inCol;
}

// Return row value
int RowColumnClass::getRow() const
{
  return inRow;
}

// Return column value
int RowColumnClass::getCol() const
{
  return inCol;
}

// Add other's row/col to this one
void RowColumnClass::addRowColTo(const RowColumnClass &inRowCol)
{
  inRow += inRowCol.getRow();
  inCol += inRowCol.getCol();
}

// Print as [row,col] (no newline)
void RowColumnClass::printRowCol() const
{
  cout << "[" << inRow << "," << inCol << "]";
}



// 3. ColorImageClass
// Default
ColorImageClass::ColorImageClass()
{
  // Standardization
  numRows = IMAGE_NUM_ROWS;
  numCols = IMAGE_NUM_COLS;

  // Initializes to black
  ColorClass black;
  black.setToBlack();
  initializeTo(black);
}

// Initializes all pixels to given value
void ColorImageClass::initializeTo(const ColorClass &inColor)
{
  for (int i = 0; i < numRows; i++)
  {
    for (int j = 0; j < numCols; j++)
    {
      img[i][j].setTo(inColor);
    }
  }
}

// Add rhs image to this; return true if clipping happened
bool ColorImageClass::addImageTo(const ColorImageClass &rhsImg)
{
  bool flag = false;
  for (int i = 0; i < numRows; i++)
  {
    for (int j = 0; j < numCols; j++)
    {
      if (img[i][j].addColor(rhsImg.img[i][j]))
      {
        flag = true;
      }
    }
  }
  return flag;
}

// Set this image to the sum of numImgsToAdd images;
// return true if clipping happened
bool ColorImageClass::addImages(const int numImgsToAdd,
  const ColorImageClass imagesToAdd[])
{
  // Initializes to black
  ColorClass black;
  black.setToBlack();
  initializeTo(black);

  bool flag = false;
  for (int k = 0; k < numImgsToAdd; k++)
  {
    for (int i = 0; i < numRows; i++)
    {
      for (int j = 0; j < numCols; j++)
      {
        if (img[i][j].addColor(imagesToAdd[k].img[i][j]))
        {
          flag = true;
        }
      }
    }
  }
  return flag;
}

// Set pixel; return false if out of bounds.
bool ColorImageClass::setColorAtLocation(const RowColumnClass &inRowCol, 
  const ColorClass &inColor)
{
  int row = inRowCol.getRow();
  int col = inRowCol.getCol();

  if (row < 0 || row >= numRows || col < 0 || col >= numCols)
  {
    return false;
  }
  
  img[row][col].setTo(inColor);
  return true;
}

// Get pixel; return false if out of bounds
bool ColorImageClass::getColorAtLocation(const RowColumnClass &inRowCol, 
  ColorClass &outColor) const
{
  int row = inRowCol.getRow();
  int col = inRowCol.getCol();

  if (row < 0 || row >= numRows || col < 0 || col >= numCols)
  {
    return false;
  }
  outColor.setTo(img[row][col]);
  return true;
}

// Print the entire image (pixels separated by "--", newline per row)
void ColorImageClass::printImage() const
{
  for (int i = 0; i < numRows; i++)
  {
    for (int j = 0; j < numCols; j++)
    {
      img[i][j].printComponentValues();
      if (j < numCols - 1)
      {
        cout << SYMBOL;
      }
    }
    cout << endl;
  }
}

