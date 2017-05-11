#ifndef BANNER_H
#define BANNER_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"


class Banner
{
public:
	Banner(string text, SDL_Color color);
	~Banner();

	void showBanner();
	void freeSurfaceBanner();

protected:
	TTF_Font* font;
	Texture image;
	Texture background;
	float posX, posY;
	SDL_Color color;
	SDL_Surface* message;
	string text;

};

#endif // !BANNER_H