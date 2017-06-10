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

	unordered_map<int, PlayerView*> playerViews = NetworkManager::getInstance().getPlayerViews();
	if (!playerViews.empty()) {
		for (unordered_map<int, PlayerView*>::iterator it = playerViews.begin(); it != playerViews.end(); ++it) {
			Player* player = it->second->getPlayer();
			players.push_back(player);
		}
	}

	this->showLevelHasPassed();
	this->showStatistics();
}

int EndLevelState::unload()
{
	TTF_CloseFont(fontLifes);
	fontLifes = NULL;
	TTF_CloseFont(fontScore);
	fontScore = NULL;
	TTF_CloseFont(fontLevel);
	fontLevel = NULL;
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
		// Go to next level
		game->changeState(PlayState::Instance());
	}
}

void EndLevelState::render(Game* game)
{
}

void EndLevelState::showLevelHasPassed()
{
	levelHasPassed.render(200, 100, levelHasPassed.getWidth() / 2.5, levelHasPassed.getHeight() / 2.5);
}

void EndLevelState::showText(string text, int x, int y, TTF_Font* font, SDL_Color color)
{
	textTexture.loadFromFont(font, text, color);
	textTexture.render(x, y, NULL);
}

void EndLevelState::showPlayerImage(Texture playerImage, int x, int y)
{
	if (playerImage.getTexture() != nullptr) {
		playerImage.render(x, y, playerImage.getWidth() * 2.5, playerImage.getHeight() * 2.5);
	}
}

void EndLevelState::showStatistics()
{
	int PLAYERS_SIZE = players.size();
	int x = 400 - (75 + 100 * (PLAYERS_SIZE - 1));

	// Show blur background
	boxRGBA(Renderer::getInstance().gRenderer, 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight(), 0, 0, 0, 150);

	// Show level has passed image
	showLevelHasPassed();

	// Show number level
	string nameLevel = to_string(1); // TODO get level dynamically
	showText(nameLevel, 560, 150, fontLevel, { 255, 255, 0 });

	// Show player statistics
	for (int i = PLAYERS_SIZE - 1; i >= 0; i--) {
		// Check texture
		if (!this->playerImage.loadFromFile(PlayerUtils::getPlayerAvatarFilePath(players.at(i)))) {
			LOG(logWARNING) << "No se pudo cargar la imagen del avatar '" << PlayerUtils::getPlayerAvatarFilePath(players[i]) << "'.";
			return;
		}

		// Show Player image
		showPlayerImage(playerImage, x, 350);

		// Show userName
		string namePlayer = PlayerUtils::getPlayerName(players.at(i));
		showText(namePlayer, x + playerImage.getWidth() * 2 + 20, 345, fontLifes, { 255, 255, 0 });

		// Show team
		string team = "TEAM " + to_string(1); //Refactor when player has rings
		showText(team, x + playerImage.getWidth() * 2 + 20, 370, fontLifes, { 255, 255, 255 });

		// Show score
		string score = "SCORE " + to_string(100); //Refactor when player has rings
		showText(score, x, 400, fontScore, { 255, 255, 0 });

		// Show rings
		string rings = "RING BONUS " + to_string(500); //Refactor when player has rings
		showText(rings, x, 430, fontScore, { 255, 255, 0 });

		x += 200;
	}
}