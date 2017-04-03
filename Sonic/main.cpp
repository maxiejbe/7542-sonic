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

bool loadMedia(); //TODO: volarlo
void close();

Texture gBGTexture; //TODO: volarlo de aca y pasarlo a layer

bool loadMedia()
{
	bool success = true;

	if (!gBGTexture.loadFromFile("img/level2.jpg")) {
		LOG(logERROR) << "Error al cargar la imagen de la capa.";
		// TODO: usar img por defecto
		success = false;
	}

	return success;
}

void close()
{
	gBGTexture.free();

	SDLWindow::getInstance().close();
	Renderer::getInstance().close();

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	Logger::Init();

	//TODO: Take params from argv
	Parser* parser = new Parser("config/params.json");
	Window window;
	parser->Parse(&window);

	Configuration config;
	parser->Parse(&config);

	Logger::LoggingLevel() = Logger::FromString(config.GetLogLevel());
	LOG(logINFO) << "Se ha configurado el nivel de log en '" << Logger::ToString() << "'.";

	LOG(logINFO) << "Se ha configurado la velocidad de scroll en " << config.GetScrollSpeed() << " pixels por segundo.";

	Scenario scenario;
	parser->Parse(&scenario);

	int scenarioWidth = scenario.GetWidth();
	int scenarioHeight = scenario.GetHeight();

	LOG(logINFO) << "Se ha creado el escenario con un tamaño de " << scenarioWidth << "x" << scenarioHeight << ".";

	if (!SDLWindow::getInstance().create(window.getWidth(), window.getHeight()) || !Renderer::getInstance().create()) {
		LOG(logERROR) << "Error al inicializar el juego!";
	}
	else {
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			bool isRunning = true;
			SDL_Event event;

			Player player("img/sonic.png", 0, SDLWindow::getInstance().getScreenHeight() / 1.35, 0, 0, scenarioWidth, scenarioHeight, config.GetScrollSpeed());
			LOG(logINFO) << "El personaje ha sido creado correctamente.";

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

				gBGTexture.render(0, 0, &camera);
				player.render(camera.x, camera.y);

				SDL_RenderPresent(Renderer::getInstance().gRenderer);
			}
		}
	}

	close();

	LOG(logINFO) << "El juego ha finalizado.";

	return 0;
}