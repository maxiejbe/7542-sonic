#include "InGameStatisticsPanel.h"

InGameStatisticsPanel::InGameStatisticsPanel()
{
	TTF_Init();
	fontLifes = TTF_OpenFont("fonts/SonicAdvance.ttf", 10);
	fontScore = TTF_OpenFont("fonts/SonicAdvance.ttf", 20);

	//this->playerImage.loadFromFile("img/sonic_avatar.png"); //Refactor when player has playerImage
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
	//Call base method
	//SDL_FreeSurface(surfaceMessage);
}

//void InGameStatisticsPanel::showStatistics(Player* player)
void InGameStatisticsPanel::showStatistics()
{
	this->playerImage.loadFromFile("img/sonic_avatar.png"); //Bug

	//Show Player image
	showPlayerImage(playerImage, 30, 550); //Refactor when player has image

	//Show userName
	string namePlayer = "SONIC"; //Refactor when player has playerName
	showText(namePlayer, 80, 545, fontLifes, { 255, 255, 0 });
	
	//Show lifes
	string lifesPlayer = "X 3"; //Refactor when player has lifes
	showText(lifesPlayer, 80, 570, fontLifes, { 255, 255, 255 });

	//Show score
	string score = "SCORE " + to_string(100); //Refactor when player has score
	showText(score, 30, 10, fontScore, { 255, 255, 0 });

	//Show rings
	string rings = "RINGS " + to_string(50); //Refactor when player has rings
	showText(rings, 30, 65, fontScore, { 255, 255, 0 });

	//Show team
	string team = "TEAM " + to_string(1); //Refactor when player has rings
	showText(team, 670, 10, fontScore, { 255, 255, 255 });
}