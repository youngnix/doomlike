#include <SDL.h>
#include <cmath>
#include "SDL_render.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "input.hpp"
#include "player.hpp"
#include "tiles.hpp"

#define screenWidth 640
#define screenHeight 480

int main(void)
{
	SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("DOOMLIKE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetWindowResizable(window, SDL_FALSE);

    bool running = true;

    // Initialize the player
    Player player(renderer);
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
            case SDL_KEYDOWN:
            	input.EventKeyDown(event);
            	break;
            case SDL_KEYUP:
            	input.EventKeyUp(event);
            	break;
            case SDL_QUIT: {
                running = false;
                break;
            }
            default:
                break;
            }
        }

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        player.Update(input, deltaTime);
        printf("%f\n", deltaTime);

    	player.raycaster.Cast(renderer, player.pos, player.kinematics.angle, tilemap);

        player.Draw(renderer);
        tilemap.Draw(renderer);

        SDL_RenderPresent(renderer);

    	endTime = SDL_GetPerformanceCounter();
    }

    return 0;
}
