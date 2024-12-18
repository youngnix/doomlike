#include "graphics.hpp"
#include "SDL_mouse.h"
#include "SDL_render.h"
#include "SDL_video.h"

Graphics graphics;

Graphics::Graphics() {
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("DOOMLIKE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Graphics::Begin() {
	SDL_SetRenderDrawColor(graphics.renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(graphics.renderer);
}

void Graphics::End() {
	SDL_RenderPresent(graphics.renderer);
}
