#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Timer.h"
#include "Parser.h"
#include "Menu.h"
#include "Entities/Window.h"
#include "Renderer.h"
#include "entities/Configuration.h"
#include "entities/Scenario.h"
#include "entities/Player.h"
#include "InputManager.h"
#include "network/NetworkManager.h"

#include "views/LayerView.h"
#include "views/EntityView.h"
#include "views/PlayerView.h"

#include "views/common/EntityViewResolver.h"

void close();

void close()
{
	SDLWindow::getInstance().close();
	Renderer::getInstance().close();
	NetworkManager::getInstance().close();

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	Logger::init();
	Logger::loggingLevel() = logHIGH;

	string configParamName = "--config";
	string configPath = "";

	//Take config file from param
	if (argc > 2) {
		string arg = args[1];
		if (arg == configParamName) {
			configPath = args[2];
		}
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

	// Initialize layers
	vector<Layer> layers = scenario.getLayers();
	vector<LayerView> layerViews;
	for (vector<Layer>::iterator it = layers.begin(); it != layers.end(); ++it) {
		Layer* layer = &(*it);
		LayerView layerView(layer);
		layerViews.push_back(layerView);
	}

	//Initialize entities
	vector<Entity*> entities = scenario.getEntities();
	vector<EntityView*> entityViews;
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		Entity* entity = *it;
		EntityView* entityView = EntityViewResolver::resolve(entity);
		entityViews.push_back(entityView);
	}

	if (!SDLWindow::getInstance().create(window.getWidth(), window.getHeight()) || !Renderer::getInstance().create()) {
		LOG(logERROR) << "Error al inicializar el juego!";
	}
	else {
		bool isRunning = true;

		//Load layers
		for (vector<LayerView>::iterator it = layerViews.begin(); it != layerViews.end(); ++it) {
			LayerView* layerView = &(*it);
			layerView->loadLayer();
		}

		// Initialize player
		Player player("img/foo22.png", 0, SDLWindow::getInstance().getScreenHeight() / 1.35, 0, 0, scenarioWidth, scenarioHeight, config.getScrollSpeed());
		LOG(logINFO) << "El personaje ha sido creado correctamente.";

		//Initialize network manager
		//TODO: inicializar cliente desde config
		NetworkManager::getInstance().startClient("127.0.0.1", 5000, &player);

		// Initialize camera
		Timer stepTimer;
		SDL_Rect camera = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };

		// Initialize menu
		Menu menu = Menu();
		int i = menu.ShowMenu();
		if (i == 1) { isRunning = false; }

		while (isRunning) {

			InputManager* input = InputManager::getInstance();
			input->update();

			if (input->quitRequested()) {
				isRunning = false;
				LOG(logINFO) << "El usuario ha solicitado la terminación del juego.";
			}

			if (input->isKeyDown(KEY_ESCAPE) || input->isKeyDown(KEY_Q)) {
				i = menu.ShowMenu();
				if (i == 1) { isRunning = false; }
				LOG(logINFO) << "El usuario ha solicitado ingresar al menu del juego.";
			}

			float timeStep = stepTimer.getTicks() / 1000.f;

			//Message msg("hola");
			//NetworkManager::getInstance().sendMessage(&msg);
			// TODO: player.update(timeStep);

			Message msg(1, true, false, true, false, true, false, true);



			std::vector<Message*> messages;
			messages.push_back(&msg);

			std::string outputBuffer;
			BoostSerializable::serialize_save(messages, outputBuffer);

			// Se manda outputBuffer al server.

			// EN EL SERVER
			// Intento recuperarlo
			std::vector<Message*> messages2;
			//string receiveBuffer;
			BoostSerializable::serialize_load(messages2, outputBuffer.c_str(), outputBuffer.size());





			stepTimer.start();

			/*	UNCOMMENT WHEN PLAYERS ARE DONE
			// Center the camera
			//camera.x = ((int)player.getPosition().x + player.getWidth() / 2) - SDLWindow::getInstance().getScreenWidth() / 2;
			//camera.y = ((int)player.getPosition().y + player.getHeight() / 2) - SDLWindow::getInstance().getScreenHeight() / 2;
				UNCOMMENT WHEN PLAYERS ARE DONE */

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
			for (vector<LayerView>::iterator it = layerViews.begin(); it != layerViews.end(); ++it) {
				LayerView* layerView = &(*it);
				layerView->renderLayer(0, 0, &camera);
			}

			// Render entities
			for (vector<EntityView*>::iterator it = entityViews.begin(); it != entityViews.end(); ++it) {
				EntityView* entityView = *it;
				entityView->draw(camera);
			}

			// Render players
			// TODO: foreach() -> playerView.render(camera.x, camera.y);

			SDL_RenderPresent(Renderer::getInstance().gRenderer);
		}
	}

	//Dispose entity views
	for (vector<EntityView*>::iterator it = entityViews.begin(); it != entityViews.end(); ++it) {
		EntityView* entityView = *it;
		delete entityView;
	}

	close();

	LOG(logINFO) << "El juego ha finalizado.";

	return 0;
}