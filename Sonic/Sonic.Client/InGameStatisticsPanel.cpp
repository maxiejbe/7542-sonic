#include "InGameStatisticsPanel.h"

InGameStatisticsPanel::InGameStatisticsPanel()
{
	TTF_Init();
	fontLifes = TTF_OpenFont("fonts/SonicAdvance.ttf", 10);
	fontScore = TTF_OpenFont("fonts/SonicAdvance.ttf", 20);
}

InGameStatisticsPanel::~InGameStatisticsPanel()
{
	/*freeSurfaceStatistics();
	TTF_CloseFont(fontLifes);
	fontLifes = NULL;
	TTF_CloseFont(fontScore);
	fontScore = NULL;*/
}

void InGameStatisticsPanel::freeSurfaceStatistics()
{
	SDL_FreeSurface(surfaceMessage);
}

void InGameStatisticsPanel::showStatistics(Player* player)
{
	TTF_Init();
	SDL_Rect destrect;
	SDL_Texture* text;

	this->player = player;
	this->playerImage.loadFromFile("img/sonic_avatar.png"); //Refactor when player has playerImage

	//Show Player image, name and lifes
	if (this->playerImage.getTexture() != nullptr) {
		destrect.x = 30;
		destrect.y = 550;
		destrect.w = playerImage.getWidth()*2;
		destrect.h = playerImage.getHeight()*2;

		SDL_RenderCopy(Renderer::getInstance().gRenderer, playerImage.getTexture(), NULL, &destrect);
	}

	//Show userName
	string namePlayer = "SONIC"; //Refactor when player has playerName
	surfaceMessage = TTF_RenderText_Solid(fontLifes, namePlayer.c_str(), { 255, 255, 0 });
	text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surfaceMessage);
	destrect.x = 80;
	destrect.y = 545;
	destrect.w = surfaceMessage->w;
	destrect.h = surfaceMessage->h;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);
	
	//Show lifes
	string lifesPlayer = "X 3"; //Refactor when player has lifes
	surfaceMessage = TTF_RenderText_Solid(fontLifes, lifesPlayer.c_str(), { 255, 255, 255 });
	text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surfaceMessage);
	destrect.x = 80;
	destrect.y = 570;
	destrect.w = surfaceMessage->w;
	destrect.h = surfaceMessage->h;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);


	//Show score
	string score = "SCORE " + to_string(100); //Refactor when player has score
	surfaceMessage = TTF_RenderText_Solid(fontScore, score.c_str(), { 255, 255, 0 });
	text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surfaceMessage);
	destrect.x = 30;
	destrect.y = 10;
	destrect.w = surfaceMessage->w;
	destrect.h = surfaceMessage->h;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);

	//Show rings
	string rings = "RINGS " + to_string(50); //Refactor when player has rings
	surfaceMessage = TTF_RenderText_Solid(fontScore, rings.c_str(), { 255, 255, 0 });
	text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surfaceMessage);
	destrect.x = 30;
	destrect.y = 65;
	destrect.w = surfaceMessage->w;
	destrect.h = surfaceMessage->h;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);
}