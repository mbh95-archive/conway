//
//  main.c
//  conway
//
//  Created by Matthew Hammond on 12/21/16.
//  Copyright © 2016 Matthew Hammond. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>

#include "conway.h"

#define WINDOW_TITLE "gol"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define GAME_WIDTH 80
#define GAME_HEIGHT 60

#define SCREEN_TO_GAME_X(x) ((x) * GAME_WIDTH / WINDOW_WIDTH)
#define SCREEN_TO_GAME_Y(y) ((y) * GAME_HEIGHT / WINDOW_HEIGHT)

SDL_Window *sdlWindow = NULL;
SDL_Renderer *sdlRenderer = NULL;
SDL_Texture *renderTarget = NULL;
SDL_Rect *gameRect = NULL;
SDL_Rect *windowRect = NULL;

int init_sdl(void);

void exit_sdl(void);

void render(GameOfLife *gol, SDL_Renderer *renderer);

int main(int argc, const char * argv[]) {
	
	int running = 1;
	int paused = 1;
	int mouseDown = 0;
	SDL_Event e;
	
	// Initialize SDL
	if (init_sdl() < 0) {
		fprintf(stderr, "Error initializing SDL: %s", SDL_GetError());
		exit_sdl();
		return 1;
	}
	
	GameOfLife *gol = new_gameoflife(GAME_WIDTH, GAME_HEIGHT);
	
	// Main loop
	while (running) {
		
		SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(sdlRenderer);
		
		// Handle SDL events
		while (SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_MOUSEBUTTONDOWN:
					printf("BUTTON %d\n", e.button.button);
					gameoflife_put_at(gol, SCREEN_TO_GAME_Y(e.motion.y), SCREEN_TO_GAME_X(e.motion.x), 1);
					mouseDown = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					mouseDown = 0;
					break;
				case SDL_MOUSEMOTION:
					if (!mouseDown) {
						break;
					}
					gameoflife_put_at(gol, SCREEN_TO_GAME_Y(e.motion.y), SCREEN_TO_GAME_X(e.motion.x), 1);
					break;
				case SDL_KEYDOWN:
					if (e.key.keysym.sym == SDLK_SPACE) {
						paused = !paused;
					}
					
			}
		}
		
		if (!paused) {
			gameoflife_step(gol);
		}
		
		SDL_SetRenderTarget(sdlRenderer, renderTarget);
		SDL_RenderClear(sdlRenderer);
		render(gol, sdlRenderer);
		SDL_SetRenderTarget(sdlRenderer, NULL);

		SDL_RenderCopy(sdlRenderer, renderTarget, gameRect, windowRect);
		SDL_RenderPresent(sdlRenderer);
	}
	
	// Clean up and exit
	printf("Exiting...\n");
	free_gameoflife(gol);
	exit_sdl();
	return 0;
}

int init_sdl() {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return -1;
	}
	
	sdlWindow = SDL_CreateWindow(WINDOW_TITLE,
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  WINDOW_WIDTH, WINDOW_HEIGHT,
							  SDL_WINDOW_SHOWN);
	if (sdlWindow == NULL) {
		return -1;
	}
	
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (sdlRenderer == NULL) {
		return -1;
	}
	
	renderTarget = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, GAME_WIDTH, GAME_HEIGHT);
	if (renderTarget == NULL) {
		return -1;
	}
	
	gameRect = malloc(sizeof(SDL_Rect));
	gameRect->x = 0;
	gameRect->y = 0;
	gameRect->w = GAME_WIDTH;
	gameRect->h = GAME_HEIGHT;
	
	windowRect = malloc(sizeof(SDL_Rect));
	windowRect->x = 0;
	windowRect->y = 0;
	windowRect->w = WINDOW_WIDTH;
	windowRect->h = WINDOW_HEIGHT;
	
	return 0;
}

void exit_sdl() {
	SDL_DestroyRenderer(sdlRenderer);
	sdlRenderer = NULL;
	
	SDL_DestroyWindow(sdlWindow);
	sdlWindow = NULL;
	
	SDL_Quit();
}

void render(GameOfLife *gol, SDL_Renderer *renderer) {
	int r, c;
	SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	for (r = 0; r < gol->world->height; r++) {
		for (c = 0; c < gol->world->width; c++) {
			if (gameoflife_get_at(gol, r, c)) {
				SDL_RenderDrawPoint(renderer, c, r);
			}
		}
	}
}
