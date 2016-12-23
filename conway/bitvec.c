//
//  bitvec.c
//  conway
//
//  Created by Matthew Hammond on 12/23/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "bitvec.h"

BitVec *new_bitvec(int size) {
	BitVec *bitvec = NULL;
	int i;
	if (size <= 0) {
		fprintf(stderr, "Error (new_bitvec): Invalid size (%d)\n", size);
		return NULL;
	}
	bitvec = malloc(sizeof(BitVec));
	if (bitvec == NULL) {
		fprintf(stderr, "Error (new_bitvec): Failed to allocate BitVec struct\n");
		return NULL;
	}
	bitvec->intsize = (size + INTS_TO_BITS - 1) / INTS_TO_BITS;
	bitvec->data = malloc( bitvec->intsize * sizeof(int));
	if (bitvec->data == NULL) {
		fprintf(stderr, "Error (new_bitvec): Failed to allocate BitVec data\n");
		free(bitvec);
		bitvec = NULL;
		return NULL;
	}
	for (i = 0; i < bitvec->intsize; i++) {
		bitvec->data[i] = 0;
	}
	return bitvec;
}

void free_bitvec(BitVec *freeme) {
	if (freeme == NULL) {
		return;
	}
	if (freeme->data != NULL) {
		free(freeme->data);
		freeme->data = NULL;
	}
	free(freeme);
}

/*
 * Works by doubling the capacity of the bit vector until size requirement is satisfied.
 */
void ensure_bitvec_size(BitVec *bitvec, int newsize) {
	int increase = 0;
	int i;
	if (newsize <= 0) {
		fprintf(stderr, "Error (ensure_bitvec_size): Invalid size (%d)\n", newsize);
		return;
	}
	if (newsize <= (INTS_TO_BITS * bitvec->intsize)) {
		return;
	}
	while (newsize > (INTS_TO_BITS * bitvec->intsize)) {
		increase += bitvec->intsize;
		bitvec->intsize *= 2;
	}
	bitvec->data = realloc(bitvec->data, bitvec->intsize * sizeof(int));
	for (i = 0; i < increase; i++) {
		bitvec->data[bitvec->intsize - 1 - i] = 0;
	}
}

void set_bit(BitVec *bitvec, int b) {
	if (b < 0) {
		fprintf(stderr, "Error (set_bit): Invalid bit index (%d)", b);
		return;
	}
	ensure_bitvec_size(bitvec, b + 1);
	bitvec->data[BIDX_TO_IIDX(b)] |= (1 << BIDX_TO_OFFSET(b));
}

void clear_bit(BitVec *bitvec, int b) {
	if (b < 0) {
		fprintf(stderr, "Error (clear_bit): Invalid bit index (%d)", b);
		return;
	}
	ensure_bitvec_size(bitvec, b + 1);
	bitvec->data[BIDX_TO_IIDX(b)] &= ~(1 << BIDX_TO_OFFSET(b));
}

int test_bit(BitVec *bitvec, int b) {
	if (b < 0) {
		fprintf(stderr, "Error (test_bit): Invalid bit index (%d)", b);
		return -1;
	}
	ensure_bitvec_size(bitvec, b + 1);
	return (bitvec->data[BIDX_TO_IIDX(b)] >> BIDX_TO_OFFSET(b)) & 0x1;
}

void print_bitvec(BitVec *bitvec) {
	int i;
	if (bitvec == NULL) {
		fprintf(stderr, "Error: Attempted to print NULL bit vector\n");
		return;
	}
	printf("Printing bit vector of size %d:\n", bitvec->intsize);
	
	for (i = 0; i < bitvec->intsize; i++) {
		printf("0x%04x\n", bitvec->data[i]);
	}
}
