#include "BaseStatisticsPanel.h"

void BaseStatisticsPanel::showText(string text, int x, int y, TTF_Font* font, SDL_Color color)
{
	SDL_Texture* textTexture;
	SDL_Surface* surfaceMessage;
	
	surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surfaceMessage);
	destrect.x = x;
	destrect.y = y;
	destrect.w = surfaceMessage->w;
	destrect.h = surfaceMessage->h;

	SDL_RenderCopy(Renderer::getInstance().gRenderer, textTexture, NULL, &destrect);
}

void BaseStatisticsPanel::showPlayerImage(Texture playerImage, int x, int y)
{
	if (playerImage.getTexture() != nullptr) {
		destrect.x = x;
		destrect.y = y;
		destrect.w = playerImage.getWidth() * 2;
		destrect.h = playerImage.getHeight() * 2;

		SDL_RenderCopy(Renderer::getInstance().gRenderer, playerImage.getTexture(), NULL, &destrect);
	}
}