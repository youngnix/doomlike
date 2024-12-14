#include "player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "kinematics.hpp"
#include <cmath>

#define PI 3.1415926

static float rad_to_deg(float rad) {
	return rad * 180 / PI;
}

static float deg_to_rad(float deg) {
	return deg * PI / 180.0;
}

// Player contructor and enable the kinematics of the character with speed of 300, 1.2 of acceleration and 0.6 of desacceleration
Player::Player() : kinematics(300, 1.2, 0.6) {
	this->rect.setPosition(0, 0);
	this->rect.setSize(sf::Vector2f(16, 16));
	this->rect.setOrigin(this->rect.getSize().x / 2, this->rect.getSize().y / 2);
	kinematics.angle = 90 * PI / 180;
}

void Player::Update(float delta) {
    // Determine direction based on input axis
    sf::Vector2<float> input = {
        static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)),
        static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)),
    };

    float rotate = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) - sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    this->kinematics.angle -= deg_to_rad(rotate * 360) * delta;

    auto pos = this->kinematics.Apply(delta, input);

    this->rect.setPosition(this->rect.getPosition() + pos);
    this->rect.setRotation(this->kinematics.angle * 180/PI);
}

void Player::Draw(sf::RenderWindow &w) {
    w.draw(this->rect);
}
