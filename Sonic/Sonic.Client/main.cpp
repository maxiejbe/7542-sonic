#include <SDL.h>
#include <SDL_image.h>
#include "Parser.h"
#include "Entities/Window.h"
#include "Renderer.h"
#include "entities/ServerConfiguration.h"
#include "network/NetworkManager.h"
#include "Game.h"

void close()
{
	SDLWindow::getInstance().close();
	Renderer::getInstance().close();
	NetworkManager::getInstance().close();

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	Logger::init(logLOW);

	string configParamName = "--config";
	string configPath = "";

	//Take config file from param
	if (argc > 2) {
		string arg = args[1];
		if (arg == configParamName) {
			configPath = args[2];
		}
	}

	Window window;
	ServerConfiguration serverConfig;

	// Parse local window and config
	Parser* localParser = new Parser(configPath, "");
	localParser->parse(&window);
	localParser->parse(&serverConfig);
	delete localParser;

	bool windowCreated = SDLWindow::getInstance().create(window.getWidth(), window.getHeight());
	bool rendererCreated = Renderer::getInstance().create();

	Game game(serverConfig, configPath);

	if (windowCreated && rendererCreated) {
		game.run();
	}
	else {
		LOG(logERROR) << "Error al inicializar el juego!";
	}

	game.unload();
	close();

	LOG(logINFO) << "El juego ha finalizado.";

	return 0;
}