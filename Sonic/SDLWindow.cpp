#include "SDLWindow.h"

void SDLWindow::Close()
{
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

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG(logERROR) << "SDL no pude ser inicializado! SDL Error: " << SDL_GetError();
		return false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			LOG(logWARNING) << "El filtrado de textura lineal no está habilitado.";
		}

		gWindow = SDL_CreateWindow("Sonic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GetScreenWidth(), GetScreenHeight(), SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			LOG(logERROR) << "La ventana no pudo ser creada! SDL Error: " << SDL_GetError();
			return false;
		}
	}

	return true;
}