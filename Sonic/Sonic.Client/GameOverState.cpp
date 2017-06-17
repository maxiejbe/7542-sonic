#include "GameOverState.h"
#include "Game.h"

GameOverState GameOverState::m_GameOverState;


void GameOverState::load(Game* game)
{
	gameOverBackground.loadFromFile("img/gameover.jpg");

	this->showGameOver();
}

void GameOverState::update(Game* game, float dt)
{
	InputManager* input = InputManager::getInstance();
	input->update();

	if (input->quitRequested()) {
		LOG(logINFO) << "El usuario ha solicitado la terminación del juego.";
		game->quit();
		return;
	}

	if (input->isKeyDown(KEY_RETURN)) {
		// Disconnect
		NetworkManager::getInstance().disconnect();
		// Go to menu
		game->changeState(MenuState::Instance());
	}
}

void GameOverState::render(Game* game)
{
}

int GameOverState::unload()
{
	return 0;
}

void GameOverState::showGameOver()
{
	gameOverBackground.render(0, 0, gameOverBackground.getWidth(), gameOverBackground.getHeight());
}