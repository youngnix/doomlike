#include "kinematics.hpp"
#include "player.hpp"


void raycast(Player &player) {

	int width {1};
	float dirX {cos(player.kinematics.angle)};
	float dirY {sin(player.kinematics.angle)};

	for (int ray = 0; ray < width; ray++) {

		// Calculate ray position and direction
		double cameraX = 2 * ray / double(width) - 1;
		double rayDirX = dirX + player.planeX * cameraX;
		double rayDirY = dirY + player.planeY * cameraX;
		
		// Which box of the map we are
		int mapX {int(player.rect.getPosition().x)};
		int mapY {int(player.rect.getPosition().y)};

		// Length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
	}

}