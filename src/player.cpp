#include "player.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <cmath>

Player::Player()
{
    this->rect.setSize(sf::Vector2<float>(16, 16));
    this->speed = 200;
}

void
Player::Update(float delta)
{
    // Determine direction based on input axis
    sf::Vector2<float> direction = {
    	static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)),
    	static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)),
	};

	float length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));

	if (length != 0) {
		direction /= length;
	}

	this->rect.setPosition(this->rect.getPosition() + direction * this->speed * delta);
}

void
Player::Draw(sf::RenderWindow &w)
{
    w.draw(this->rect);
}
