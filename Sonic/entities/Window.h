#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Window {
public:
	static Window& getInstance() {
		static Window instance;
		return instance;
	}
	bool Create();
	void Close();
	SDL_Window* gWindow = NULL;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
private:
	Window() {}
public:
	Window(Window const&) = delete;
	void operator=(Window const&) = delete;
};

#endif // !WINDOW_H