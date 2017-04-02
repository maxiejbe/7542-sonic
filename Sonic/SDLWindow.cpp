#include "SDLWindow.h"

void SDLWindow::Close() {
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
}

int SDLWindow::GetScreenWidth()
{
	return this->screenWidth;
}

int SDLWindow::GetScreenHeight()
{
	return this->screenHeight;
}

bool SDLWindow::Create(int width, int height)
{
	this->screenWidth = width;
	this->screenHeight = height;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GetScreenWidth(), GetScreenHeight(), SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
	}

	return true;
}