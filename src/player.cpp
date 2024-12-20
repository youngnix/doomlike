#include <SDL3/SDL.h>
#include "player.hpp"
#include "SDL3/SDL_render.h"
#include "graphics.hpp"
#include "input.hpp"
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
	this->pos[0] = 1;
	this->pos[1] = 1;
	kinematics.angle = deg_to_rad(90);

	SDL_Surface *surf = SDL_CreateSurface(16, 16, SDL_PIXELFORMAT_RGBA32);

	SDL_FillSurfaceRect(surf, NULL, 0xFFFFFFFF);

	texture_2d = SDL_CreateTextureFromSurface(graphics.renderer, surf);
}

void Player::Update(Input::Input &input, float delta) {
    // Determine direction based on input axis
    vec2 direction = {
        static_cast<float>(input.keyHeld(SDL_SCANCODE_D) - input.keyHeld(SDL_SCANCODE_A)),
        static_cast<float>(input.keyHeld(SDL_SCANCODE_S) - input.keyHeld(SDL_SCANCODE_W)),
    };

    float rotate = deg_to_rad(-input.mouseRel[0]) * 0.5;

    if (input.keyPressed(SDL_SCANCODE_ESCAPE))
    {
    	SDL_SetWindowRelativeMouseMode(graphics.window, true);
    }

    if (input.buttonPressed(SDL_BUTTON_LEFT))
    {
    	SDL_SetWindowRelativeMouseMode(graphics.window, false);
    }

    this->kinematics.angle -= rotate;

    this->kinematics.Apply(delta, direction);

    pos[0] += kinematics.velocity[0];
    pos[1] += kinematics.velocity[1];
}

void Player::Draw() {
    SDL_FRect rect = {pos[0], pos[1], 1, 1};
    SDL_FPoint center = {rect.w / 2, rect.h/2};

    SDL_RenderTextureRotated(graphics.renderer, texture_2d, NULL, &rect, kinematics.angle, &center, SDL_FLIP_NONE);
}
