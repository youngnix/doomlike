#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "player.hpp"
#include "tiles.hpp"

#define screenWidth 640
#define screenHeight 480

int main(void)
{
    // Configures the OpenGL context used by SFML
    sf::ContextSettings settings;

    // Define the OpenGL 3.3
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    // sf::RenderWindow window() create a window called doonlike, set a size for this window, use the default style for this an apply the opengl settings
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "doomlike", sf::Style::Default, settings);

    // Initialize the player
    Player player;

    // Get Delta Time
	sf::Clock clock;

	Tilemap tilemap("../res/map01.txt");

    // Main Loop that have the responsibility to update the Delta Time, update the Player and render this in the window
    while (window.isOpen())
    {
    	float delta = clock.restart().asSeconds();
        sf::Event event;

        // Window Events that for now we have just the close event
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: {
                window.close();
                break;
            }
            default:
                break;
            }
        }

        player.Update(delta);

        window.clear();

        player.Draw(window);
        tilemap.Draw(window);

        window.display();

    }

    return 0;
}
