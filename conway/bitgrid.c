//
//  bitgrid.c
//  conway
//
//  Created by Matthew Hammond on 12/23/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>

#include "bitgrid.h"
#include "bitvec.h"

BitGrid *new_bitgrid(int width, int height) {
	BitGrid *bitgrid = NULL;
	if (width <= 0 || height <= 0) {
		fprintf(stderr, "Error (bitgrid_new): Invalid grid size (%dx%d)\n", width, height);
		return NULL;
	}
	bitgrid = malloc(sizeof(BitGrid));
	if (bitgrid == NULL) {
		fprintf(stderr, "Error (bitgrid_new): Failed to allocate BitGrid struct\n");
		return NULL;
	}
	bitgrid->width = width;
	bitgrid->height = height;
	bitgrid->bits = new_bitvec(width * height);
	if (bitgrid->bits == NULL) {
		fprintf(stderr, "Error (bitgrid_new): Failed to allocate bit vector\n");
		return NULL;
	}
	return bitgrid;
}

void free_bitgrid(BitGrid *freeme) {
	if (freeme == NULL) {
		return;
	}
	if (freeme->bits != NULL) {
		free_bitvec(freeme->bits);
		freeme->bits = NULL;
	}
	free(freeme);
}

void bitgrid_put_bit(BitGrid *bitgrid, int r, int c, int val) {
	if (bitgrid == NULL) {
		fprintf(stderr, "Error (bitgrid_put_bit): Received NULL bit grid\n");
		return;
	}
	if (r < 0 || r >= bitgrid->height || c < 0 || c >= bitgrid->width) {
		fprintf(stderr, "Error (bitgrid_put_bit): Invalid coordinates (%d, %d)\n", r, c);
		return;
	}
	int idx = RC_TO_IDX(r, c, bitgrid->width);
	if (val) {
		bitvec_set_bit(bitgrid->bits, idx);
	} else {
		bitvec_clear_bit(bitgrid->bits, idx);
	}
}

void bitgrid_set_bit(BitGrid *bitgrid, int r, int c) {
	bitgrid_put_bit(bitgrid, r, c, 1);
}

void bitgrid_clear_bit(BitGrid *bitgrid, int r, int c) {
	bitgrid_put_bit(bitgrid, r, c, 0);
}

int bitgrid_test_bit(BitGrid *bitgrid, int r, int c) {
	if (bitgrid == NULL) {
		fprintf(stderr, "Error (bitgrid_test_bit): Received NULL bit grid\n");
		return -1;
	}
	if (r < 0 || r >= bitgrid->height || c < 0 || c >= bitgrid->width) {
		return 0;
	}
	int idx = RC_TO_IDX(r, c, bitgrid->width);
	return bitvec_test_bit(bitgrid->bits, idx);
}
