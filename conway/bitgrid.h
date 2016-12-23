//
//  bitgrid.h
//  conway
//
//  Created by Matthew Hammond on 12/23/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//

#ifndef bitgrid_h
#define bitgrid_h

#include "bitvec.h"

#define RC_TO_IDX(r, c, w) (((r) * (w)) + (c))

typedef struct {
	int width;
	int height;
	BitVec *bits;
} BitGrid;

/*
 * Allocate, initialize, and return a new bit grid with the given width and height (in bits).
 * Guarantees all bits are intially zero.
 * Return NULL on failure.
 */
BitGrid *new_bitgrid(int width, int height);

/*
 * Deallocate the given bit grid and all of its internal data structures.
 */
void free_bitgrid(BitGrid *freeme);

/*
 * Set the specified bit in the given bit grid to the given value.
 */
void bitgrid_put_bit(BitGrid *bitgrid, int r, int c, int val);

/*
 * Set the specified bit in the given bit grid to 1.
 */
void bitgrid_set_bit(BitGrid *bitgrid, int r, int c);

/*
 * Set the specified bit in the given bit grid to 0.
 */
void bitgrid_clear_bit(BitGrid *bitgrid, int r, int c);

/*
 * Return the value of the specified bit in the given bit grid.
 * Returns 0 for any coordinate not on the grid.
 * Returns -1 on failure.
 */
int bitgrid_test_bit(BitGrid *bitgrid, int r, int c);


#endif /* bitgrid_h */
