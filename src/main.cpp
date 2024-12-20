#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <cassert>
#include <cmath>
#include "graphics.hpp"
#include "input.hpp"
#include "player.hpp"
#include "tilemap.hpp"

int main(void)
{
    bool running = true;

    // Initialize the player
    Player player;
	Input::Input input;

	Tilemap tilemap("./res/map01.txt");

    double startTime = (double)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency() / 1000.0;
    double endTime = startTime;
    double deltaTime = INFINITY;
    // Main Loop that have the responsibility to update the Delta Time, update the Player and render this in the window
    while (running)
    {
    	deltaTime = (endTime - startTime) / SDL_GetPerformanceFrequency();
    	startTime = SDL_GetPerformanceCounter();

    	SDL_Event event;
    	input.Update();
        
        // Window Events that for now we have just the close event
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
            case SDL_EVENT_MOUSE_BUTTON_DOWN: 
            	input.EventMouseButtonDown(event);
            	break;
            case SDL_EVENT_MOUSE_MOTION:
            	input.EventMouseMotion(event);
            	break;
            case SDL_EVENT_KEY_DOWN:
            	input.EventKeyDown(event);
            	break;
            case SDL_EVENT_KEY_UP:
            	input.EventKeyUp(event);
            	break;
            case SDL_EVENT_QUIT: {
                running = false;
                break;
            }
            default:
                break;
            }
        }

        player.Update(input, deltaTime);

		graphics.Begin();

        player.Draw();
        tilemap.Draw();

    	player.raycaster.Draw(player.pos, player.kinematics.angle, tilemap);

		graphics.End();

    	endTime = SDL_GetPerformanceCounter();
    }

    return 0;
}
