#include "FinalLevelStatisticsPanel.h"

FinalLevelStatisticsPanel::FinalLevelStatisticsPanel()
{
	TTF_Init();
	fontLifes = TTF_OpenFont("fonts/SonicAdvance.ttf", 10);
	fontScore = TTF_OpenFont("fonts/SonicAdvance.ttf", 13);
	fontLevel = TTF_OpenFont("fonts/SonicAdvance.ttf", 50);

	//levelHasPassed.loadFromFile("img/levelhaspassed.png");
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

void FinalLevelStatisticsPanel::freeSurfaceStatistics()
{
	//Call base method 
	//SDL_FreeSurface(surfaceMessage);
}

void FinalLevelStatisticsPanel::showLevelHasPassed(Texture imgLevel, int x, int y)
{
	SDL_Rect destrect;
	destrect.x = x;
	destrect.y = y;
	destrect.w = imgLevel.getWidth() / 2.5;
	destrect.h = imgLevel.getHeight() / 2.5;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, imgLevel.getTexture(), NULL, &destrect);
}

//void FinalLevelStatisticsPanel::showStatistics(vector<Player*> players)
void FinalLevelStatisticsPanel::showStatistics()
{
	int PLAYERS_SIZE = 3;
	int x = 400 - (75 + 100 * (PLAYERS_SIZE - 1));

	//ONLY FOR TEST
   	Texture playerImage;
	levelHasPassed.loadFromFile("img/levelhaspassed.png"); //Bug

	//Show blur background
	boxRGBA(Renderer::getInstance().gRenderer, 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight(), 0, 0, 0, 150);

	//Show level has passed image
	showLevelHasPassed(levelHasPassed, 200, 100);

	//Show number level
	string nameLevel = to_string(1); //Refactor when player has playerName
	showText(nameLevel, 560, 150, fontLevel, { 255, 255, 0 });
	
	//Show player statistics
	for (int i = 0; i < PLAYERS_SIZE; i++)
	{
		playerImage.loadFromFile("img/sonic_avatar.png"); //Bug

		//Show Player image
		showPlayerImage(playerImage, x, 350); //Refactor when player has image

		//Show userName
		string namePlayer = "SONIC"; //Refactor when player has playerName
		showText(namePlayer, x + playerImage.getWidth() * 2 + 20, 345, fontLifes, { 255, 255, 0 });

		//Show team
		string team = "TEAM " + to_string(1); //Refactor when player has rings
		showText(team, x + playerImage.getWidth() * 2 + 20, 370, fontLifes, { 255, 255, 255 });

		//Show score
		string score = "SCORE " + to_string(100); //Refactor when player has rings
		showText(score, x, 400, fontScore, { 255, 255, 0 });

		//Show rings
		string rings = "RING BONUS " + to_string(500); //Refactor when player has rings
		showText(rings, x, 430, fontScore, { 255, 255, 0 });

		x = x + 200;
	}
}