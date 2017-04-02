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

	if (!gBGTexture.loadFromFile("img/level.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	return success;
}

void close()
{
	gBGTexture.free();

	SDLWindow::getInstance().Close();
	Renderer::getInstance().Close();

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

	SDLWindow::getInstance().SCREEN_WIDTH = window.GetWidth();
	SDLWindow::getInstance().SCREEN_HEIGHT = window.GetHeight();

	Configuration config;
	parser->Parse(&config);

	Logger::LoggingLevel() = Logger::FromString(config.GetLogLevel());

	Scenario scenario;
	parser->Parse(&scenario);

	int scenarioWidth = scenario.GetWidth();
	int scenarioHeight = scenario.GetHeight();

	//Start up SDL and create window
	if (!SDLWindow::getInstance().Create() || !Renderer::getInstance().Create()) {
		printf("Failed to initialize!\n");
	}
	else {
		//Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			bool isRunning = true;
			SDL_Event e;

			//The dot that will be moving around on the screen
			Player player("img/sonic.png", 0, SDLWindow::getInstance().SCREEN_HEIGHT / 2, 0, 0, scenarioWidth, scenarioHeight);

			Timer stepTimer;
			SDL_Rect camera = { 0, 0, SDLWindow::getInstance().SCREEN_WIDTH, SDLWindow::getInstance().SCREEN_HEIGHT };

			while (isRunning) {

				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						isRunning = false;
					}

					player.handleEvent(e);
				}

				//Calculate time step
				float timeStep = stepTimer.getTicks() / 1000.f;

				//Move for time step
				player.move(timeStep);

				//Restart step timer
				stepTimer.start();

				//Center the camera over the player
				camera.x = ((int)player.getPosX() + player.GetWidth() / 2) - SDLWindow::getInstance().SCREEN_WIDTH / 2;
				camera.y = ((int)player.getPosY() + player.GetHeight() / 2) - SDLWindow::getInstance().SCREEN_HEIGHT / 2;

				//Keep the camera in bounds
				if (camera.x < 0)
					camera.x = 0;
				if (camera.y < 0)
					camera.y = 0;

				if (camera.x > scenarioWidth - camera.w)
					camera.x = scenarioWidth - camera.w;
				if (camera.y > scenarioHeight - camera.h)
					camera.y = scenarioHeight - camera.h;

				//Clear screen
				SDL_SetRenderDrawColor(Renderer::getInstance().gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer::getInstance().gRenderer);

				//Render background
				gBGTexture.render(0, 0, &camera);

				player.render(camera.x, camera.y);

				SDL_RenderPresent(Renderer::getInstance().gRenderer);
			}
		}
	}

	close();

	return 0;
}