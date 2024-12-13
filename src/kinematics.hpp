#pragma once

#include "SFML/System/Vector2.hpp"

// The kinematics component should be used with entities that move.
class Kinematics
{
  public:
    float speed;
    sf::Vector2<float> velocity;

    float accel;
    float decel;
    float angle;

    Kinematics(float speed, float accel, float decel);
    // Apply will store velocity based on factors like acceleration, deceleration, friction, speed and angle.
    sf::Vector2f Apply(float delta, sf::Vector2<float> input);
};
