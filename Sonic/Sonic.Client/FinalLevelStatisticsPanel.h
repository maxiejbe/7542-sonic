#ifndef FINALLEVELSTATISTICSPANEL_H
#define FINALLEVELSTATISTICSPANEL_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"
#include "views/PlayerView.h"
#include "BaseStatisticsPanel.h"

class FinalLevelStatisticsPanel : public BaseStatisticsPanel
{
public:
	FinalLevelStatisticsPanel();
	~FinalLevelStatisticsPanel();

	//void showStatistics(vector<Player*> players);
	void showStatistics();
	void showLevelHasPassed(Texture imgLevel, int x, int y);
	void freeSurfaceStatistics();

private:
	Player* player;
	TTF_Font* fontLifes;
	TTF_Font* fontScore;
	TTF_Font* fontLevel;
	Texture levelHasPassed;
};

#endif // !FINALLEVELSTATISTICSPANEL_H