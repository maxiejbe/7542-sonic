#ifndef BASE_STATISTICS_PANEL_H
#define BASE_STATISTICS_PANEL_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Texture.h"
#include "views/PlayerView.h"

class BaseStatisticsPanel
{
public:
	virtual void showText(string text, int x, int y, TTF_Font* font, SDL_Color color);
	virtual void showStatistics(Player* player) = 0;
	//virtual void freeSurfaceStatistics() = 0;
	virtual void showPlayerImage(Texture* playerImage, int x, int y);

private:
	SDL_Rect destrect;

protected:
	BaseStatisticsPanel() {}
	~BaseStatisticsPanel() {}
};

#endif // !BASE_STATISTICS_PANEL_H