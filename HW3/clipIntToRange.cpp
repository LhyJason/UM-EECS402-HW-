#include "clipIntToRange.h"

/*
 * Function: clipIntToRange
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 * 
 * Purpose:
 *   Clip an integer value "value" so it lies within the
 *   closed interval [low, high].
 */

int clipIntToRange(int value, int low, int high)
{
  if (value < low)
  {
    return low;
  }
  else if (value > high)
  {
    return high;
  }
  else
  {
    return value;
  }
}
