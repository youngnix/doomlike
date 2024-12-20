#include "tilemap.hpp"
#include "graphics.hpp"
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <SDL3/SDL.h>

Tile::Tile() {
	this->type = TILES_EMPTY;
}

Tile::Tile(TileType type) {
	this->type = type;
}

Tilemap::Tilemap(std::string path) {
	width = 0;
	height = 0;

	std::ifstream ifs(path);

	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	int start = 0;
	int len = 0;
	vec2 pos;

	int lineLength = 0;

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

	tiles.resize(width * height);

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
			TileType type = (TileType)std::atoi(sub.c_str());

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

void Tilemap::SetTile(vec2 pos, TileType type) {
	if (type <= TILES_EMPTY || type >= TILES_COUNT) {
		return;
	}

	this->tiles[pos[1] * width + pos[0]] = type;
}

void Tilemap::Draw() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (tiles[i * width + j] == TILES_EMPTY) {
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
