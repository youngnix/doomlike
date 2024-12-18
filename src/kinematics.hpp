#pragma once

#include "util.hpp"

// The kinematics component should be used with entities that move.
class Kinematics {
  public:
    float speed;
    vec2 velocity;

    float accel;
    float decel;
    float angle;

    Kinematics(float speed, float accel, float decel);
    // Apply will store velocity based on factors like acceleration, deceleration, friction, speed and angle.
    void Apply(float delta, vec2 direction);
};
