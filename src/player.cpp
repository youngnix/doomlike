#include <SDL3/SDL.h>
#include "player.hpp"
#include "SDL3/SDL_render.h"
#include "graphics.hpp"
#include "input.hpp"
#include "kinematics.hpp"
#include <cmath>

namespace MathUtils {
    constexpr float PI = 3.1415926;
    inline float rad_to_deg(float rad) {
	    return rad * 180 / PI;
    }

    inline float deg_to_rad(float deg) {
	    return deg * PI / 180.0;
    }
}

// Player contructor and enable the kinematics of the character with speed of 300, 1.2 of acceleration and 0.6 of desacceleration
Player::Player() : kinematics(10, 1.2, 0.6), pos{10.0f, 10.0f} {
	kinematics.angle = MathUtils::deg_to_rad(90);

    // Create surface and texture to player
	SDL_Surface *surf = SDL_CreateSurface(16, 16, SDL_PIXELFORMAT_RGBA32);
    if (!surf) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SURFACE_ERROR: %s", SDL_GetError());
        return;
    }

	SDL_FillSurfaceRect(surf, NULL, 0xFFFFFFFF);
	texture_2d = SDL_CreateTextureFromSurface(graphics.renderer, surf);
    SDL_DestroySurface(surf);
}

void Player::Update(Input::Input &input, float delta) {
    // Determine direction based on input axis
    vec2 direction = {
        static_cast<float>(input.keyHeld(SDL_SCANCODE_D) - input.keyHeld(SDL_SCANCODE_A)),
        static_cast<float>(input.keyHeld(SDL_SCANCODE_S) - input.keyHeld(SDL_SCANCODE_W)),
    };

    float rotate = MathUtils::deg_to_rad(-input.mouseRel[0]) * 0.5;
    kinematics.angle -= rotate;

    if (input.keyPressed(SDL_SCANCODE_ESCAPE)) {
        SDL_SetWindowRelativeMouseMode(graphics.window, false);
        SDL_ShowCursor();
    }

    if (input.buttonPressed(SDL_BUTTON_LEFT)) {
    	SDL_SetWindowRelativeMouseMode(graphics.window, true);
        SDL_HideCursor();
    }

    kinematics.Apply(delta, direction);
    pos[0] += kinematics.velocity[0];
    pos[1] += kinematics.velocity[1];

}

void Player::Draw() {
    SDL_FRect rect = {pos[0], pos[1], 1.0f, 1.0f};
    SDL_FPoint center = {rect.w / 2.0f, rect.h/2.0f};
    SDL_RenderTextureRotated(graphics.renderer, texture_2d, nullptr, &rect, kinematics.angle, &center, SDL_FLIP_NONE);
}
