#pragma once

#include "util.hpp"
#include <string>
#include <vector>
#include <SDL3/SDL.h>

enum TileType : int
{
    Bricks,
    Dirt,
    Light,
    Count,
};

class Tile
{
public:
    TileType type;
    unsigned int color;
    SDL_Surface *texture;

    Tile();
    Tile(TileType type, unsigned int color, std::string texture_path);
};

class Tilemap
{
public:
    int width, height;

	Tilemap();
	Tilemap(std::vector<int> data);
	Tilemap(std::string path);

	void Draw();
	void LoadFromFile(std::string path);
	void SetTile(vec2i pos, TileType type);
	Tile *GetTile(vec2i pos);
	Tile *GetTile(int x, int y);
private:
	std::vector<Tile*> map;
	std::vector<Tile> tiles;
};
