#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "kinematics.hpp"

class Player
{
  public:
    Player();
    void Update(float delta);
    void Draw(sf::RenderWindow &w);

  private:
    Kinematics kinematics;
    sf::RectangleShape rect;
};
