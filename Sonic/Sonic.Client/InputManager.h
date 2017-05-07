#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include "InputTable.h"

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
