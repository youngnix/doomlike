#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <map>
#include <string>
#include <unordered_map>

enum TileType
{
    TILES_EMPTY,
    TILES_WALL,
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
	std::unordered_map<sf::Vector2i, Tile, HashVector2i> tiles;

	Tilemap();
	Tilemap(std::vector<int> data);
	Tilemap(std::string path);

	void Draw(sf::RenderWindow &w);
	void LoadFromFile(std::string path);
	void SetTile(sf::Vector2i pos, TileType type);
};
