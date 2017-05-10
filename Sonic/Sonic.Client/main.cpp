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
#include "Banner.h"

#include "views/common/EntityViewResolver.h"
#include <unordered_map>

char* SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 5000;

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
	Logger::loggingLevel() = logLOW;

	string configParamName = "--config";
	string configPath = "";

	//Initialize network manager
	NetworkManager networkManager = NetworkManager::getInstance();
	networkManager.startClient(SERVER_IP, SERVER_PORT);

	while (networkManager.getPlayerNumber() < 0) {
		Sleep(3000);
	}

	while (networkManager.getFileContent().empty()) {
		Sleep(3000);
	}

	Parser* parser = new Parser(configPath, networkManager.getFileContent());
	Window window;
	Configuration config;
	Scenario scenario;
	Camera * cameraModel;

	parser->parse(&window);
	parser->parse(&config);
	parser->parse(&scenario);

	int scenarioWidth = scenario.getWidth();
	int scenarioHeight = scenario.getHeight();

	int reconnectionAttemp;
	double reconnectionPause;
	bool connectionLostAbort = false;
	Banner reconnectionBanner;

	Message * lastMessage = nullptr;
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

		// Initialize camera
		Timer stepTimer;
		SDL_Rect camera = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };
		
		// Initialize menu
		Menu menu = Menu();
		int i = menu.showMenu("disconnect");
		if (i == 1) { isRunning = false; }
		if (i == 2) { isRunning = false; }

		while (isRunning) {

			if (!networkManager.online()) {
				double reconnetionTimeStep = stepTimer.getTicks() / 1000.;
				reconnectionAttemp = 1;
				bool reconnected = false;
				while (!networkManager.online() && reconnectionAttemp <= 3) {
					reconnectionBanner.showBanner();
					SDL_RenderPresent(Renderer::getInstance().gRenderer);
					
					double currentTime = stepTimer.getTicks() / 1000.;
					if ((currentTime - reconnetionTimeStep) > 5) {
						reconnected = networkManager.reconnect();
						reconnectionAttemp++;
						reconnetionTimeStep = stepTimer.getTicks() / 1000.;
					}
				}

				if (!reconnected) connectionLostAbort = true;
			}

			if (connectionLostAbort) break;

			InputManager* input = InputManager::getInstance();
			input->update();

			if (input->quitRequested()) {
				isRunning = false;
				LOG(logINFO) << "El usuario ha solicitado la terminación del juego.";
			}

			if (input->isKeyDown(KEY_ESCAPE) || input->isKeyDown(KEY_Q)) {
				i = menu.showMenu("connect");
				if (i == 1) { isRunning = false; }
				if (i == 2) { isRunning = false; }
				LOG(logINFO) << "El usuario ha solicitado ingresar al menu del juego.";
			}

			double timeStep = stepTimer.getTicks() / 1000.;

			//Handle player input
			bool isKPLeft = input->isKeyPressed(KEY_LEFT);
			bool isKPSpace = input->isKeyPressed(KEY_SPACE);
			bool isKPRight = input->isKeyPressed(KEY_RIGHT);
			bool isKPUp = input->isKeyPressed(KEY_UP);

			bool isKULeft = input->isKeyUp(KEY_LEFT);
			bool isKURight = input->isKeyUp(KEY_RIGHT);
			bool isKUSpace = input->isKeyUp(KEY_SPACE);

			Message* message = new Message(timeStep, isKPLeft, isKPSpace, isKPRight, isKPUp, isKULeft, isKURight, isKUSpace);

			if (lastMessage == nullptr) {
				networkManager.sendMessage(message);
				lastMessage = message;
			}
			else if (!lastMessage->equals(*message)) {
				networkManager.sendMessage(message);
				delete lastMessage;
				lastMessage = message;
			}
			else {
				delete message;
			}

			stepTimer.start();

			// Initialize player
			PlayerView* playerView = networkManager.getOwnPlayerView();
			Player* player = nullptr;
			if (playerView != nullptr) {
				player = playerView->getPlayer();
			}

			cameraModel = networkManager.getCamera();
			if (cameraModel) {
				camera.x = cameraModel->getPosition().x;
				camera.y = cameraModel->getPosition().y;
			}
			

			// UNCOMMENT WHEN PLAYERS ARE DONE
			// Center the camera
			if (player != nullptr) {
				/*int bordeR = camera.x + SDLWindow::getInstance().getScreenWidth() - 100;
				int bordeL = camera.x + 100;

				camera.y = ((int)player->getPosition().y + player->getHeight() / 2) - SDLWindow::getInstance().getScreenHeight() / 2;
				if (player->getPosition().x > bordeR) { camera.x = camera.x + player->getPosition().x - bordeR; }
				if (player->getPosition().x < bordeL) { camera.x = camera.x + player->getPosition().x - bordeL; }

				// Keep the camera in bounds
				if (camera.x < 0)
					camera.x = 0;
				if (camera.y < 0)
					camera.y = 0;

				if (camera.x > scenarioWidth - camera.w)
					camera.x = scenarioWidth - camera.w;
				if (camera.y > scenarioHeight - camera.h)
					camera.y = scenarioHeight - camera.h;*/
			}

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
			// TODO: MUTEX HERE?!?!?!
			unordered_map<int, PlayerView*> playerViews = networkManager.getPlayerViews();
			if (!playerViews.empty()) {
				for (unordered_map<int, PlayerView*>::iterator it = playerViews.begin(); it != playerViews.end(); ++it) {
					it->second->render(camera.x, camera.y);
				}
			}

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

	delete parser;

	return 0;
}