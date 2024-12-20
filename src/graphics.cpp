#include "graphics.hpp"
#include "SDL3/SDL_mouse.h"
#include <cassert>

Graphics graphics;

Graphics::Graphics() {
	assert(SDL_Init(SDL_INIT_VIDEO));

	window = SDL_CreateWindow("DOOMLIKE", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, "opengl");

	SDL_SetWindowRelativeMouseMode(window, true);
}

void Graphics::Begin() {
	SDL_SetRenderDrawColor(graphics.renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(graphics.renderer);
}

void Graphics::End() {
	SDL_RenderPresent(graphics.renderer);
}
