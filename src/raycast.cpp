#include "SFML/Graphics/PrimitiveType.hpp"
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

void Raycaster::Cast(sf::RenderWindow &window, sf::Vector2i pos, float angle, Tilemap &tilemap) {
	float dirX = std::cos(angle);
	float dirY = std::sin(angle);

	for (int x = 0; x < screenWidth; x++) {
		// Calculate ray position and direction
		double cameraX = 2 * x / double(screenWidth) - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		
		// Which box of the map we are
		int mapX = int(pos.x);
		int mapY = int(pos.y);

		// Length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// Length of ray from one x or y-side to nex x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
		double perpWallDist;

		int stepX, stepY;
		int hit = 0;
		int side;

		// Calculate step and initial sideDist
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (pos.x - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - pos.x) * deltaDistX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (pos.y - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - pos.y) * deltaDistY;
		}

		// Perform DDA
		while (!hit) {
			// Jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			// Check if ray has hit a wall
			if (tilemap.tiles.count(sf::Vector2i(mapX / 16, mapY / 16)) && tilemap.tiles[{mapX / 16, mapY / 16}].type) {
				hit = 1;
			}
		}

		// Calculate distance projected on camera direction
		if (side == 0) {
			perpWallDist = (sideDistX - deltaDistX);
		} else {
			perpWallDist = (sideDistY - deltaDistY);
		}

		// Calculate height of line to draw on screen
		int lineHeight {(int)(screenHeight / perpWallDist)};

		// Calculate lowest and highest pixel to fill in current stripe
		int drawStart {-lineHeight / 2 + screenHeight / 2};
		if (drawStart < 0) {
			drawStart = 0;
		}

		int drawEnd {lineHeight / 2 + screenHeight / 2};
		if (drawEnd >= screenHeight) {
			drawEnd = screenHeight - 1;
		}

		sf::Vertex line[2] = {
			sf::Vertex(sf::Vector2f(x, drawStart)),
			sf::Vertex(sf::Vector2f(x, drawEnd)),
		};

		window.draw(line, 2, sf::Lines);
	}
}
