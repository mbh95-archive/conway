//
//  test.c
//  conway
//
//  Created by Matthew Hammond on 12/23/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "bitvec.h"
#include "bitgrid.h"

void test_run_all() {
	int bitvec_result = test_bitvec();
	if (bitvec_result != 0) {
		printf("FAILED BitVec (%d)\n", bitvec_result);
	} else {
		printf("PASSED BitVec (%d)\n", bitvec_result);
	}
	
	int bitgrid_result = test_bitgrid();
	if (bitgrid_result != 0) {
		printf("FAILED BitGrid (%d)\n", bitgrid_result);
	} else {
		printf("PASSED BitGrid (%d)\n", bitgrid_result);
	}
}

int test_bitvec() {
	BitVec *bv = NULL;
	int i;
	bv = bitvec_new(-1);
	if (bv != NULL) {
		return -1;
	}
	bv = bitvec_new(0);
	if (bv != NULL) {
		return -2;
	}
	
	bv = bitvec_new(1);
	if (bv == NULL) {
		return -3;
	}
	
	for (i = 0; i < 1000; i++) {
		if (bitvec_test_bit(bv, i) != 0) {
			return -4;
		}
		bitvec_set_bit(bv, i);
		if (bitvec_test_bit(bv, i) != 1) {
			return -5;
		}
		bitvec_clear_bit(bv, i);
		if (bitvec_test_bit(bv, i) != 0) {
			return -6;
		}
	}
	
	bitvec_free(bv);
	bv = NULL;
	
	bv = bitvec_new(32000);
	if (bv == NULL) {
		return -7;
	}
	for (i = 0; i < 32000; i+= 1) {
		if (bitvec_test_bit(bv, i) != 0) {
			return -8;
		}
		bitvec_set_bit(bv, i);
		if (bitvec_test_bit(bv, i) != 1) {
			return -9;
		}
		bitvec_clear_bit(bv, i);
		if (bitvec_test_bit(bv, i) != 0) {
			return -10;
		}
	}
	return 0;
}

int test_bitgrid() {
	BitGrid *bg = NULL;
	int r, c;
	bg = bitgrid_new(-1, -1);
	if (bg != NULL) {
		return -1;
	}
	bg = bitgrid_new(0, 0);
	if (bg != NULL) {
		return -2;
	}
	
	bg = bitgrid_new(1000, 1000);
	if (bg == NULL) {
		return -3;
	}
	
	for (r = 0; r < 1000; r++) {
		for (c = 0; c < 1000; c++) {
			if (bitgrid_test_bit(bg, r, c) != 0) {
				return -4;
			}
			bitgrid_set_bit(bg, r, c);
			if (bitgrid_test_bit(bg, r, c) != 1) {
				return -5;
			}
			bitgrid_clear_bit(bg, r, c);
			if (bitgrid_test_bit(bg, r, c) != 0) {
				return -6;
			}
		}
	}
	
	bitgrid_free(bg);
	bg = NULL;
	
	bg = bitgrid_new(1234, 17);
	if (bg == NULL) {
		return -7;
	}
	
	for (r = 0; r < 17; r++) {
		for (c = 0; c < 1234; c++) {
			if (bitgrid_test_bit(bg, r, c) != 0) {
				return -8;
			}
			bitgrid_set_bit(bg, r, c);
			if (bitgrid_test_bit(bg, r, c) != 1) {
				return -9;
			}
			bitgrid_clear_bit(bg, r, c);
			if (bitgrid_test_bit(bg, r, c) != 0) {
				return -10;
			}
		}
	}
	for (r = 17; r < 2000; r++) {
		for (c = 1234; c < 2000; c++) {
			if (bitgrid_test_bit(bg, r, c) != 0) {
				return -11;
			}
		}
	}

	return 0;
}
