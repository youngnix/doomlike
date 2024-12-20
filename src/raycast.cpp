#include <SDL3/SDL.h>
#include "tiles.hpp"
#include "raycast.hpp"
#include "graphics.hpp"
#include <cmath>

// Put a limit do DDA dont run a infinite distance
constexpr float MAX_RAY_LENGTH = 100.0f;

// Defining colors for tiles
constexpr unsigned int tileColors[] = {
    0x00000000, // TILES_EMPTY
    0xFF8F4DFF, // TILES_BRICKS
    0xFF8F4DFF, // TILES_DIRT
    0xFFFFBDFF, // TILES_LIGHT
};

// Constructors using Initialization List
Raycaster::Raycaster() : plane{0, 0.66} {}
Raycaster::Raycaster(float planeX, float planeY) : plane{planeX, planeY} {}

void Raycaster::CalculateRayDirection(int x, vec2 dir, vec2 rayDir) {
    const double cameraX = 2 * x / static_cast<double>(WINDOW_WIDTH) - 1;
    const double angle = std::atan2(dir[1], dir[0]);

    rayDir[0] = dir[0] + (plane[0] * cos(angle) - plane[1] * sin(angle)) * cameraX;
    rayDir[1] = dir[1] + (plane[0] * sin(angle) + plane[1] * cos(angle)) * cameraX;
}

bool Raycaster::PerformDDA(vec2i mapPos, vec2 sideDist, vec2 deltaDist, vec2i step, bool &side, Tilemap &tilemap, TileType &hitTile) {
	vec2i initialPos = {mapPos[0], mapPos[1]};

    // checks for hit tile and length of the ray
    while (std::sqrt(std::pow(mapPos[0] - initialPos[0], 2) + std::pow(mapPos[1] - initialPos[1], 2)) < MAX_RAY_LENGTH) {
        // Determine next position of ray based on which axis will be hit first
        bool axis = (sideDist[0] >= sideDist[1]);
        sideDist[axis] += deltaDist[axis];
        mapPos[axis] += step[axis];
        side = axis;

        // Check if ray has hit a wall
        if (mapPos[0] >= 0 && mapPos[0] < tilemap.width && mapPos[1] >= 0 && mapPos[1] < tilemap.height) {
            hitTile = tilemap.tiles[mapPos[1] * tilemap.width + mapPos[0]];
            if (hitTile != TILES_EMPTY) {
                return true;
            }
        }
    }

    return false;
}

void Raycaster::Draw(vec2 pos, float angle, Tilemap &tilemap) {
	vec2 dir = {std::sin(angle), -std::cos(angle)};

    for (int x = 0; x < WINDOW_WIDTH; x++) {
        TileType hitTile = TILES_EMPTY;
        vec2i mapPos;
        vec2 rayDir, deltaDist, sideDist;
        vec2i step;
        bool side;

        CalculateRayDirection(x, dir, rayDir);

		// perform calculations for x and y axis
        for (int i = 0; i <= 1; i++) {
			mapPos[i] = pos[i];
        	deltaDist[i] = std::abs(1 / rayDir[i]);
        	sideDist[i] = (rayDir[i] < 0) ? (pos[i] - mapPos[i]) * deltaDist[i] : (mapPos[i] + 1.0 - pos[i]) * deltaDist[i];
        	step[i] = (rayDir[i] < 0) ? -1 : 1;
        }

        // Start DDA
        bool hit = PerformDDA(mapPos, sideDist, deltaDist, step, side, tilemap, hitTile);

		SDL_SetRenderDrawColor(graphics.renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderLine(graphics.renderer, pos[0], pos[1], mapPos[0], mapPos[1]);

        if (hit) {
			// start and finish y coordinates
            vec2 line;
            double perpWallDist;
            double lineHeight;
            unsigned int color;
            
            // Calculate Wall Distance
            // false side = index zero
            // true side = index one
            perpWallDist = sideDist[side] - deltaDist[side];

            // Determine the Height of the Line that will be drawn
            lineHeight = std::min(WINDOW_WIDTH / perpWallDist, WINDOW_WIDTH);

            line[0] = std::max(-lineHeight / 2 + WINDOW_WIDTH / 2, 0.0);
            line[1] = std::min(lineHeight / 2 + WINDOW_WIDTH / 2, WINDOW_WIDTH - 1);

			color = tileColors[hitTile];

			// side will bitshift colors so that they're halved
			SDL_SetRenderDrawColor(graphics.renderer, ((color >> 24) & 0xff) >> static_cast<int>(side), ((color >> 16) & 0xff) >> static_cast<int>(side), ((color >> 8) & 0xff) >> static_cast<int>(side), (color & 0xff) >> static_cast<int>(side));
			SDL_RenderLine(graphics.renderer, x, line[0], x, line[1]);
		}
	}
}
