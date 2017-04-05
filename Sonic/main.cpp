#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Timer.h"
#include "Player.h"
#include "Logger.h"
#include "Parser.h"
#include "Entities/Window.h"
#include "Renderer.h"
#include "entities/Rectangle.h"
#include "entities/Circle.h"
#include "entities/Square.h"

void close();

void close()
{
	SDLWindow::getInstance().close();
	Renderer::getInstance().close();

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	Logger::init();
	Logger::loggingLevel() = logMEDIUM; //Logger::fromString(config.GetLogLevel());

	//TODO: Take params from argv
	string configPath;
	if (argc > 1) {
		configPath = args[1];
	}
	Parser* parser = new Parser(configPath);
	Window window;
	parser->parse(&window);

	Configuration config;
	parser->parse(&config);

	Scenario scenario;
	parser->parse(&scenario);

	int scenarioWidth = scenario.getWidth();
	int scenarioHeight = scenario.getHeight();

	if (!SDLWindow::getInstance().create(window.getWidth(), window.getHeight()) || !Renderer::getInstance().create()) {
		LOG(logERROR) << "Error al inicializar el juego!";
	}
	else {
		bool isRunning = true;
		SDL_Event event;

		// Initialize layers
		vector<Layer> layers = scenario.getLayers();
		for (vector<Layer>::iterator it = layers.begin(); it != layers.end(); ++it) {
			Layer* layer = &(*it);
			layer->loadLayer();
		}

		// Initialize player
		Player player("img/sonic.png", 0, SDLWindow::getInstance().getScreenHeight() / 1.35, 0, 0, scenarioWidth, scenarioHeight, config.getScrollSpeed());
		LOG(logINFO) << "El personaje ha sido creado correctamente.";

		// Initialize camera
		Timer stepTimer;
		SDL_Rect camera = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };

		while (isRunning) {

			// Check event type
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					isRunning = false;
					LOG(logINFO) << "El usuario ha solicitado la terminación del juego.";
				}

				player.handleEvent(event);
			}

			float timeStep = stepTimer.getTicks() / 1000.f;

			player.move(timeStep);

			stepTimer.start();

			// Center the camera
			camera.x = ((int)player.getPosX() + player.getWidth() / 2) - SDLWindow::getInstance().getScreenWidth() / 2;
			camera.y = ((int)player.getPosY() + player.getHeight() / 2) - SDLWindow::getInstance().getScreenHeight() / 2;

			// Keep the camera in bounds
			if (camera.x < 0)
				camera.x = 0;
			if (camera.y < 0)
				camera.y = 0;

			if (camera.x > scenarioWidth - camera.w)
				camera.x = scenarioWidth - camera.w;
			if (camera.y > scenarioHeight - camera.h)
				camera.y = scenarioHeight - camera.h;

			// Clear screen
			SDL_SetRenderDrawColor(Renderer::getInstance().gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(Renderer::getInstance().gRenderer);

			// Render layers
			for (size_t i = 0; i < layers.size(); i++) {
				Layer* layer = &(layers.at(i));
				layer->renderLayer(0, 0, &camera);
			}

			// Render entities
			for (size_t i = 0; i < scenario.getEntities().size(); i++) {
				Entity* entity = scenario.getEntities().at(i);
				entity->draw(camera);
			}

			// Render player
			player.render(camera.x, camera.y);

			SDL_RenderPresent(Renderer::getInstance().gRenderer);
		}
	}

	close();

	LOG(logINFO) << "El juego ha finalizado.";

	return 0;
}