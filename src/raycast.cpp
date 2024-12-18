#include <SDL.h>
#include "SDL_render.h"
#include "tiles.hpp"
#include "raycast.hpp"
#include <cmath>

#define screenWidth 640
#define screenHeight 480

// Put a limit do DDA dont run a infinite distance
const float MAX_RAY_LENGTH = 100.0f;

// Defining colors for tiles
const unsigned int tileColors[] = {
    0x00000000, // TILES_EMPTY
    0xFF8F4DFF, // TILES_BRICKS
    0xFF8F4DFF, // TILES_DIRT
    0xFFFFBDFF, // TILES_LIGHT
};

// Constructors using Initialization List
Raycaster::Raycaster() : planeX(0), planeY(0.66) {}
Raycaster::Raycaster(float planeX, float planeY) : planeX(planeX), planeY(planeY) {}

void calculateRayDirection(int x, float dirX, float dirY, float planeX, float planeY, double &rayDirX, double &rayDirY) {
    double cameraX = 2 * x / double(screenWidth) - 1;
    rayDirX = dirX + planeX * cameraX;
    rayDirY = dirY + planeY * cameraX;
}

bool performDDA(SDL_Renderer *renderer, vec2 pos, int &mapX, int &mapY, double rayDirX, double rayDirY, double &sideDistX, double &sideDistY, double deltaDistX, double deltaDistY, int &stepX, int &stepY, int &side, Tilemap &tilemap, TileType &hitTile) {
	float length = 0;
	while (!hitTile && length < MAX_RAY_LENGTH) {
        // Determine next position of ray using as a base which edge will be heat first
		if (sideDistX < sideDistY) {
			length += deltaDistX;
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		} else {
			length += deltaDistY;
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawLineF(renderer, pos[0], pos[1], mapX, mapY);

		if (mapX >= 0 && mapY >= 0 && mapX < tilemap.width && mapY < tilemap.height) {
			// Check if ray has hit a wall
			hitTile = tilemap.tiles[mapY * tilemap.width + mapX];

			if (hitTile != TILES_EMPTY) {
				return true;
			}
		}
    }

    return false;
}

void Raycaster::Cast(SDL_Renderer *renderer, vec2 pos, float angle, Tilemap &tilemap) {
	float dirX = std::sin(angle);
	float dirY = -std::cos(angle);

    for (int x = 0; x < screenWidth; x++) {
        // Calculate ray position and direction
        double rayDirX, rayDirY;
        calculateRayDirection(x, dirX, dirY, planeX, planeY, rayDirX, rayDirY);

		// Which box of the map we are
		int mapX = pos[0];
		int mapY = pos[1];

        double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

        double sideDistX = (rayDirX < 0) ? (pos[0] - mapX) * deltaDistX : (mapX + 1.0 - pos[0]) * deltaDistX;
        double sideDistY = (rayDirY < 0) ? (pos[1] - mapY) * deltaDistY : (mapY + 1.0 - pos[1]) * deltaDistY;

        int stepX = (rayDirX < 0) ? -1 : 1;
        int stepY = (rayDirY < 0) ? -1 : 1;

        int side;
        TileType hitTile = TILES_EMPTY;

        // Start DDA
        bool hit = performDDA(renderer, pos, mapX, mapY, rayDirX, rayDirY, sideDistX, sideDistY, deltaDistX, deltaDistY, stepX, stepY, side, tilemap, hitTile);

        if (hit) {
            // Calculate Wall Distance
            double perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);

            // Determine the Height of the Line that will be drawn
            int lineHeight = std::min(int(screenHeight / perpWallDist), screenHeight);

            int drawStart = std::max(-lineHeight / 2 + screenHeight / 2, 0);
            int drawEnd = std::min(lineHeight / 2 + screenHeight / 2, screenHeight - 1);

			unsigned int color = tileColors[hitTile];
			// side will bitshift colors so that they're halved
			SDL_SetRenderDrawColor(renderer, ((color >> 24) & 0xff) >> side, ((color >> 16) & 0xff) >> side, ((color >> 8) & 0xff) >> side, (color & 0xff) >> side);

			SDL_RenderDrawLineF(renderer, x, drawStart, x, drawEnd);
		}
	}
}
