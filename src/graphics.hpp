#pragma once

#include <SDL3/SDL.h>

#define WINDOW_WIDTH 640.0
#define WINDOW_HEIGHT 480.0

struct Graphics {
	SDL_Renderer *renderer;
	SDL_Window *window;

	Graphics();

	void Begin();
	void End();
};

extern struct Graphics graphics;
