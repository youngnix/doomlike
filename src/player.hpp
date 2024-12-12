#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

class Player
{
public:
	Player();
	void Update(float delta);
	void Draw(sf::RenderWindow &w);
	float speed;
private:
    sf::RectangleShape rect;
};
