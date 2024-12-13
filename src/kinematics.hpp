#pragma once

#include "SFML/System/Vector2.hpp"
class Kinematics
{
  public:
    float speed;
    sf::Vector2<float> velocity;

    float accel;
    float decel;

    Kinematics(float speed, float accel, float decel);
    sf::Vector2f ApplyVector(float delta, sf::Vector2<float> direction);
    sf::Vector2f ApplyRadians(float delta, float angle);
};
