#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "Logger.h"

class SDLWindow {
public:
	static SDLWindow& getInstance() {
		static SDLWindow instance;
		return instance;
	}
	bool create(int width, int height);
	void close();

	int getScreenWidth();
	int getScreenHeight();

	SDL_Window* gWindow = NULL;
	SDLWindow(SDLWindow const&) = delete;
	void operator=(SDLWindow const&) = delete;
private:
	SDLWindow() {}
	int screenWidth, screenHeight;
};

#endif // !SDLWindow_H