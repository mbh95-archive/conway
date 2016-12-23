//
//  test.c
//  conway
//
//  Created by Matthew Hammond on 12/23/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "bitvec.h"

void run_all_tests() {
	int bitvec_result = bitvec_test();
	if (bitvec_result != 0) {
		printf("FAILED BitVec (%d)\n", bitvec_result);
	} else {
		printf("PASSED BitVec (%d)\n", bitvec_result);
	}
}

int bitvec_test() {
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
		if (test_bit(bv, i) != 0) {
			return -4;
		}
		set_bit(bv, i);
		if (test_bit(bv, i) != 1) {
			return -5;
		}
	}
	
	free_bitvec(bv);
	bv = NULL;
	
	bv = new_bitvec(32000);

	for (i = 0; i < 32000; i+= 1) {
		if (test_bit(bv, i) != 0) {
			return -6;
		}
		set_bit(bv, i);
		if (test_bit(bv, i) != 1) {
			return -7;
		}
	}

	return 0;
}
