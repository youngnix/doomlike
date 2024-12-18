#include "kinematics.hpp"
#include <cmath>

Kinematics::Kinematics(float speed, float accel, float decel) {
    this->speed = speed;
    this->accel = accel;
    this->decel = decel;
    this->angle = 0;
    this->velocity[0] = 0;
    this->velocity[1] = 0;
}

// Linearly interpolates a Vector2. This function should be eventually moved.
static void lerpVector2f(vec2 a, vec2 b, float c, vec2 res) {
    res[0] = a[0] + c * (b[0] - a[0]);
    res[1] = a[1] + c * (b[1] - a[1]);
}

void Kinematics::Apply(float delta, vec2 direction) {
    // Normalizes the vector in case it is not normalized using the pythagorean theorem.
    float length = std::sqrt(std::pow(direction[0], 2) + std::pow(direction[1], 2));
    if (length != 0) {
        direction[0] /= length;
        direction[1] /= length;
    }

    // Rotate our direction vector accordingly to our angle
    float x = direction[0] * cos(this->angle) - direction[1] * sin(this->angle);
    float y = direction[0] * sin(this->angle) + direction[1] * cos(this->angle);

    direction[0] = x;
    direction[1] = y;

    // whether we should accelerate or decelerate based off of the input
    if (direction[0] != 0 || direction[1] != 0)
    {
        vec2 finalDir = {
			direction[0] * speed * delta,
			direction[1] * speed * delta,
        };

        lerpVector2f(this->velocity, finalDir, accel, velocity);
    }
    else
	{
        vec2 zero = { 0, 0 };
        lerpVector2f(this->velocity, zero, decel, velocity);
    }
}
