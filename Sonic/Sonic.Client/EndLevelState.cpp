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
	this->showStatistics(game->getGameMode());
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
	levelHasPassed.render(200, 100, (int)(levelHasPassed.getWidth() / 2.5), (int)(levelHasPassed.getHeight() / 2.5));
}

void EndLevelState::showText(string text, int x, int y, TTF_Font* font, SDL_Color color)
{
	textTexture.loadFromFont(font, text, color);
	textTexture.render(x, y, NULL);
}

void EndLevelState::showPlayerImage(Texture playerImage, int x, int y)
{
	if (playerImage.getTexture() != nullptr) {
		playerImage.render(x, y, (int)(playerImage.getWidth() * 2.5), (int)(playerImage.getHeight() * 2.5));
	}
}

void EndLevelState::showStatistics(GameMode gameMode)
{
	int PLAYERS_SIZE = players.size();
	int x = 400 - (75 + 100 * (PLAYERS_SIZE - 1));

	// Show blur background
	boxRGBA(Renderer::getInstance().gRenderer, 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight(), 0, 0, 0, 150);

	// Show level has passed image
	showLevelHasPassed();

	// Show number level
	string nameLevel = to_string(NetworkManager::getInstance().getActualLevel());
	showText(nameLevel, 560, 150, fontLevel, { 255, 255, 0 });

	int INITIAL_Y = 300;

	// Show player statistics
	for (int i = PLAYERS_SIZE - 1; i >= 0; i--) {
		// Check texture
		if (!this->playerImage.loadFromFile(PlayerUtils::getPlayerAvatarFilePath(players.at(i)))) {
			LOG(logWARNING) << "No se pudo cargar la imagen del avatar '" << PlayerUtils::getPlayerAvatarFilePath(players[i]) << "'.";
			return;
		}

		// Show Player image
		showPlayerImage(playerImage, x, INITIAL_Y);

		// Show userName
		string namePlayer = PlayerUtils::getPlayerName(players.at(i));
		showText(namePlayer, x + playerImage.getWidth() * 2 + 20, INITIAL_Y - 5, fontLifes, { 255, 255, 0 });

		if (gameMode == GameMode::grupal) {
			// Show team
			string team = "TEAM " + to_string(players.at(i)->getTeamId());
			showText(team, x + playerImage.getWidth() * 2 + 20, INITIAL_Y + 20, fontLifes, { 255, 255, 255 });
		}

		// Show score
		string score = "SCORE    " + to_string(players.at(i)->getPoints());
		showText(score, x, INITIAL_Y + 50, fontScore, { 255, 255, 0 });

		// Show rings
		string rings = "RING BONUS    " + to_string(players.at(i)->getRings());
		showText(rings, x, INITIAL_Y + 80, fontScore, { 255, 255, 0 });

		x += 200;
	}

	// Calculate team stats
	int teamScore = 0;
	int teamRings = 0;
	INITIAL_Y = 470;

	if (gameMode == GameMode::grupal) {
		x = 400 - (75 + 100 * (2 - 1));
		for (int j = 1; j <= 2; j++) {

			for (int i = 0; i < PLAYERS_SIZE; i++) {
				if (players.at(i)->getTeamId() == j) {
					teamScore = players.at(i)->getTeamPoints();
					teamRings = players.at(i)->getTeamRings();
					break;
				}
			}

			string team = "TEAM " + to_string(j);
			showText(team, x + playerImage.getWidth() * 2, INITIAL_Y, fontLifes, { 255, 255, 255 });

			// Show score
			string score = "SCORE    " + to_string(teamScore);
			showText(score, x, INITIAL_Y + 30, fontScore, { 255, 255, 0 });

			// Show rings
			string rings = "RING BONUS    " + to_string(teamRings);
			showText(rings, x, INITIAL_Y + 60, fontScore, { 255, 255, 0 });

			x += 300;
		}
	}
	else if (gameMode == GameMode::colaborativo) {
		x = 400 - 75;
		teamScore = players.at(0)->getTeamPoints();
		teamRings = players.at(0)->getTeamRings();

		string team = "TOTAL";
		showText(team, x + playerImage.getWidth() * 2, INITIAL_Y, fontLifes, { 255, 255, 255 });

		// Show score
		string score = "SCORE    " + to_string(teamScore);
		showText(score, x, INITIAL_Y + 30, fontScore, { 255, 255, 0 });

		// Show rings
		string rings = "RING BONUS    " + to_string(teamRings);
		showText(rings, x, INITIAL_Y + 60, fontScore, { 255, 255, 0 });
	}
}