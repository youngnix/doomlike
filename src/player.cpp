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
Player::Player() : kinematics(10, 1.2, 0.6) {
	this->x = 0;
	this->y = 0;
	this->rect.setSize(sf::Vector2f(5, 5));
	this->rect.setOrigin(this->rect.getSize().x / 2, this->rect.getSize().y / 2);
	kinematics.angle = deg_to_rad(90);
}

void Player::Update(float delta) {
    // Determine direction based on input axis
    sf::Vector2<float> input = {
        static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A)),
        static_cast<float>(sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)),
    };

    float rotate = deg_to_rad(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) - sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) * 360 * delta;

    this->kinematics.angle -= rotate;

    auto pos = this->kinematics.Apply(delta, input);

    x += pos.x;
    y += pos.y;
    this->rect.setPosition(x, y);
    this->rect.setRotation(rad_to_deg(this->kinematics.angle));

    this->raycaster.planeX = 0.68 * cos(this->kinematics.angle);
    this->raycaster.planeY = 0.68 * sin(this->kinematics.angle);
}

void Player::Draw(sf::RenderWindow &w) {
    w.draw(this->rect);
}
