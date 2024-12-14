#include "kinematics.hpp"
#include "SFML/System/Vector2.hpp"
#include <cmath>

Kinematics::Kinematics(float speed, float accel, float decel) {

    this->speed = speed;
    this->accel = accel;
    this->decel = decel;

}

static sf::Vector2f lerpVector2f(sf::Vector2f a, sf::Vector2f b, float c) {

    return sf::Vector2f(a.x + c * (b.x - a.x), a.y + c * (b.y - a.y));

}

sf::Vector2f Kinematics::Apply(float delta, sf::Vector2<float> input) {

    float length = std::sqrt(std::pow(input.x, 2) + std::pow(input.y, 2));

    if (length != 0) {
        input /= length;
    }

    float x = input.x * cos(this->angle) - input.y * sin(this->angle);
    float y = input.x * sin(this->angle) + input.y * cos(this->angle);

    input.x = x;
    input.y = y;

    // whether we should accelerate or decelerate
    if (input != sf::Vector2<float>()) {
        this->velocity = lerpVector2f(this->velocity, input * this->speed * delta, this->accel);
    } else {
        this->velocity = lerpVector2f(this->velocity, sf::Vector2f(), this->decel);
    }

    return this->velocity;

}
