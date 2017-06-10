#include "Game.h"
#include "EndLevelState.h"

EndLevelState EndLevelState::m_EndLevelState;

void EndLevelState::load(Game* game)
{
	TTF_Init();
	fontLifes = TTF_OpenFont("fonts/SonicAdvance.ttf", 10);
	fontScore = TTF_OpenFont("fonts/SonicAdvance.ttf", 13);
	fontLevel = TTF_OpenFont("fonts/SonicAdvance.ttf", 50);

	levelHasPassed.loadFromFile("img/levelhaspassed.png");
}

int EndLevelState::unload()
{
	//freeSurfaceStatistics();
	return 0;
}

void EndLevelState::update(Game* game, float dt)
{
	InputManager* input = InputManager::getInstance();
	input->update();

	if (input->quitRequested()) {
		game->quit();
		return;
	}

	if (input->isKeyDown(KEY_RETURN)) {
		//Go to next level
		game->pushState(MenuState::Instance());
	}
}

void EndLevelState::render(Game* game)
{
	this->showLevelHasPassed();
	this->showStatistics();
}

void EndLevelState::showLevelHasPassed()
{
	SDL_Rect destrect;
	destrect.x = 200;
	destrect.y = 100;
	destrect.w = levelHasPassed.getWidth() / 2.5;
	destrect.h = levelHasPassed.getHeight() / 2.5;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, levelHasPassed.getTexture(), NULL, &destrect);
}

void EndLevelState::showText(string text, int x, int y, TTF_Font* font, SDL_Color color)
{
	SDL_Rect destrect;
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

void EndLevelState::showPlayerImage(Texture playerImage, int x, int y)
{
	SDL_Rect destrect;

	if (playerImage.getTexture() != nullptr) {
		destrect.x = x;
		destrect.y = y;
		destrect.w = playerImage.getWidth() * 2;
		destrect.h = playerImage.getHeight() * 2;

		SDL_RenderCopy(Renderer::getInstance().gRenderer, playerImage.getTexture(), NULL, &destrect);
	}
}

//void FinalLevelStatisticsPanel::showStatistics(vector<Player*> players)
void EndLevelState::showStatistics()
{
	int PLAYERS_SIZE = 3;
	int x = 400 - (75 + 100 * (PLAYERS_SIZE - 1));

	//ONLY FOR TEST
	Texture playerImage;
	//levelHasPassed.loadFromFile("img/levelhaspassed.png"); Bug

	//Show blur background
	boxRGBA(Renderer::getInstance().gRenderer, 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight(), 0, 0, 0, 150);

	//Show level has passed image
	showLevelHasPassed();

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