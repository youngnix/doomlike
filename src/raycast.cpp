#include <SDL.h>
#include "tiles.hpp"
#include "raycast.hpp"
#include <cmath>

#define screenWidth 640
#define screenHeight 480

Raycaster::Raycaster() {
	this->planeX = 0;
	this->planeY = 0.66;
}

Raycaster::Raycaster(float planeX, float planeY) {
	this->planeX = planeX;
	this->planeY = planeY;
}

void Raycaster::Cast(SDL_Renderer *renderer, vec2 pos, float angle, Tilemap &tilemap) {
	float dirX = std::sin(angle);
	float dirY = -std::cos(angle);

	for (int x = 0; x < screenWidth; x++) {
		// Calculate ray position and direction
		double cameraX = 2 * x / double(screenWidth) - 1;

		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		
		// Which box of the map we are
		int mapX = pos[0];
		int mapY = pos[1];

		// Length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// Length of ray from one x or y-side to nex x or y-side
		double deltaDistX = std::abs(1 / rayDirX);
		double deltaDistY = std::abs(1 / rayDirY);

		double perpWallDist;

		int stepX, stepY;
		int hit = 0;
		int side;

		// Calculate step and initial sideDist
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (pos[0] - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - pos[0]) * deltaDistX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (pos[1] - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - pos[1]) * deltaDistY;
		}

		float maxLength = 300;
		float length = 0;
		TileType hitTile = TILES_EMPTY;

		// Perform DDA
		while (!hit && length < maxLength) {
			// Jump to next map square, either in x-direction, or in y-direction
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

			if (mapX >= 0 && mapY >= 0
			&& mapX < tilemap.width && mapY < tilemap.height)
			{
				// Check if ray has hit a wall
				hitTile = tilemap.tiles[mapY * tilemap.width + mapX];

				if (hitTile != TILES_EMPTY) {
					hit = 1;
				}
			}
		}

		if (hit) {
			// Calculate distance projected on camera direction
			if (side == 0) {
				perpWallDist = (sideDistX - deltaDistX);
			} else {
				perpWallDist = (sideDistY - deltaDistY);
			}

			// Calculate height of line to draw on screen
			int lineHeight = screenHeight / perpWallDist;

			// Calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + screenHeight / 2;
			if (drawStart < 0) {
				drawStart = 0;
			}

			int drawEnd = lineHeight / 2 + screenHeight / 2;
			if (drawEnd >= screenHeight) {
				drawEnd = screenHeight - 1;
			}

			unsigned int color;
			switch (hitTile) {
				case TILES_BRICKS:
					color = 0xc7381eFF;
					break;
				case TILES_DIRT:
					color = 0xc07032FF;
					break;
				case TILES_LIGHT:
					color = 0xfff04aff;
					break;
				default:
					continue;
			}

			SDL_SetRenderDrawColor(renderer, (color >> 24) & 0xff, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);

			SDL_RenderDrawLineF(renderer, x, drawStart, x, drawEnd);
		}
	}
}
