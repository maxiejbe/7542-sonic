#include "WinGameState.h"
#include "Game.h"

WinGameState WinGameState::m_WinGameState;

void WinGameState::load(Game* game)
{
	winGameBackground.loadFromFile("img/wingame.jpg");

	this->showWinGame();
	SoundManager::getInstance().playSound("sounds/ending.mp3");
}

void WinGameState::update(Game* game, float dt)
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

void WinGameState::render(Game* game)
{
}

int WinGameState::unload()
{
	SoundManager::getInstance().stopMusic();
	SoundManager::getInstance().close();
	return 0;
}

void WinGameState::showWinGame()
{
	winGameBackground.render(0, 0, winGameBackground.getWidth(), winGameBackground.getHeight());
}