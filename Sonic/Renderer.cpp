#include "Renderer.h"
#include "SDLWindow.h"

bool Renderer::Create() {

	bool success = true;

	//Create renderer for window
	gRenderer = SDL_CreateRenderer(SDLWindow::getInstance().gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}
	}

	return success;
}

void Renderer::Close() {
	//Destroy renderer	
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
}