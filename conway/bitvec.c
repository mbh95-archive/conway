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

BitVec *bitvec_new(int size) {
	BitVec *bitvec = NULL;
	int i;
	if (size <= 0) {
		fprintf(stderr, "Error (bitvec_new): Invalid size (%d)\n", size);
		return NULL;
	}
	bitvec = malloc(sizeof(BitVec));
	if (bitvec == NULL) {
		fprintf(stderr, "Error (bitvec_new): Failed to allocate BitVec struct\n");
		return NULL;
	}
	bitvec->intsize = (size + INTS_TO_BITS - 1) / INTS_TO_BITS;
	bitvec->data = malloc( bitvec->intsize * sizeof(int));
	if (bitvec->data == NULL) {
		fprintf(stderr, "Error (bitvec_new): Failed to allocate BitVec data\n");
		free(bitvec);
		bitvec = NULL;
		return NULL;
	}
	for (i = 0; i < bitvec->intsize; i++) {
		bitvec->data[i] = 0;
	}
	return bitvec;
}

void bitvec_free(BitVec *freeme) {
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
void bitvec_ensure_size(BitVec *bitvec, int newsize) {
	int increase = 0;
	int i;
	if (newsize <= 0) {
		fprintf(stderr, "Error (bitvec_ensure_size): Invalid size (%d)\n", newsize);
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

void bitvec_set_bit(BitVec *bitvec, int b) {
	if (b < 0) {
		fprintf(stderr, "Error (bitvec_set_bit): Invalid bit index (%d)\n", b);
		return;
	}
	bitvec_ensure_size(bitvec, b + 1);
	bitvec->data[BIDX_TO_IIDX(b)] |= (1 << BIDX_TO_OFFSET(b));
}

void bitvec_clear_bit(BitVec *bitvec, int b) {
	if (b < 0) {
		fprintf(stderr, "Error (bitvec_clear_bit): Invalid bit index (%d)\n", b);
		return;
	}
	bitvec_ensure_size(bitvec, b + 1);
	bitvec->data[BIDX_TO_IIDX(b)] &= ~(1 << BIDX_TO_OFFSET(b));
}

int bitvec_test_bit(BitVec *bitvec, int b) {
	if (b < 0) {
		fprintf(stderr, "Error (bitvec_test_bit): Invalid bit index (%d)\n", b);
		return -1;
	}
	bitvec_ensure_size(bitvec, b + 1);
	return (bitvec->data[BIDX_TO_IIDX(b)] >> BIDX_TO_OFFSET(b)) & 0x1;
}

void bitvec_print(BitVec *bitvec) {
	int i;
	if (bitvec == NULL) {
		fprintf(stderr, "Error (bitvec_print): Attempted to print NULL bit vector\n");
		return;
	}
	printf("Printing bit vector of size %d:\n", bitvec->intsize);
	
	for (i = 0; i < bitvec->intsize; i++) {
		printf("0x%04x\n", bitvec->data[i]);
	}
}
