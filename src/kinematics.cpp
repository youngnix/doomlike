#include "kinematics.hpp"
#include "SFML/System/Vector2.hpp"
#include <cmath>

Kinematics::Kinematics(float speed, float accel, float decel)
{
    this->speed = speed;
    this->accel = accel;
    this->decel = decel;
}

static sf::Vector2f lerpVector2f(sf::Vector2f a, sf::Vector2f b, float c) {
	return sf::Vector2f(a.x + c * (b.x - a.x), a.y + c * (b.y - a.y));
}

sf::Vector2f Kinematics::ApplyVector(float delta, sf::Vector2<float> direction) {
    float length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));

    if (length != 0)
    {
        direction /= length;
    }

    // whether we should accelerate or decelerate
    if (direction != sf::Vector2<float>()) {
    	this->velocity = lerpVector2f(this->velocity, direction * this->speed * delta, this->accel);
    } else {
    	this->velocity = lerpVector2f(this->velocity, sf::Vector2f(), this->decel);
    }

    return this->velocity;
}
