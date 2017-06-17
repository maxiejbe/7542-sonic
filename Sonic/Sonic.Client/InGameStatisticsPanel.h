#ifndef INGAMESTATISTICS_H
#define INGAMESTATISTICS_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"
#include "views/PlayerView.h"
#include "BaseStatisticsPanel.h"
#include "utils/PlayerUtils.h"
#include "entities/GameConfig.h"

class InGameStatisticsPanel : public BaseStatisticsPanel
{
public:
	InGameStatisticsPanel(GameMode gameMode, int team);
	~InGameStatisticsPanel();

	void showStatistics(Player* player);
	void freeSurfaceStatistics();

private:
	Player* player;
	TTF_Font* fontLifes;
	TTF_Font* fontScore;
	TTF_Font* fontTestMode;
	Texture playerImage;
	GameMode gameMode;
	int team;
};

#endif // !INGAMESTATISTICS_H