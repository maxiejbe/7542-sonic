#include "Renderer.h"
#include "SDLWindow.h"

bool Renderer::create()
{
	gRenderer = SDL_CreateRenderer(SDLWindow::getInstance().gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL) {
		LOG(logERROR) << "El Renderer no pudo ser creado! SDL Error: " << SDL_GetError();
		return false;
	}
	else {
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags)) {
			LOG(logERROR) << "SDL_Image no pudo ser inicializado! SDL_Image Error: " << IMG_GetError();
			return false;
		}
	}
	return true;
}

void Renderer::close()
{
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
}