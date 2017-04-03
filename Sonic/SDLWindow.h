#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Logger.h"

class SDLWindow {
public:
	static SDLWindow& getInstance() {
		static SDLWindow instance;
		return instance;
	}
	bool Create(int width, int height);
	void Close();

	int GetScreenWidth();
	int GetScreenHeight();

	SDL_Window* gWindow = NULL;
	SDLWindow(SDLWindow const&) = delete;
	void operator=(SDLWindow const&) = delete;
private:
	SDLWindow() {}
	int screenWidth, screenHeight;
};

#endif // !SDLWindow_H