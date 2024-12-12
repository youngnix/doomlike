#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/OpenGL.hpp"
#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include "player.hpp"

int
main(void)
{
    // Configures the OpenGL context used by SFML
    sf::ContextSettings settings;

    settings.majorVersion = 3;
    settings.minorVersion = 3;

    sf::RenderWindow window(sf::VideoMode(640, 360), "doomlike", sf::Style::Default, settings);

    Player player;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            default:
                break;
            }
        }

        player.Update();

        window.clear();

        player.Draw(window);

        window.display();
    }
    return 0;
}
