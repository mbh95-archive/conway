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
#include "intqueue.h"

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
	
	int intqueue_result = test_intqueue();
	if (intqueue_result != 0) {
		printf("FAILED IntQueue(%d)\n", intqueue_result);
	} else {
		printf("PASSED IntQueue (%d)\n", intqueue_result);
	}
}

int test_bitvec() {
	BitVec *bv = NULL;
	int i;
	bv = new_bitvec(-1);
	if (bv != NULL) {
		return -1;
	}
	bv = new_bitvec(0);
	if (bv != NULL) {
		return -2;
	}
	
	bv = new_bitvec(1);
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
	
	free_bitvec(bv);
	bv = NULL;
	
	bv = new_bitvec(32000);
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
	free_bitvec(bv);
	return 0;
}

int test_bitgrid() {
	BitGrid *bg = NULL;
	int r, c;
	bg = new_bitgrid(-1, -1);
	if (bg != NULL) {
		return -1;
	}
	bg = new_bitgrid(0, 0);
	if (bg != NULL) {
		return -2;
	}
	
	bg = new_bitgrid(1000, 1000);
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
	
	free_bitgrid(bg);
	bg = NULL;
	
	bg = new_bitgrid(1234, 17);
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
	free_bitgrid(bg);
	return 0;
}

int test_intqueue() {
	IntQueue *iq = NULL;
	int i;
	int *testvals;
	
	iq = new_intqueue(-1);
	if (iq != NULL) {
		return -1;
	}
	iq = new_intqueue(0);
	if (iq != NULL) {
		return -2;
	}
	
	iq = new_intqueue(100);
	if (iq == NULL || iq->curcap != 0 || iq->maxcap != 100) {
		return -3;
	}
	
	if (intqueue_peek(iq) != -1) {
		return -4;
	}
	
	if (intqueue_pop(iq) != -1) {
		return -5;
	}
	
	testvals = malloc(100 * sizeof(int));
	for (i = 0; i < 50; i++) {
		testvals[i] = rand();
		intqueue_push(iq, testvals[i]);
	}
	for (i = 0; i < 25; i++) {
		if (intqueue_pop(iq) != testvals[i]) {
			return -6;
		}
	}
	for (i = 50; i < 100; i++) {
		testvals[i] = rand();
		intqueue_push(iq, testvals[i]);
	}
	for (i = 25; i < 100; i++) {
		if (intqueue_pop(iq) != testvals[i]) {
			return -7;
		}
	}
	
	free(testvals);
	free_intqueue(iq);
	return 0;
}
