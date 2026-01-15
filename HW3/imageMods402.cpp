#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>
#include "constants.h"
#include "clearBadInput.h"
#include "clipIntToRange.h"
#include "readOneInt.h"
#include "readTwoInts.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"
#include "PatternClass.h"
#include "RectangleClass.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/*
 * File: imageMods402.cpp
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 *
 * Purpose:
 *   Main program for Project 3.
 *   This file implements the user menu and control flow for
 *   performing various image modification operations such as:
 *   1. Drawing filled or outlined rectangles
 *   2. Inserting pattern files with transparency
 *   3. Inserting other PPM images with transparency
 *   4. Saving the modified image to an output PPM file
 */

// Color menu
void printColorMenu()
{
  cout << MENU_COLOR_RED << endl;
  cout << MENU_COLOR_GREEN << endl;
  cout << MENU_COLOR_BLUE << endl;
  cout << MENU_COLOR_BLACK << endl;
  cout << MENU_COLOR_WHITE << endl;
}

bool pickColor(const std::string &prompt, ColorClass &color)
{
  int choice;
  printColorMenu();

  if (!readOneInt(prompt, choice))
  {
    return false;
  }

  if (choice == CHOICE_ONE_INT)
  {
    color.setToRed();
    return true; 
  }
  else if (choice == CHOICE_TWO_INT)
  { 
    color.setToGreen();
    return true; 
  }
  else if (choice == CHOICE_THREE_INT)
  {
    color.setToBlue();  
    return true; 
  }
  else if (choice == CHOICE_FOUR_INT)  
  { 
    color.setToBlack(); 
    return true; 
  }
  else if (choice == CHOICE_FIVE_INT)  
  { 
    color.setToWhite(); 
    return true; 
  }

  cout << INVALID_CHOICE << endl;
  return false;
}

// Main menus
void printMainMenu()
{
  cout << MAIN_MENU_ANNOTATE_RECTANGLE << endl;
  cout << MAIN_MENU_ANNOTATE_FILE << endl;
  cout << MAIN_MENU_INSERTION << endl;
  cout << MAIN_MENU_WRITE_OUT << endl;
  cout << MAIN_MENU_EXIT << endl;
}

void printRectSpecMenu()
{
  cout << SPEC_MENU_CORNERS << endl;
  cout << SPEC_MENU_DIMENSIONS << endl;
  cout << SPEC_MENU_EXTENT << endl;
}

// Main
int main(int argc, char *argv[])
{
  if (argc != EXPECTED_ARG_COUNT)
  {
    cout << "Error: " << USAGE << endl;
    return EXIT_CODE_USAGE_ERROR;
  }

  string bgName = argv[FILENAME_ARG_INDEX];
  std::ifstream inFile(bgName.c_str());
  if (!inFile)
  {
    cout << ERROR_UNABLE_OPEN << bgName << endl;
    return EXIT_CODE_BAD_IMAGE;
  }

  ColorImageClass image;
  if (!image.readFromPPM(inFile))
  {
    cout << ERROR_INVALID_IMAGE << bgName << endl;
    return EXIT_CODE_BAD_IMAGE;
  }
  inFile.close();

  bool done = false;

  while (!done)
  {
    printMainMenu();
    int choice = DEFAULT_CHOICE_INT;
    bool menuOk = readOneInt(ASK_FOR_CHOICE, choice);

    if (!menuOk)
    {
      // invalid input already handled by readOneInt -> show menu again
    }
    else if (choice == CHOICE_ONE_INT)
    {
      // Rectangle
      printRectSpecMenu();
      int rectChoice = DEFAULT_CHOICE_INT;
      bool rectOK = readOneInt(ASK_FOR_METHOD, rectChoice);

      RowColumnClass ul;
      RowColumnClass lr;
      bool validRect = false;

      if (rectOK)
      {
        if (rectChoice == CHOICE_ONE_INT)
        {
          int r1;
          int c1;
          int r2;
          int c2;
          bool ok1 = readTwoInts(REC_REQUEST_LEFT_CORNER_AND_ROW, r1, c1);
          bool ok2 = 
            ok1 && readTwoInts(REC_REQUEST_RIGHT_CORNER_AND_ROW, r2, c2);
          if (ok1 && ok2)
          {
            ul = RowColumnClass(r1, c1);
            lr = RowColumnClass(r2, c2);
            validRect = true;
          }
        }
        else if (rectChoice == CHOICE_TWO_INT)
        {
          int r;
          int c;
          int nRows;
          int nCols;
          bool okPos = readTwoInts(REC_REQUEST_LEFT_CORNER_AND_ROW, r, c);
          bool okR = okPos && readOneInt(REC_REQUEST_ROW, nRows);
          bool okC = okR && readOneInt(REC_REQUEST_COLUMN, nCols);
          if (okPos && okR && okC)
          {
            nRows = clipIntToRange(nRows, MIN_DIMENSION, MAX_DIMENSION);
            nCols = clipIntToRange(nCols, MIN_DIMENSION, MAX_DIMENSION);
            ul = RowColumnClass(r, c);
            lr = RowColumnClass(r + nRows - 1, c + nCols - 1);
            validRect = true;
          }
        }
        else if (rectChoice == CHOICE_THREE_INT)
        {
          int cr, cc, halfR, halfC;
          bool okCenter = readTwoInts(REC_REQUEST_CENTER, cr, cc);
          bool okHr = okCenter && readOneInt(REC_REQUEST_HALF_ROW, halfR);
          bool okHc = okHr && readOneInt(REC_REQUEST_HALF_COLUMN, halfC);
          if (okCenter && okHr && okHc)
          {
            halfR = clipIntToRange(halfR, MIN_DIMENSION, MAX_DIMENSION);
            halfC = clipIntToRange(halfC, MIN_DIMENSION, MAX_DIMENSION);
            ul = RowColumnClass(cr - halfR, cc - halfC);
            lr = RowColumnClass(cr + halfR, cc + halfC);
            validRect = true;
          }
        }
        else
        {
          cout << INVALID_CHOICE << endl;
        }
      }

      if (validRect)
      {
        ColorClass rectColor;
        bool colorOK = pickColor(REC_REQUEST_COLOR, rectColor);

        cout << ANSWER_NO << endl;
        cout << ANSWER_YES << endl;
        int fillOpt = DEFAULT_CHOICE_INT;
        bool fillOK = colorOK && readOneInt(REC_REQUEST_OPTION_INT, fillOpt);
        if (fillOK)
        {
          bool filled = (fillOpt == CHOICE_TWO_INT);
          RectangleClass rect(ul, lr, rectColor, filled);
          rect.drawOnImage(image);
        }
      }
    }
    else if (choice == CHOICE_TWO_INT)
{
  // Pattern from file
  cout << PAT_REQUEST_FILE_NAME;
  string pName;
  bool nameOk = static_cast<bool>(cin >> pName);
  if (!nameOk)
  {
    cout << PAT_INVALID_INPUT << endl;
    clearBadInput();
  }
  else
  {
    int pr;
    int pc;
    bool posOk = false;
    while (!posOk)
    {
      cout << PAT_REQUEST_UPPER_LEFT_CORNER;
      if (cin >> pr >> pc)
      {
        posOk = true;
      }
      else
      {
        cout << PAT_INVALID_INPUT << endl;
        clearBadInput();
      }
    }

    ColorClass pColor;
    bool colorOk = posOk && pickColor(PAT_REQUEST_COLOR_INT, pColor);

    if (colorOk)
    {
      std::ifstream pin(pName.c_str());
      bool fileOk = static_cast<bool>(pin);
      if (!fileOk)
      {
        cout << PAT_ERROR_UNABLE_OPEN << pName << endl;
      }
      else
      {
        PatternClass pat;
        bool readOk = pat.readFrom(pin);
        pin.close();
        if (!readOk)
        {
          cout << PAT_ERROR_INVALID_FILE << pName << endl;
        }
        else
        {
          RowColumnClass topLeft(pr, pc);
          pat.applyToImage(image, topLeft, pColor);
        }
      }
    }
  }
}
    else if (choice == CHOICE_THREE_INT)
    {
      // Insert another image
      cout << NEW_IMAGE_FILE_NAME;
      string inName;
      bool gotName = static_cast<bool>(cin >> inName);
      if (!gotName)
      {
        cout << NEW_IMAGE_ERROR_INVALID_INPUT << endl;
        clearBadInput();
      }
      else
      {
        int r;
        int c;
        bool posOk = readTwoInts(NEW_IMAGE_REQUEST_UPPER_LEFT, r, c);
        ColorClass transColor;
        bool colorOk =
          posOk && pickColor(NEW_IMAGE_REQUEST_COLOR_INT, transColor);

        if (colorOk)
        {
          std::ifstream inImg(inName.c_str());
          bool fileOk = static_cast<bool>(inImg);
          if (!fileOk)
          {
            cout << NEW_IMAGE_ERROR_UNABLE_OPEN << inName << endl;
          }
          else
          {
            ColorImageClass small;
            bool readOk = small.readFromPPM(inImg);
            inImg.close();

            if (!readOk)
            {
              cout << NEW_IMAGE_ERROR_INVALID_IMAGE << inName << endl;
            }
            else
            {
              for (int rr = 0; rr < small.getRows(); rr++)
              {
                for (int cc = 0; cc < small.getCols(); cc++)
                {
                  RowColumnClass srcLoc(rr, cc);
                  ColorClass pix;
                  bool gotPix = small.getColorAtLocation(srcLoc, pix);
                  if (gotPix && !pix.isEqual(transColor))
                  {
                    RowColumnClass dstLoc(r + rr, c + cc);
                    image.paintIfInBounds(dstLoc, pix);
                  }
                }
              }
            }
          }
        }
      }
    }
    else if (choice == CHOICE_FOUR_INT)
    {
      // Write out current image
      cout << WRITE_OUT_REQUEST_FILE_NAME;
      string outName;
      bool nameOk = static_cast<bool>(cin >> outName);

      if (!nameOk)
      {
        cout << ERROR_ALERT << endl;
        clearBadInput();
      }
      else
      {
        std::ofstream out(outName.c_str());
        bool openOk = static_cast<bool>(out);
        if (!openOk)
        {
          cout << WRITE_OUT_ERROR_UNABLE_OPEN << outName << endl;
        }
        else
        {
          bool writeOk = image.writeToPPM(out);
          if (!writeOk)
          {
            cout << WRITE_OUT_ERROR_FAIL << outName << endl;
          }
          out.close();
        }
      }
    }
    else if (choice == CHOICE_FIVE_INT)
    {
      cout << ENDING << endl;
      done = true;
    }
    else
    {
      cout << INVALID_CHOICE << endl;
    }
  }

  return 0;
}
