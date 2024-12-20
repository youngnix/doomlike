#include "tilemap.hpp"
#include "graphics.hpp"
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Tile::Tile() {
	this->type = (TileType)-1;
	this->color = 0x00000000;
	this->texture = NULL;
}

Tile::Tile(TileType type, unsigned int color, std::string texture_path) {
	this->type = type;
	this->color = color;
	this->texture = IMG_Load(texture_path.c_str());

	this->texture = SDL_ConvertSurface(this->texture, SDL_PIXELFORMAT_ABGR32);

	assert(this->texture);
}

Tilemap::Tilemap(std::string path) {
	width = 0;
	height = 0;

	std::ifstream ifs(path);

	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	int start = 0;
	int len = 0;
	vec2i pos;

	int lineLength = 0;
	
	tiles.resize(TileType::Count);

	tiles[TileType::Bricks] = Tile(TileType::Bricks, 0xFFFFFFFF, "res/tile_bricks.png");

	// calculate map proportions before parsing map file
	for (unsigned long i = 0; i < content.size(); i++) {
		lineLength += 1;

		if (width < lineLength) {
			width = lineLength;
		}

		if (content[i] == '\n') {
			lineLength = 0;
			height++;
		}
	}

	map.resize(width * height);

	for (unsigned long i = 0; i < content.size(); i++) {
		char c = content[i];

		// Checking whether c is in the numbers range of the ASCII standard
		if (c >= '0' && c <= '9') {
			len = i - start + 1;
		}

		// ignore spaces for the sake of formatting
		if (c == ' ') {
			len = i - start + 1;
			continue;
		}

		// we'll parse tile numbers and add the tiles to our map. This method allows for varying line lengths 
		if (c == '\n' || c == ',') {
			std::string sub = content.substr(start, len);
			TileType type = TileType(std::atoi(sub.c_str()) - 1);

			this->SetTile(pos, type);

			pos[0]++;

			if (c == '\n') {
				pos[0] = 0;
				pos[1] += 1;
			}

			start = i+1;
		}
	}
}

void Tilemap::SetTile(vec2i pos, TileType type) {
	if (pos[0] < 0 || pos[1] >= this->width) {
		return;
	}

	if (pos[1] < 0 || pos[1] >= this->height) {
		return;
	}

	if (type < TileType::Bricks || type >= TileType::Count) {
		this->map[pos[1] * width + pos[0]] = NULL;
		return;
	}

	this->map[pos[1] * width + pos[0]] = &this->tiles[type];
}


Tile *Tilemap::GetTile(int x, int y) {
	if (x < 0 || x >= this->width) {
		return NULL;
	}

	if (y < 0 || y >= this->height) {
		return NULL;
	}

	return this->map[width * y + x];
}

Tile *Tilemap::GetTile(vec2i pos) {
	if (pos[0] < 0 || pos[0] >= this->width) {
		return NULL;
	}

	if (pos[1] < 0 || pos[1] >= this->height) {
		return NULL;
	}

	return this->map[width * pos[1] + pos[0]];
}

void Tilemap::Draw() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Tile *tile = GetTile(j, i);

			if (!tile) {
				continue;
			}

			SDL_FRect rect = {
				(float)j,
				(float)i,
				1,
				1,
			};

			SDL_SetRenderDrawColor(graphics.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			SDL_RenderFillRect(graphics.renderer, &rect);
		}
	}
}
