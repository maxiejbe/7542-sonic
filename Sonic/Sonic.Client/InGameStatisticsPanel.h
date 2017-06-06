#ifndef INGAMESTATISTICS_H
#define INGAMESTATISTICS_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"
#include "views/PlayerView.h"
#include "BaseStatisticsPanel.h"

class InGameStatisticsPanel : public BaseStatisticsPanel
{
public:
	InGameStatisticsPanel();
	~InGameStatisticsPanel();

	//void showStatistics(Player* player);
	void showStatistics();
	void freeSurfaceStatistics();

private:
	Player* player;
	TTF_Font* fontLifes;
	TTF_Font* fontScore;
	Texture playerImage;
};

#endif // !INGAMESTATISTICS_H