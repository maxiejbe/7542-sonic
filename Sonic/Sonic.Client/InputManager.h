#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include "InputTable.h"

#define KEYBOARD_SIZE 284 // Fuente: https://wiki.libsdl.org/SDLScancodeLookup

class InputManager {
public:
	static InputManager* getInstance();
	void update();
	bool isKeyDown(int key);
	bool isKeyUp(int key);
	bool isKeyPressed(KeyboardKey key);
	bool quitRequested();

	InputManager();
	InputManager(InputManager const&) {};
	void operator=(InputManager const&) {};
private:
	static InputManager* instance;
	const uint8_t* keyboard;
	bool keyDown[KEYBOARD_SIZE];
	bool keyUp[KEYBOARD_SIZE];
	bool quit;
};

#endif // !INPUTMANAGER_H
