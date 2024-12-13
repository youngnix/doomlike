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
	this->rect.setOrigin(this->rect.getSize().x / 2, this->rect.getSize().y / 2);
	kinematics.angle = 90 * 3.14 / 180;
}

void
Player::Update(float delta)
{
    // Determine direction based on input axis
    sf::Vector2<float> input = {
        static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)),
        static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)),
    };

    float rotate = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) - sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    this->kinematics.angle -= rotate * 90 * (3.14 / 180) * delta;

    auto pos = this->kinematics.Apply(delta, input);

    this->rect.setPosition(this->rect.getPosition() + pos);
    this->rect.setRotation(this->kinematics.angle * 180/3.1415);
}

void
Player::Draw(sf::RenderWindow &w)
{
    w.draw(this->rect);
}
