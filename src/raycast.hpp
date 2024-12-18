#pragma once

#include "tiles.hpp"

struct Raycaster {
	float planeX, planeY;

	Raycaster();
	Raycaster(float planeX, float planeY);
	void Cast(SDL_Renderer *window, vec2 pos, float angle, Tilemap &tilemap);
};
