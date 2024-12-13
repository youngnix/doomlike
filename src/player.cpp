#include "player.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "kinematics.hpp"
#include <cmath>

Player::Player() : kinematics(300, 1.2, 0.6)
{
	this->rect.setPosition(0, 0);
	this->rect.setSize(sf::Vector2f(16, 16));
}

void
Player::Update(float delta)
{
    // Determine direction based on input axis
    sf::Vector2<float> direction = {
        static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)),
        static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)),
    };

    auto pos = this->kinematics.ApplyVector(delta, direction);

    this->rect.setPosition(this->rect.getPosition() + pos);
}

void
Player::Draw(sf::RenderWindow &w)
{
    w.draw(this->rect);
}
