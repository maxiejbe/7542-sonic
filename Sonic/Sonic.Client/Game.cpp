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
	// cleanup the current state
	while (!states.empty()) {
		states.back()->unload();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->load(this);
}

void Game::pushState(GameState* state)
{
	//// pause current state
	//if (!states.empty()) {
	//	states.back()->Pause();
	//}

	// store and init the new state
	states.push_back(state);
	states.back()->load(this);
}

void Game::popState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->unload();
		states.pop_back();
	}

	//// resume previous state
	//if (!states.empty()) {
	//	states.back()->Resume();
	//}
}

void Game::run() {

	Timer fpsTimer;
	Timer capTimer;
	int countedFrames = 0;

	fpsTimer.start();

	this->changeState(MenuState::Instance());

	while (running) {

		capTimer.start();

		// Calculate and correct fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		this->update();

		this->render();

		SDL_RenderPresent(Renderer::getInstance().gRenderer);

		++countedFrames;

		// If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICK_PER_FRAME)
		{
			// Wait remaining time
			SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
		}
	}
}

int Game::statesSize()
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
