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
//#include "Texture.h"

bool loadMedia(); //TODO: volarlo
void close();

Layer gBGLayer;
Texture gSpriteTexture;
Texture gSpriteTexture1;

bool loadMedia()
{
	bool success = true;

	success = gBGLayer.loadLayer();

	//Load sprite texture
	if (!gSpriteTexture.loadFromFile("img/sprite.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	//Load sprite texture
	if (!gSpriteTexture1.loadFromFile("img/sprite.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	return success;
}

void close()
{
	gBGLayer.destroyLayer();
	gSpriteTexture.free();

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

			

				//Render background
				gBGLayer.renderLayer(0, 0, &camera);


				//Crop img = rect
				Rectangle rectangle = Rectangle(100, 100, 100, 100);
				rectangle.draw(camera);
				int x1 = 100 - camera.x;
				int y1 = 100 - camera.y;
				SDL_Rect dstrect = { x1, y1, 100, 100 };			
				SDL_Rect croprect = { 0, 0, 100, 100 };				
				SDL_RenderCopy(Renderer::getInstance().gRenderer, gSpriteTexture.getTexture(), &croprect, &dstrect);

				//Crop img < rect
				Rectangle rectangle1 = Rectangle(300, 300, 300, 300);
				rectangle1.draw(camera);
				x1 = 300 - camera.x;
				y1 = 300 - camera.y;
				SDL_Rect dstrect1 = { x1, y1, 200, 200 };
				SDL_Rect croprect1 = { 0, 0, 200, 200 };
				SDL_RenderCopy(Renderer::getInstance().gRenderer, gSpriteTexture1.getTexture(), &croprect1, &dstrect1);

				//Crop img > rect (img.h es mas chica que el rect.h)
				Rectangle rectangle2 = Rectangle(700, 200, 300, 100);
				rectangle2.draw(camera);
				x1 = 700 - camera.x;
				y1 = 200 - camera.y;
				SDL_Rect dstrect2 = { x1, y1, 200, 100 };
				SDL_Rect croprect2 = { 0, 0, 200, 100 }; //rect.w mas grande que img.w, queda la img.w
				SDL_RenderCopy(Renderer::getInstance().gRenderer, gSpriteTexture1.getTexture(), &croprect2, &dstrect2);

				//Crop img > rect (img.w es mas chica que el rect.w)
				Rectangle rectangle3 = Rectangle(1200, 50, 60, 400);
				rectangle3.draw(camera);
				x1 = 1200 - camera.x;
				y1 = 50 - camera.y;
				SDL_Rect dstrect3 = { x1, y1, 60, 200 };
				SDL_Rect croprect3 = { 0, 0, 60, 200 }; //rect.w mas chico que img.w, queda la rect.w, rect.h es mas grande que img.h entocnes queda igual
				SDL_RenderCopy(Renderer::getInstance().gRenderer, gSpriteTexture1.getTexture(), &croprect3, &dstrect3);

				Circle circle = Circle(1500,200, 100);
				circle.draw(camera);

				Square square = Square(1300, 300, 80);
				square.draw(camera);

				player.render(camera.x, camera.y);
				
				SDL_RenderPresent(Renderer::getInstance().gRenderer);
			}
		}
	}

	close();

	LOG(logINFO) << "El juego ha finalizado.";

	return 0;
}