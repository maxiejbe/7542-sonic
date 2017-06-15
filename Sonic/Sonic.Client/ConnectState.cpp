#include "Game.h"
#include "ConnectState.h"
#include "PlayState.h"
#include "MenuState.h"

ConnectState ConnectState::m_ConnectState;

void ConnectState::load(Game* game)
{
	if (connected && !NetworkManager::getInstance().online()) {
		reconnect(game);
	}
	else {
		connected = NetworkManager::getInstance().connectToServer(game->getServerConfig());

		if (connected) {

			if (NetworkManager::getInstance().getGameMode() == GameMode::grupal) // Choose Team				
				game->changeState(SelectTeamState::Instance());
			else // Start game
				game->changeState(PlayState::Instance());
		}
	}
}

int ConnectState::unload()
{
	return 0;
}

void ConnectState::update(Game* game, float dt)
{
}

void ConnectState::render(Game* game)
{
	Banner canConnectToServerBanner = Banner("Server connection failed", { 0,0,0,150 }, "img/menu-background.jpg");
	canConnectToServerBanner.showBanner();

	Sleep(2000);

	game->changeState(MenuState::Instance());
}

void ConnectState::reconnect(Game* game)
{
	Timer timer = Timer();
	timer.start();

	Banner reconnectionBanner = Banner("Reconnecting", { 0,0,0,150 }, "img/menu-background.jpg");
	int reconnectionTimeStep = timer.getTicks() / 1000;
	int reconnectionAttempt = 1;
	bool reconnected = false;

	reconnectionBanner.showBanner();

	while (!NetworkManager::getInstance().online() && reconnectionAttempt <= 3) {
		double currentTime = timer.getTicks() / 1000;
		if ((currentTime - reconnectionTimeStep) > 3) {
			reconnected = NetworkManager::getInstance().reconnect();
			reconnectionAttempt++;
			reconnectionTimeStep = timer.getTicks() / 1000;
		}
	}

	if (!reconnected) {
		game->changeState(MenuState::Instance());
		return;
	}

	if (game->statesSize() > 1) {
		// Comming from PlayState, so return there.
		game->popState();
		//game->changeState(PlayState::Instance());
	}
	else {
		game->changeState(PlayState::Instance());
	}

}
