#include "input.hpp"
#include <cstdio>

Input::Input::Input() {
	keyboard = (unsigned char *)calloc(SDL_NUM_SCANCODES, (sizeof *keyboard));
}

void Input::Input::Update() {
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		// If key released, turn off all flags
		if (keyboard[i] == KeyFlag::Released) {
			keyboard[i] = KeyFlag::Unpressed;
		}

		// If pressed bitfield is on, disable it
		if (keyboard[i] & KeyFlag::Pressed) {
			keyboard[i] &= ~KeyFlag::Pressed;
		}
	}
}

void Input::Input::EventKeyDown(SDL_Event &event) {
	// turns pressed and held bitfields on
	if (!event.key.repeat)
	{
		keyboard[event.key.keysym.scancode] |= KeyFlag::Pressed | KeyFlag::Held;
	}
}

void Input::Input::EventKeyUp(SDL_Event &event) {
	keyboard[event.key.keysym.scancode] = KeyFlag::Released;
}

bool Input::Input::keyReleased(SDL_Scancode scancode) {
	return keyboard[scancode] & KeyFlag::Released;
}

bool Input::Input::keyHeld(SDL_Scancode scancode) {
	return keyboard[scancode] & KeyFlag::Held;
}

bool Input::Input::keyPressed(SDL_Scancode scancode) {
	return keyboard[scancode] & KeyFlag::Pressed;
}
