#include "tiles.hpp"
#include "graphics.hpp"
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <SDL3/SDL.h>

Tile::Tile() : type(TILES_EMPTY) {}

Tile::Tile(TileType type) : type(type) {}

Tilemap::Tilemap(std::string path) : width(0), height(0) {
    std::ifstream ifs(path);
    if (!ifs) {
        throw std::runtime_error("Failed to open tilemap file.");
    }

    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    
    int lineLength = 0;
    int start = 0;
    int len = 0;
    vec2 pos{0, 0};

    // Calculate the proportion of the map before to check the file
    for (const char c : content) {
        lineLength++;
        if (width < lineLength) {
            width = lineLength;
        }

        if (c == '\n') {
            height++;
            lineLength = 0;
        }
    }

    tiles.resize(width * height);

    // Check the content of the file
    for (size_t i = 0; i < content.size(); i++) {
        char c = content[i];

        // Check if the character is between the inteval numeric
        if (c >= '0' && c <= '9') {
            len = i - start + 1;
        }

        // Ignore spaces
        if (c == ' ') {
            len = i - start + 1;
            continue;
        }

        // Check numbers of tiles and add them to the list
        if (c == '\n' || c == ',') {
            std::string sub = content.substr(start, len);
            TileType type = static_cast<TileType>(std::atoi(sub.c_str()));

            this->SetTile(pos, type);

            // Update position
            if (c == '\n') {
                pos[0] = 0;
                pos[1]++;
            } else {
                pos[0]++;
            }

            start = i + 1;
        }
    }
}

void Tilemap::SetTile(vec2 pos, TileType type) {
    // Check if the tile type in inside of the valid limits
    if (type <= TILES_EMPTY || type >= TILES_COUNT) {
        return;
    }

    // Adjust linear index to storage the tile type
    tiles[pos[1] * width + pos[0]] = type;
}

void Tilemap::Draw() {
    // Iteraction with tiles
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            TileType tile = tiles[i * width + j];
            if (tile == TILES_EMPTY) {
                continue; // Jump empty tiles
            }

            SDL_FRect rect = { static_cast<float>(j), static_cast<float>(i), 1.0f, 1.0f };

            // Define render color
            SDL_SetRenderDrawColor(graphics.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderFillRect(graphics.renderer, &rect);
        }
    }
}