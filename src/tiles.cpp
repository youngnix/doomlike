#include "tiles.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <fstream>
#include <cmath>

Tile::Tile() {
	this->type = TILES_EMPTY;
}

Tile::Tile(TileType type) {
	this->type = type;
}

Tilemap::Tilemap(std::string path) {
	std::ifstream ifs(path);

	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	int start = 0;
	int len = 0;
	sf::Vector2i pos;

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

			pos.x++;

			if (c == '\n') {
				pos.x = 0;
				pos.y += 1;
			}

			start = i+1;
		}
	}
}

void Tilemap::SetTile(sf::Vector2i pos, TileType type) {
	if (type <= TILES_EMPTY || type >= TILES_COUNT) {
		return;
	}

	this->tiles[pos] = Tile(type);
}

void Tilemap::Draw(sf::RenderWindow &w) {
	for (const auto &[k, v] : this->tiles) {
		sf::RectangleShape shape;

		shape.setSize(sf::Vector2f(16, 16));
		shape.setPosition(k.x * shape.getSize().x, k.y * shape.getSize().y);

		w.draw(shape);
	}
}
