#pragma once

#include "SDL_mouse.h"
#include "util.hpp"
#include <SDL.h>
#include <cstdlib>

namespace Input {
enum KeyFlag : unsigned char {
	Unpressed = 0b0000,
	Pressed = 0b0001,
	Held = 0b0010,
	Released = 0b0100,
};

struct Input {
	unsigned char *keyboard;
	unsigned char *mouse;
	vec2i mouseMotion, mouseRel;

	Input();

	void Update();
	void EventKeyUp(SDL_Event &event);
	void EventKeyDown(SDL_Event &event);
	void EventMouseMotion(SDL_Event &event);
	void EventMouseButtonDown(SDL_Event &event);
	void EventMouseButtonUp(SDL_Event &event);
	bool buttonReleased(unsigned int button);
	bool buttonHeld(unsigned int button);
	bool buttonPressed(unsigned int button);
	bool keyReleased(SDL_Scancode scancode);
	bool keyHeld(SDL_Scancode scancode);
	bool keyPressed(SDL_Scancode scancode);
};
}
