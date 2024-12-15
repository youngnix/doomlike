#include "kinematics.hpp"
#include "player.hpp"

#define screenWidth 640
#define screenHeight 480


void raycast(Player &player) {

	float dirX {cos(player.kinematics.angle)};
	float dirY {sin(player.kinematics.angle)};

	for (int ray = 0; ray < screenWidth; ray++) {

		// Calculate ray position and direction
		double cameraX = 2 * ray / double(screenWidth) - 1;
		double rayDirX = dirX + player.planeX * cameraX;
		double rayDirY = dirY + player.planeY * cameraX;
		
		// Which box of the map we are
		int mapX {int(player.rect.getPosition().x)};
		int mapY {int(player.rect.getPosition().y)};

		// Length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// Length of ray from one x or y-side to nex x or y-side
		double deltaDistX {(rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX)};
		double deltaDistY {(rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY)};
		double perpWallDist;

		int stepX, stepY;
		int hit {0};
		int side;

		// Calculate step and initial sideDist
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (player.rect.getPosition().x - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - player.rect.getPosition().x) * deltaDistX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (player.rect.getPosition().y - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - player.rect.getPosition().y) * deltaDistY;
		}

		// Perform DDA
		while (hit == 0) {
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
			/*if (worldMap[mapX][mapY] > 0) {
				hit = 1;
			}*/
		}

		// Calculate distance projected on camera direction
		if (side==0) {
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

	}

}