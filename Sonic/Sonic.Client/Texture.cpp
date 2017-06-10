#include "Texture.h"

Texture::Texture()
{
	this->texture = NULL;
	this->width = 0;
	this->height = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(string path)
{
	free();

	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		LOG(logERROR) << "No se pudo cargar la imagen '" << path.c_str() << "'. Se tomará una por defecto. SDL_Image Error: " << IMG_GetError();
	}
	else {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

		texture = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surface);
		if (texture == NULL) {
			LOG(logERROR) << "Error al crear la textura desde '" << path.c_str() << "'. SDL Error: " << SDL_GetError();
		}
		else {
			width = surface->w;
			height = surface->h;
		}

		SDL_FreeSurface(surface);
	}

	this->texture = texture;
	return texture != NULL;
}

bool Texture::loadFromFont(TTF_Font* font, string text, SDL_Color color)
{
	free();

	SDL_Texture* texture = NULL;
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == NULL) {
		LOG(logERROR) << "No se pudo cargar la font con texto '" << text.c_str() << "'.";
		SDL_FreeSurface(surface);
		return false;
	}
	else {
		texture = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surface);
		if (texture == NULL) {
			LOG(logERROR) << "Error al crear la textura de la font con texto '" << text.c_str() << "'";
			SDL_FreeSurface(surface);
			return false;
		}
		else {
			width = surface->w;
			height = surface->h;
		}

		SDL_FreeSurface(surface);
	}

	this->texture = texture;
	return texture != NULL;
}

void Texture::free()
{
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::render(int x, int y, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, width, height };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(Renderer::getInstance().gRenderer, texture, clip, &renderQuad);
}

void Texture::render(int x, int y, int w, int h)
{
	SDL_Rect renderQuad = { x, y, w, h };
	SDL_RenderCopy(Renderer::getInstance().gRenderer, texture, NULL, &renderQuad);
}

void Texture::render(int x, int y, SDL_Rect* clip, SDL_Rect dest, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Renderer::getInstance().gRenderer, texture, clip, &dest, angle, center, flip);
}


int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

SDL_Texture* Texture::getTexture()
{
	return texture;
}
