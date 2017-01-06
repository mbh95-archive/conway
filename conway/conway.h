//
//  conway.h
//  conway
//
//  Created by Matthew Hammond on 12/23/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//

#ifndef conway_h
#define conway_h

#include "bitgrid.h"
#include "intqueue.h"

typedef struct {
	BitGrid *world;
	BitGrid *world_next;
	
	BitGrid *queue_mask;
	BitGrid *queue_mask_next;
	
	IntQueue *active;
	IntQueue *active_next;
} GameOfLife;

GameOfLife *new_gameoflife(int width, int height);

void free_gameoflife(GameOfLife *freeme);

void gameoflife_put_at(GameOfLife *gol, int r, int c, int val);
void gameoflife_put_at_next(GameOfLife *gol, int r, int c, int val);

int gameoflife_get_at(GameOfLife *gol, int r, int c);

void gameoflife_step(GameOfLife *gol);

void gameoflife_step_point(GameOfLife *gol, int r, int c);


#endif /* conway_h */
