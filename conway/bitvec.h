//
//  bitvec.h
//  conway
//
//  Created by Matthew Hammond on 12/23/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//

#ifndef bitvec_h
#define bitvec_h

#define INTS_TO_BITS (4 * sizeof(int))
#define BIDX_TO_IIDX(b) ((b) / INTS_TO_BITS)
#define BIDX_TO_OFFSET(b) ((b) % INTS_TO_BITS)

typedef struct {
	int intsize; // Number of ints in data
	int *data;
} BitVec;

/*
 * Allocate, initialize, and return a new bit vector with the given size (in bits).
 * Guarantees all bits are intially zero.
 * Return NULL on failure.
 */
BitVec *new_bitvec(int size);

/*
 * Deallocate the given bit vector and all of its internal data structures.
 */
void free_bitvec(BitVec *freeme);

/*
 * Ensures that the given bit vector can hold at least the specified number of bits.
 * Guarantees that all newly allocated bits are initially zero.
 */
void bitvec_ensure_size(BitVec *bitvec, int newsize);

/*
 * Set the specified bit in the given bit vector to 1.
 */
void bitvec_set_bit(BitVec *bitvec, int b);

/*
 * Set the specifed bit in the given bit vector to 0.
 */
void bitvec_clear_bit(BitVec *bitvec, int b);

/*
 * Return the value of the specified bit in the given bit vector.
 * Returns -1 on failure.
 */
int bitvec_test_bit(BitVec *bitvec, int b);

/*
 * Prints the given bit vector to stdout.
 */
void bitvec_print(BitVec *bitvec);

#endif /* bitvec_h */
