#pragma once

#include "util.hpp"
#include <string>
#include <vector>

enum TileType
{
    TILES_EMPTY,
    TILES_BRICKS,
    TILES_DIRT,
    TILES_LIGHT,
    TILES_COUNT,
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

	void Draw();
	void LoadFromFile(std::string path);
	void SetTile(vec2 pos, TileType type);
};
