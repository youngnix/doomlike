#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include "tiles.hpp"
#include "raycast.hpp"
#include <cmath>

#define screenWidth 640
#define screenHeight 480

// Put a limit do DDA dont run a infinite distance
const float MAX_RAY_LENGTH = 300.0f;

// Defining colors for tiles
const sf::Color tileColors[] = {
    sf::Color::Transparent,       // TILES_EMPTY
    sf::Color(199, 56, 30, 255),  // TILES_BRICKS
    sf::Color(192, 112, 50, 255), // TILES_DIRT
    sf::Color(255, 240, 74, 255), // TILES_LIGHT
};

// Constructors using Initialization List
Raycaster::Raycaster() : planeX(0), planeY(0.66) {}
Raycaster::Raycaster(float planeX, float planeY) : planeX(planeX), planeY(planeY) {}

void calculateRayDirection(int x, float dirX, float dirY, float planeX, float planeY, double &rayDirX, double &rayDirY) {
    double cameraX = 2 * x / double(screenWidth) - 1;
    rayDirX = dirX + planeX * cameraX;
    rayDirY = dirY + planeY * cameraX;
}

bool performDDA(int &mapX, int &mapY, double rayDirX, double rayDirY, double &sideDistX, double &sideDistY, double deltaDistX, double deltaDistY, int &stepX, int &stepY, int &side, Tilemap &tilemap, TileType &hitTile) {
    while (mapX >= 0 && mapY >= 0 && mapX < tilemap.width && mapY < tilemap.height) {
        // Determine next position of ray using as a base which edge will be heat first
		if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        // Check collision with the tile
        hitTile = tilemap.tiles[mapY * tilemap.width + mapX];
        if (hitTile != TILES_EMPTY) {
            return true;
        }
    }
    return false;
}

void Raycaster::Cast(sf::RenderWindow &window, sf::Vector2f pos, float angle, Tilemap &tilemap) {
    float dirX = std::sin(angle);
    float dirY = -std::cos(angle);

    sf::VertexArray wallLines(sf::Lines);

    for (int x = 0; x < screenWidth; x++) {
        // Calculate ray position and direction
        double rayDirX, rayDirY;
        calculateRayDirection(x, dirX, dirY, planeX, planeY, rayDirX, rayDirY);

        int mapX = int(pos.x);
        int mapY = int(pos.y);

        double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

        double sideDistX = (rayDirX < 0) ? (pos.x - mapX) * deltaDistX : (mapX + 1.0 - pos.x) * deltaDistX;
        double sideDistY = (rayDirY < 0) ? (pos.y - mapY) * deltaDistY : (mapY + 1.0 - pos.y) * deltaDistY;

        int stepX = (rayDirX < 0) ? -1 : 1;
        int stepY = (rayDirY < 0) ? -1 : 1;

        int side;
        TileType hitTile = TILES_EMPTY;

        // Start DDA
        bool hit = performDDA(mapX, mapY, rayDirX, rayDirY, sideDistX, sideDistY, deltaDistX, deltaDistY, stepX, stepY, side, tilemap, hitTile);

        if (hit) {
            // Calculate Wall Distance
            double perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);

            // Determine the Height of the Line that will be drawn
            int lineHeight = std::min(int(screenHeight / perpWallDist), screenHeight);

            int drawStart = std::max(-lineHeight / 2 + screenHeight / 2, 0);
            int drawEnd = std::min(lineHeight / 2 + screenHeight / 2, screenHeight - 1);

            // Color and Shadow
            sf::Color color = tileColors[hitTile];
            if (side == 1) { // Escurecer para dar efeito 3D
                color.r /= 1.5;
                color.g /= 1.5;
                color.b /= 1.5;
            }

            // Add lines to VertexArray
            wallLines.append(sf::Vertex(sf::Vector2f(x, drawStart), color));
            wallLines.append(sf::Vertex(sf::Vector2f(x, drawEnd), color));
        }
    }

    window.draw(wallLines);
}