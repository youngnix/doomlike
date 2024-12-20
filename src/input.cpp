#include "input.hpp"
#include <cstdio>

Input::Input::Input() {
	keyboard = (unsigned char *)calloc(SDL_SCANCODE_COUNT, (sizeof *keyboard));
	mouse = (unsigned char *)calloc(SDL_BUTTON_X2, (sizeof *mouse));
}

void Input::Input::Update() {
	mouseRel[0] = 0;
	mouseRel[1] = 0;

	for (int i = 0; i < SDL_BUTTON_X2; i++) {
		if (mouse[i] == KeyFlag::Released) {
			mouse[i] = KeyFlag::Unpressed;
		}

		if (mouse[i] & KeyFlag::Pressed) {
			mouse[i] &= ~KeyFlag::Pressed;
		}
	}

	for (int i = 0; i < SDL_SCANCODE_COUNT; i++) {
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
		keyboard[event.key.scancode] |= KeyFlag::Pressed | KeyFlag::Held;
	}
}

void Input::Input::EventKeyUp(SDL_Event &event) {
	keyboard[event.key.scancode] = KeyFlag::Released;
}

void Input::Input::EventMouseMotion(SDL_Event &event) {
	mouseMotion[0] = event.motion.x;
	mouseMotion[1] = event.motion.y;

	mouseRel[0] = event.motion.xrel;
	mouseRel[1] = event.motion.yrel;
}

void Input::Input::EventMouseButtonDown(SDL_Event &event) {
	mouse[event.button.button] = KeyFlag::Pressed | KeyFlag::Held;
}

void Input::Input::EventMouseButtonUp(SDL_Event &event) {
	mouse[event.button.button] = KeyFlag::Released;
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

bool Input::Input::buttonReleased(unsigned int button) {
	return mouse[button] & KeyFlag::Released;
}

bool Input::Input::buttonHeld(unsigned int button) {
	return mouse[button] & KeyFlag::Held;
}

bool Input::Input::buttonPressed(unsigned int button) {
	return mouse[button] & KeyFlag::Pressed;
}
