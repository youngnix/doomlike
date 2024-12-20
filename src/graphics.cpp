#include "graphics.hpp"
#include "SDL3/SDL_mouse.h"
#include <cassert>
#include <stdexcept>

Graphics graphics;

Graphics::Graphics() {
	assert(SDL_Init(SDL_INIT_VIDEO));

	window = SDL_CreateWindow("DOOMLIKE", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!window) {
		throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
    }

	renderer = SDL_CreateRenderer(window, "opengl");
	if (!renderer) {
        SDL_DestroyWindow(window);
        throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
    }

	SDL_SetWindowRelativeMouseMode(window, true);
}

Graphics::~Graphics() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Graphics::Begin() {
	SDL_SetRenderDrawColor(graphics.renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(graphics.renderer);
}

void Graphics::End() {
	SDL_RenderPresent(graphics.renderer);
}
