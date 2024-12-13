#pragma once

#include "SFML/System/Vector2.hpp"
class Kinematics
{
  public:
    float speed;
    sf::Vector2<float> velocity;

    float accel;
    float decel;
    float angle;

    Kinematics(float speed, float accel, float decel);
    sf::Vector2f Apply(float delta, sf::Vector2<float> input);
};
