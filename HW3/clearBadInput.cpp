#include "clearBadInput.h"
#include <iostream>
#include <limits>

using std::cin;

/*
 * Function: clearBadInput
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 * 
 * Purpose:
 *  Clear memory and ignore after input.
 */

void clearBadInput()
{
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}