#pragma once

#include "input.hpp"
#include "kinematics.hpp"
#include "raycast.hpp"

class Player {
    public:
        Player();
        void Update(float delta);
        void Draw();
        Kinematics kinematics;
        Raycaster raycaster;
    	vec2 pos;
		void Update(Input::Input &input, float delta);
		SDL_Texture *texture_2d;
};
