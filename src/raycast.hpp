#pragma once

#include "SFML/System/Vector2.hpp"
#include "tiles.hpp"

struct Raycaster {
	float planeX, planeY;

	Raycaster();
	Raycaster(float planeX, float planeY);
	void Cast(sf::RenderWindow &window, sf::Vector2i pos, float angle, Tilemap &tilemap);
};
