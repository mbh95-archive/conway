//
//  intqueue.c
//  sand
//
//  Created by Matthew Hammond on 12/21/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "intqueue.h"

IntQueue *new_intqueue(int size) {
	if (size <= 0) {
		fprintf(stderr, "Error: Invalid queue size: %d\n", size);
		return NULL;
	}
	IntQueue *queue = malloc(sizeof(IntQueue));
	if (queue == NULL) {
		fprintf(stderr, "Error: Failed to allocate int queue struct\n");
		return NULL;
	}
	queue->data = malloc(size * sizeof(int));
	if (queue->data == NULL) {
		fprintf(stderr, "Error: Failed to allocate int queue data\n");
		free(queue);
		return NULL;
	}
	queue->maxcap = size;
	queue->curcap = 0;
	queue->leftp = 0;
	queue->rightp = 0;
	return queue;
}

void free_intqueue(IntQueue *freeme) {
	if (freeme == NULL) {
		return;
	}
	if (freeme->data != NULL) {
		free(freeme->data);
		freeme->data = NULL;
	}
	free(freeme);
}

int intqueue_is_empty(IntQueue *queue) {
	if (queue->curcap == 0) {
		return 1;
	} else {
		return 0;
	}
}

void intqueue_push(IntQueue *queue, int pushme) {
	if (queue->curcap >= queue->maxcap) {
		fprintf(stderr, "Error: queue full (%d/%d)\n", queue->curcap, queue->maxcap);
		return;
	} else {
		queue->data[queue->rightp] = pushme;
		queue->rightp = (queue->rightp + 1) % queue->maxcap;
		queue->curcap++;
	}
}

int intqueue_pop(IntQueue *queue) {
	int return_val;
	if (intqueue_is_empty(queue)) {
		fprintf(stderr, "Error: Attempted pop from empty queue\n");
		return -1;
	} else {
		return_val = queue->data[queue->leftp];
		queue->leftp = (queue->leftp + 1) % queue->maxcap;
		queue->curcap--;
		return return_val;
	}
}

int intqueue_peek(IntQueue *queue) {
	if (intqueue_is_empty(queue)) {
		fprintf(stderr, "Error: Attempted peek from empty queue\n");
		return -1;
	} else {
		return queue->data[queue->leftp];
	}
}
