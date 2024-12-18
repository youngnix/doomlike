#pragma once

#include "input.hpp"
#include "kinematics.hpp"
#include "raycast.hpp"

class Player {
    public:
        Player();
        Player(SDL_Renderer *renderer);
        void Update(float delta);
        void Draw(SDL_Renderer *r);
        Kinematics kinematics;
        Raycaster raycaster;
    	vec2 pos;
		void Update(Input::Input &input, float delta);
		SDL_Texture *texture_2d;
};
