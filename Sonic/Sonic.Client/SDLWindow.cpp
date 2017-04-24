#include "SDLWindow.h"

void SDLWindow::close()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
}

int SDLWindow::getScreenWidth()
{
	return this->screenWidth;
}

int SDLWindow::getScreenHeight()
{
	return this->screenHeight;
}

bool SDLWindow::create(int width, int height)
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

		gWindow = SDL_CreateWindow("Sonic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, getScreenWidth(), getScreenHeight(), SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			LOG(logERROR) << "La ventana no pudo ser creada! SDL Error: " << SDL_GetError();
			return false;
		}
	}

	LOG(logINFO) << "Se ha creado la ventana con un tamaño de " << width << "x" << height << ".";

	return true;
}