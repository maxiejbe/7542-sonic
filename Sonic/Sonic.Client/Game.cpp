#include "Game.h"
#include "GameState.h"
#include "MenuState.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

Game::Game(ServerConfiguration serverConfig, string configPath) {
	this->serverConfig = serverConfig;
	this->configPath = configPath;
	this->running = true;
}

void Game::unload()
{
	while (!states.empty()) {
		states.back()->unload();
		states.pop_back();
	}
}

void Game::update()
{
	states.back()->update(this, 0);
}

void Game::render()
{
	states.back()->render(this);
}

void Game::changeState(GameState* state)
{
	while (!states.empty()) {
		states.back()->unload();
		states.pop_back();
	}

	states.push_back(state);
	states.back()->load(this);
}

void Game::pushState(GameState* state)
{
	states.push_back(state);
	states.back()->load(this);
}

void Game::popState()
{
	if (!states.empty()) {
		states.back()->unload();
		states.pop_back();
	}
}

void Game::run()
{
	Timer fpsTimer;
	Timer capTimer;
	int countedFrames = 0;

	fpsTimer.start();

	this->changeState(MenuState::Instance());

	while (running) {

		capTimer.start();

		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000) {
			avgFPS = 0;
		}

		this->update();
		this->render();

		SDL_RenderPresent(Renderer::getInstance().gRenderer);

		++countedFrames;

		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICK_PER_FRAME) {
			SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
		}
	}
}

size_t Game::statesSize()
{
	return this->states.size();
}

string Game::getConfigPath()
{
	return this->configPath;
}

ServerConfiguration Game::getServerConfig()
{
	return this->serverConfig;
}
