//
//  intqueue.h
//  sand
//
//  Created by Matthew Hammond on 12/21/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//

#ifndef intqueue_h
#define intqueue_h

typedef struct {
	unsigned int maxcap; // Maximum capacity of the queue
	unsigned int curcap; // Current capacity of the queue
	unsigned int leftp;  // Index of first element
	unsigned int rightp; // Index of next free slot
	int *data;
} IntQueue;

/*
 * Allocate, initialize, and return a new int queue with the given maximum capacity.
 * On failure print an error and return NULL.
 */
IntQueue *new_intqueue(int size);

/*
 * Deallocate the given int queue structure and its internal data structures.
 */
void free_intqueue(IntQueue *freeme);

/*
 * Return 1 if the given int queue is empty and 0 otherwise.
 */
int intqueue_is_empty(IntQueue *queue);

/*
 * Push an int onto the given queue.
 * If the queue is already full then print an error and return.
 */
void intqueue_push(IntQueue *queue, int pushme);

/*
 * Remove and return the next int from the given queue.
 * Return -1 and print an error if the queue is empty.
 */
int intqueue_pop(IntQueue *queue);

/*
 * Return the next int from the given queue.
 * Return -1 and print an error if the queue is empty.
 */
int intqueue_peek(IntQueue *queue);

#endif /* intqueue_h */
