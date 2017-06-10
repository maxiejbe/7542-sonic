#include "BaseStatisticsPanel.h"

void BaseStatisticsPanel::showText(string text, int x, int y, TTF_Font* font, SDL_Color color)
{
	textTexture.loadFromFont(font, text, color);
	textTexture.render(x, y, NULL);
}

void BaseStatisticsPanel::showPlayerImage(Texture* playerImage, int x, int y)
{
	destrect.w = playerImage->getWidth() * 2.5;
	destrect.h = playerImage->getHeight() * 2.5;
	playerImage->render(x, y, &destrect);
}