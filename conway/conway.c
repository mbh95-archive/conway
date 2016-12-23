//
//  conway.c
//  conway
//
//  Created by Matthew Hammond on 12/23/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "conway.h"

GameOfLife *new_gameoflife(int width, int height) {
	GameOfLife *gol = NULL;
	if (width <= 0 || height <= 0) {
		fprintf(stderr, "Error (new_gameoflife): Invalid grid size (%dx%d)\n", width, height);
		return NULL;
	}
	gol = malloc(sizeof(GameOfLife));
	if (gol == NULL) {
		fprintf(stderr, "Error (new_gameoflife): Failed to allocate GameOfLife struct\n");
		return NULL;
	}
	gol->world = new_bitgrid(width, height);
	if (gol->world == NULL) {
		fprintf(stderr, "Error (new_gameoflife): Failed to allocate GameOfLife data\n");
		free(gol);
		return NULL;
	}
	gol->world_next = new_bitgrid(width, height);
	if (gol->world_next == NULL) {
		fprintf(stderr, "Error (new_gameoflife): Failed to allocate GameOfLife data\n");
		free_bitgrid(gol->world);
		free(gol);
		return NULL;
	}
	gol->queue_mask = new_bitgrid(width, height);
	if (gol->queue_mask == NULL) {
		fprintf(stderr, "Error (new_gameoflife): Failed to allocate GameOfLife data\n");
		free_bitgrid(gol->world_next);
		free_bitgrid(gol->world);
		free(gol);
		return NULL;
	}
	gol->queue_mask_next = new_bitgrid(width, height);
	if (gol->queue_mask_next == NULL) {
		fprintf(stderr, "Error (new_gameoflife): Failed to allocate GameOfLife data\n");
		free_bitgrid(gol->queue_mask);
		free_bitgrid(gol->world_next);
		free_bitgrid(gol->world);
		free(gol);
		return NULL;
	}
	gol->active = new_intqueue(width * height);
	if (gol->active == NULL) {
		fprintf(stderr, "Error (new_gameoflife): Failed to allocate GameOfLife data\n");
		free_bitgrid(gol->queue_mask_next);
		free_bitgrid(gol->queue_mask);
		free_bitgrid(gol->world_next);
		free_bitgrid(gol->world);
		free(gol);
		return NULL;
	}
	gol->active_next = new_intqueue(width * height);
	if (gol->active_next == NULL) {
		fprintf(stderr, "Error (new_gameoflife): Failed to allocate GameOfLife data\n");
		free_intqueue(gol->active);
		free_bitgrid(gol->queue_mask_next);
		free_bitgrid(gol->queue_mask);
		free_bitgrid(gol->world_next);
		free_bitgrid(gol->world);
		free(gol);
		return NULL;
	}
	return gol;
}

void free_gameoflife(GameOfLife *freeme) {
	if (freeme == NULL) {
		return;
	}
	if (freeme->world != NULL) {
		free_bitgrid(freeme->world);
	}
	if (freeme->world_next != NULL) {
		free_bitgrid(freeme->world_next);
	}
	if (freeme->queue_mask != NULL) {
		free_bitgrid(freeme->queue_mask);
	}
	if (freeme->queue_mask_next != NULL) {
		free_bitgrid(freeme->queue_mask_next);
	}
	if (freeme->active != NULL) {
		free_intqueue(freeme->active);
	}
	if (freeme->active_next != NULL) {
		free_intqueue(freeme->active_next);
	}
}

void gameoflife_put_at(GameOfLife *gol, int r, int c, int val) {
	int nr, nc;
	int clamped_val;
	if (val) {
		clamped_val = 1;
	} else {
		clamped_val = 0;
	}
	bitgrid_put_bit(gol->world_next, r, c, clamped_val);
	
	if (bitgrid_test_bit(gol->world, r, c) != clamped_val) {
		for (nr = r - 1; nr <= r + 1; nr++) {
			for (nc = c - 1; nc <= c + 1; nc++) {
				if (nr < 0 || nr >= gol->world->height || nc < 0 || nc >= gol->world->width) {
					continue;
				}
				if (!bitgrid_test_bit(gol->queue_mask_next, nr, nc)) {
					bitgrid_set_bit(gol->queue_mask_next, nr, nc);
					intqueue_push(gol->active_next, RC_TO_IDX(nr, nc, gol->world->width));
					
				}
			}
		}
	}
}

int gameoflife_get_at(GameOfLife *gol, int r, int c) {
	return bitgrid_test_bit(gol->world, r, c);
}

void gameoflife_step(GameOfLife *gol) {
	BitGrid *swap_grid = NULL;
	IntQueue *swap_queue = NULL;
	int idx;
	int r, c;
	while (!intqueue_is_empty(gol->active)) {
		idx = intqueue_pop(gol->active);
		r = IDX_TO_ROW(idx, gol->world->width);
		c = IDX_TO_COL(idx, gol->world->height);
		bitgrid_clear_bit(gol->queue_mask, r, c);
		
		gameoflife_step_point(gol, r, c);
	}
	swap_grid = gol->world;
	gol->world = gol->world_next;
	gol->world_next = swap_grid;
	swap_grid = NULL;

	swap_grid = gol->queue_mask;
	gol->queue_mask = gol->queue_mask_next;
	gol->queue_mask_next = swap_grid;
	swap_grid = NULL;
	
	swap_queue = gol->active;
	gol->active = gol->active_next;
	gol->active_next = swap_queue;
	swap_queue = NULL;
}

void gameoflife_step_point(GameOfLife *gol, int r, int c) {
	int nr, nc;
	int neighbors = 0;
	for (nr = r - 1; nr <= r + 1; nr++) {
		for (nc = c - 1; nc <= c + 1; nc++) {
			if (nr == r && nc == c) {
				continue;
			}
			if (bitgrid_test_bit(gol->world, nr, nc)) {
				neighbors++;
			}
		}
	}
	
	if (bitgrid_test_bit(gol->world, r, c)) { // LIVE
		if (neighbors < 2 || neighbors > 3) {
			// DEATH
			gameoflife_put_at(gol, r, c, 0);
		} else {
			// LIFE
			gameoflife_put_at(gol, r, c, 1);

		}
	} else { // DEAD
		if (neighbors == 3) {
			// LIFE
			gameoflife_put_at(gol, r, c, 1);

		}
	}
	
}
