#include "player.hpp"
#include "SDL_mouse.h"
#include "SDL_render.h"
#include "SDL_surface.h"
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

	SDL_Surface *surf = SDL_CreateRGBSurface(0, 16, 16, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	SDL_FillRect(surf, NULL, 0xFFFFFFFF);

	texture_2d = SDL_CreateTextureFromSurface(graphics.renderer, surf);

	SDL_FreeSurface(surf);
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
    	SDL_SetRelativeMouseMode(SDL_FALSE);
    }

    if (input.buttonPressed(SDL_BUTTON_LEFT))
    {
    	SDL_SetRelativeMouseMode(SDL_TRUE);
    }

    this->kinematics.angle -= rotate;

    this->kinematics.Apply(delta, direction);

    pos[0] += kinematics.velocity[0];
    pos[1] += kinematics.velocity[1];
}

void Player::Draw() {
    SDL_FRect rect = {pos[0], pos[1], 1, 1};
    SDL_FPoint center = {rect.w / 2, rect.h/2};

    SDL_RenderCopyExF(graphics.renderer, texture_2d, NULL, &rect, kinematics.angle, &center, SDL_FLIP_NONE);
}
