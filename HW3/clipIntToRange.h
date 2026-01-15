#ifndef CLIP_INT_TO_RANGE_H
#define CLIP_INT_TO_RANGE_H

/*
 * File: clipIntToRange.h
 * Name: Hanyang Liu
 * UniqueID: hanyliu
 * UMID: 10357681
 * Date: 11/13/2025
 *
 * Purpose:
 *   Global helper to clip an integer value into the closed interval [low,high].
 *   Used for color channel limits and other bounded integer operations.
 */

int clipIntToRange(int value, int low, int high);

#endif // CLIP_INT_TO_RANGE_H
