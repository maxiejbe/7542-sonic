#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class SDLWindow {
public:
	static SDLWindow& getInstance() {
		static SDLWindow instance;
		return instance;
	}
	bool Create();
	void Close();
	SDL_Window* gWindow = NULL;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
private:
	SDLWindow() {}
public:
	SDLWindow(SDLWindow const&) = delete;
	void operator=(SDLWindow const&) = delete;
};

#endif // !SDLWindow_H