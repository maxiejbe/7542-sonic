#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Renderer.h"

class Texture {
public:
	Texture();
	~Texture();

	bool loadFromFile(std::string path);
	void free();
	void render(int x, int y, SDL_Rect* clip = NULL);
	void render(int x, int y, SDL_Rect* clip, SDL_Rect dest, double angle, SDL_Point* center, SDL_RendererFlip flip);

	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();

protected:
	SDL_Texture* texture;
	int width;
	int height;
};

#endif