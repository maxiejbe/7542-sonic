#ifndef INGAMESTATISTICS_H
#define INGAMESTATISTICS_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"
#include "views/PlayerView.h"

class InGameStatisticsPanel
{
public:
	InGameStatisticsPanel();
	~InGameStatisticsPanel();

	void showStatistics(Player* player);
	void freeSurfaceStatistics();

private:
	Player* player;
	TTF_Font* fontLifes;
	TTF_Font* fontScore;
	Texture playerImage;
	SDL_Surface* surfaceMessage;
};

#endif // !INGAMESTATISTICS_H