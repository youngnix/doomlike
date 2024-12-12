#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

class Player
{
public:
	Player();
    void Update();
	void Draw(sf::RenderWindow &w);
private:
    sf::RectangleShape rect;
};
