#pragma once

#include "tiles.hpp"

struct Raycaster {
	float planeX, planeY;

	Raycaster();
	Raycaster(float planeX, float planeY);
	void Draw(vec2 pos, float angle, Tilemap &tilemap);
	void CalculateRayDirection(int x, vec2 dir, vec2 rayDir);
	bool PerformDDA(vec2 pos, vec2 mapPos, vec2 sideDist, vec2 deltaDist, vec2i step, bool &side, Tilemap &tilemap, TileType &hitTile);
};
