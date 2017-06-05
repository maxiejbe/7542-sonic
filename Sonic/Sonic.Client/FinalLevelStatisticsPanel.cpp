#include "FinalLevelStatisticsPanel.h"

FinalLevelStatisticsPanel::FinalLevelStatisticsPanel()
{
	TTF_Init();
	fontLifes = TTF_OpenFont("fonts/SonicAdvance.ttf", 10);
	fontScore = TTF_OpenFont("fonts/SonicAdvance.ttf", 13);
	fontLevel = TTF_OpenFont("fonts/SonicAdvance.ttf", 50);
}


FinalLevelStatisticsPanel::~FinalLevelStatisticsPanel()
{
	/*freeSurfaceFinalLevelStatistics();
	TTF_CloseFont(fontLifes);
	fontLifes = NULL;
	TTF_CloseFont(fontScore);
	fontScore = NULL;
	TTF_CloseFont(fontLevel);
	fontLevel = NULL;*/
}

//void FinalLevelStatisticsPanel::showStatistics(vector<Player*> players)
void FinalLevelStatisticsPanel::showStatistics()
{
	SDL_Rect destrect;
	SDL_Texture* text;
	int PLAYERS_SIZE = 4;
	int x = 400 - (75 + 100 * (PLAYERS_SIZE - 1));

	//ONLY FOR TEST
   	Texture playerImage;
	playerImage.loadFromFile("img/sonic_avatar.png");
	levelHasPassed.loadFromFile("img/levelhaspassed.png");

	//Show first player statistics
	//Show blur background
	boxRGBA(Renderer::getInstance().gRenderer, 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight(), 0, 0, 0, 150);

	//Show level has passed
	destrect.x = 200;
	destrect.y = 100;
	destrect.w = levelHasPassed.getWidth() / 2.5;
	destrect.h = levelHasPassed.getHeight() / 2.5;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, levelHasPassed.getTexture(), NULL, &destrect);

	//Show number level
	string nameLevel = to_string(1); //Refactor when player has playerName
	surfaceMessage = TTF_RenderText_Solid(fontLevel, nameLevel.c_str(), { 255, 255, 0 });
	text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surfaceMessage);
	destrect.x = 560;
	destrect.y = 150;
	destrect.w = surfaceMessage->w;
	destrect.h = surfaceMessage->h;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);
	
	//Show player statistics
	for (int i = 0; i < PLAYERS_SIZE; i++)
	{
		//Show Player image
		destrect.x = x;
		destrect.y = 350;
		destrect.w = playerImage.getWidth() * 2;
		destrect.h = playerImage.getHeight() * 2;
		SDL_RenderCopy(Renderer::getInstance().gRenderer, playerImage.getTexture(), NULL, &destrect);

		//Show userName
		string namePlayer = "SONIC"; //Refactor when player has playerName
		surfaceMessage = TTF_RenderText_Solid(fontLifes, namePlayer.c_str(), { 255, 255, 0 });
		text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surfaceMessage);
		destrect.x = x + playerImage.getWidth() * 2 + 20;
		destrect.y = 345;
		destrect.w = surfaceMessage->w;
		destrect.h = surfaceMessage->h;
		SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);

		//Show team
		string team = "TEAM " + to_string(1); //Refactor when player has rings
		surfaceMessage = TTF_RenderText_Solid(fontLifes, team.c_str(), { 255, 255, 255 });
		text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surfaceMessage);
		destrect.x = x + playerImage.getWidth() * 2 + 20;
		destrect.y = 370;
		destrect.w = surfaceMessage->w;
		destrect.h = surfaceMessage->h;
		SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);

		//Show score
		string score = "SCORE " + to_string(100); //Refactor when player has rings
		surfaceMessage = TTF_RenderText_Solid(fontScore, score.c_str(), { 255, 255, 0 });
		text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surfaceMessage);
		destrect.x = x;
		destrect.y = 400;
		destrect.w = surfaceMessage->w;
		destrect.h = surfaceMessage->h;
		SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);

		//Show rings
		string rings = "RING BONUS " + to_string(500); //Refactor when player has rings
		surfaceMessage = TTF_RenderText_Solid(fontScore, rings.c_str(), { 255, 255, 0 });
		text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, surfaceMessage);
		destrect.x = x;
		destrect.y = 430;
		destrect.w = surfaceMessage->w;
		destrect.h = surfaceMessage->h;
		SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);

		x = x + 200;
	}
}