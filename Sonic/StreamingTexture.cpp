#include "StreamingTexture.h"

StreamingTexture::StreamingTexture()
{
	pixels = NULL;
	pitch = 0;
}

StreamingTexture::~StreamingTexture()
{
	pixels = NULL;
	free();
}

bool StreamingTexture::loadFromFile(std::string path)
{
	free();

	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		LOG(logERROR) << "No se pudo cargar la imagen '" << path.c_str() << "'. SDL_Image Error: " << IMG_GetError();
	}
	else
	{
		// Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurface(loadedSurface, SDL_GetWindowSurface(SDLWindow::getInstance().gWindow)->format, NULL);
		if (formattedSurface == NULL) {
			LOG(logERROR) << "No se pudo convertir la surface cargada de '" << path.c_str() << "'en un formato válido . SDL_Image Error: " << IMG_GetError();
		}
		else {
			//SDL_SetColorKey(formattedSurface, SDL_TRUE, SDL_MapRGB(formattedSurface->format, 0, 0xFF, 0xFF));
			// Create blank streamable texture
			newTexture = SDL_CreateTexture(Renderer::getInstance().gRenderer, SDL_GetWindowPixelFormat(SDLWindow::getInstance().gWindow), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL) {
				LOG(logERROR) << "Error al crear la textura desde '" << path.c_str() << "'. SDL Error: " << SDL_GetError();
			}
			else {
				// Lock texture for manipulation
				SDL_LockTexture(newTexture, NULL, &pixels, &pitch);

				// Copy loaded/formatted surface pixels
				memcpy(pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				// Unlock texture to update
				SDL_UnlockTexture(newTexture);
				pixels = NULL;

				// Get image dimensions
				width = formattedSurface->w;
				height = formattedSurface->h;

			}

			SDL_FreeSurface(formattedSurface);
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture = newTexture;
	return texture != NULL;
}

bool StreamingTexture::lockTexture()
{
	// Texture is already locked
	if (pixels != NULL) {
		LOG(logERROR) << "La textura ya fue bloqueada anteriormente.";
		return false;
	}

	// Lock texture
	if (SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0) {
		LOG(logERROR) << "No se pudo bloquear la textura: " << SDL_GetError();
		return false;
	}

	return true;
}

bool StreamingTexture::unlockTexture()
{
	// Texture is not locked
	if (pixels == NULL) {
		LOG(logERROR) << "La textura no está bloqueada!";
		return false;
	}

	// Unlock texture
	SDL_UnlockTexture(texture);
	pixels = NULL;
	pitch = 0;

	return true;
}

void * StreamingTexture::getPixels()
{
	return pixels;
}

int StreamingTexture::getPitch()
{
	return pitch;
}

void StreamingTexture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}
