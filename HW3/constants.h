#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
/*
 * Name: Hanyang Liu
 
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 * 
 * Purpose:
 * Global constants used in Project 3.
 */

// Image color limits
const int MIN_COLOR_VALUE = 0;
const int MAX_COLOR_VALUE = 255;

// Valid PPM image dimensions range
const int MIN_DIMENSION = 1;
const int MAX_DIMENSION = 2000;

// Default value of row and column
const int DEFAULT_INDEX = 0;

// Character
const char CHAR_P = 'P';
const char CHAR_THREE = '3';
const char CHAR_END = '\0';

// Magic
const int MAGIC_LENGTH = 3;
const int MAGIC_INDEX_ZERO = 0;
const int MAGIC_INDEX_ONE = 1;
const int MAGIC_INDEX_TWO = 2;

// Fill Values
const int FILL_VALUE_ZERO = 0;
const int FILL_VALUE_ONE = 1;

// Default value of rectangle
const int DEFAULT_LOCATION = 0;

// Requests for rectangle information
const std::string REC_REQUEST_LEFT_CORNER_AND_ROW =
  "Enter upper left corner row and column: ";
const std::string REC_REQUEST_RIGHT_CORNER_AND_ROW =
  "Enter lower right corner row and column: ";
const std::string REC_REQUEST_ROW = "Enter int for number of rows: ";
const std::string REC_REQUEST_COLUMN = "Enter int for number of columns: ";
const std::string REC_REQUEST_CENTER =
  "Enter rectangle center row and column: ";
const std::string REC_REQUEST_HALF_ROW = "Enter int for half number of rows: ";
const std::string REC_REQUEST_HALF_COLUMN =
  "Enter int for half number of columns: ";
const std::string REC_REQUEST_COLOR = "Enter int for rectangle color: ";
const std::string REC_REQUEST_OPTION_INT =
  "Enter int for rectangle fill option: ";
const std::string ANSWER_NO = "1. No";
const std::string ANSWER_YES = "2. Yes";

// Requests for pattern information
const std::string PAT_REQUEST_FILE_NAME = 
  "Enter string for file name containing pattern: ";
const std::string PAT_REQUEST_UPPER_LEFT_CORNER = 
  "Enter upper left corner of pattern row and column: ";
const std::string PAT_REQUEST_COLOR_INT = "Enter int for pattern color: ";
const std::string PAT_INVALID_INPUT = "Invalid data entered";
const std::string PAT_ERROR_UNABLE_OPEN =
  "Error: Unable to open pattern file: ";
const std::string PAT_ERROR_INVALID_FILE = "Error: Invalid pattern file: ";

// Requests for new image information
const std::string NEW_IMAGE_FILE_NAME = 
  "Enter string for file name of PPM image to insert: ";
const std::string NEW_IMAGE_REQUEST_UPPER_LEFT = 
  "Enter upper left corner to insert image row and column: ";
const std::string NEW_IMAGE_REQUEST_COLOR_INT = 
  "Enter int for transparecy color: ";
const std::string NEW_IMAGE_ERROR_INVALID_INPUT = "Invalid data entered";
const std::string NEW_IMAGE_ERROR_UNABLE_OPEN =
  "Error: Unable to open image file: ";
const std::string NEW_IMAGE_ERROR_INVALID_IMAGE = "Error: Invalid PPM image: ";

// Color menu choices
const std::string MENU_COLOR_RED = "1. Red";
const std::string MENU_COLOR_GREEN = "2. Green";
const std::string MENU_COLOR_BLUE = "3. Blue";
const std::string MENU_COLOR_BLACK = "4. Black";
const std::string MENU_COLOR_WHITE = "5. White";
const std::string INVALID_CHOICE = "Invalid menu option!";

// Main menu choices
const std::string ASK_FOR_CHOICE = "Enter int for main menu choice: ";
const std::string MAIN_MENU_ANNOTATE_RECTANGLE =
  "1. Annotate image with rectangle";
const std::string MAIN_MENU_ANNOTATE_FILE = 
  "2. Annotate image with pattern from file";
const std::string MAIN_MENU_INSERTION = "3. Insert another image";
const std::string MAIN_MENU_WRITE_OUT = "4. Write out current image";
const std::string MAIN_MENU_EXIT = "5. Exit the program";
const int DEFAULT_CHOICE_INT = 0;
const int CHOICE_ONE_INT = 1;
const int CHOICE_TWO_INT = 2;
const int CHOICE_THREE_INT = 3;
const int CHOICE_FOUR_INT = 4;
const int CHOICE_FIVE_INT = 5;

// Spec menu choices
const std::string SPEC_MENU_CORNERS = 
  "1. Specify upper left and lower right corners of rectangle";
const std::string SPEC_MENU_DIMENSIONS = 
  "2. Specify upper left corner and dimensions of rectangle";
const std::string SPEC_MENU_EXTENT = 
  "3. Specify extent from center of rectangle";
const std::string ASK_FOR_METHOD = 
  "Enter int for rectangle specification method: ";

// Command-line argument expectations
const int EXPECTED_ARG_COUNT = 2;
const int FILENAME_ARG_INDEX = 1;

// Main
const std::string USAGE = "Usage: imageMods402.exe <PPM filename>";
const std::string ERROR_UNABLE_OPEN = "Error: Unable to open main image file: ";
const std::string ERROR_INVALID_IMAGE = "Error: Invalid PPM image: ";

// Program exit codes
const int EXIT_CODE_USAGE_ERROR = 2;
const int EXIT_CODE_BAD_IMAGE = 3;

// Write out
const std::string WRITE_OUT_REQUEST_FILE_NAME = 
  "Enter string for PPM file name to output: ";
const std::string WRITE_OUT_ERROR_UNABLE_OPEN =
  "Error: Unable to open output file: ";
const std::string WRITE_OUT_ERROR_FAIL = "Error: Failed to write image to: ";

// Error
const std::string ERROR_ALERT = "Invalid data entered";

// Ending
const std::string ENDING = "Thank you for using this program";
#endif // CONSTANTS_H
