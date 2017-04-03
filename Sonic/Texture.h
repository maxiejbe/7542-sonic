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
	//void setColor(Uint8 red, Uint8 green, Uint8 blue);
	//void setBlendMode(SDL_BlendMode blending);
	//void setAlpha(Uint8 alpha);
	void render(int x, int y, SDL_Rect* clip = NULL);

	int getWidth();
	int getHeight();
	SDL_Texture* getTexture(); // es necesario?

private:
	SDL_Texture* texture;
	int width;
	int height;
};

#endif