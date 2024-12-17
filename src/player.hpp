#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "kinematics.hpp"
#include "raycast.hpp"

class Player {
    public:
        Player();
        void Update(float delta);
        void Draw(sf::RenderWindow &w);
        Kinematics kinematics;
        Raycaster raycaster;
    	float x, y;
        sf::RectangleShape rect;
};
