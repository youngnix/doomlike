#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <string>
#include <unordered_map>

enum TileType
{
    TILES_EMPTY,
    TILES_BRICKS,
    TILES_DIRT,
    TILES_LIGHT,
    TILES_COUNT,
};

struct HashVector2i {
    std::size_t operator()(const sf::Vector2i& v) const {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
    }
};

class Tile
{
public:
    TileType type;
    Tile();
    Tile(TileType type);
};

class Tilemap
{
public:
    int width, height;
	std::vector<TileType> tiles;

	Tilemap();
	Tilemap(std::vector<int> data);
	Tilemap(std::string path);

	void Draw(sf::RenderWindow &w);
	void LoadFromFile(std::string path);
	void SetTile(sf::Vector2i pos, TileType type);
};
