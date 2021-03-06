#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Timer.h"
#include "Renderer.h"
#include "Banner.h"
#include "network/NetworkManager.h"
#include <string>
#include <vector>
#include "entities/GameConfig.h"

class GameState;

class Game
{

public:
	Game(ServerConfiguration serverConfig, string configPath);

	void unload();

	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();

	void update();
	void render();

	void run();

	void quit() { running = false; }

	GameMode getGameMode();
	void setGameMode(GameMode gameMode);

	size_t statesSize();
	string getConfigPath();
	ServerConfiguration getServerConfig();

private:
	ServerConfiguration serverConfig;
	string configPath;

	std::vector<GameState*> states;
	bool running;
	GameMode gameMode;
};

#endif // !GAME_H
