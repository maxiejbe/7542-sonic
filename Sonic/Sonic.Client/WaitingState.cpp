#include "WaitingState.h"
#include "Game.h"

WaitingState WaitingState::m_WaitingState;

void WaitingState::load(Game * game)
{
	Banner waitingConnectionsBanner = Banner("Waiting for other connections", { 0,0,0,150 }, "img/menu-background.jpg");

	Message* clientResponse = new Message();
	clientResponse->setType(MessageType::content_ok);
	NetworkManager::getInstance().sendMessage(clientResponse);
	delete clientResponse;

	// Show waiting banner
	if (!NetworkManager::getInstance().canStartGame()) {
		waitingConnectionsBanner.showBanner();

		while (!NetworkManager::getInstance().canStartGame()) {
			Sleep(1000);
		}
	}

	game->popState();
}

int WaitingState::unload()
{
	return 0;
}

void WaitingState::update(Game * game, float dt)
{
}

void WaitingState::render(Game * game)
{
}
