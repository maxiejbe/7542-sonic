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
#include "utils/StringUtils.h"
#include "entities/ServerConfiguration.h"
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

	//Take config file from param
	if (argc > 2) {
		string arg = args[1];
		if (arg == configParamName) {
			configPath = args[2];
		}
	}

	ServerConfiguration serverConfig;
	Window window;
	Scenario scenario;
	Camera* cameraModel;
	vector<EntityView*> entityViews;
	Parser* parser = nullptr;

	int scenarioWidth;
	int scenarioHeight;

	int reconnectionAttemp;
	double reconnectionPause;
	bool connectionLostAbort = false;
	Banner reconnectionBanner = Banner("Reconnecting", { 255,255,102 });
	Banner waitingConnectionsBanner = Banner("Waiting for other connections", { 102,255,102 });
	Banner errorServerBanner = Banner("Error server", { 255,255,255 });

	Message * lastMessage = nullptr;

	// Parse local window and config
	Parser* localParser = new Parser(configPath, "");
	localParser->parse(&window);
	localParser->parse(&serverConfig);

	// Initialize network manager
	NetworkManager networkManager = NetworkManager::getInstance();

	if (!SDLWindow::getInstance().create(window.getWidth(), window.getHeight()) || !Renderer::getInstance().create()) {
		LOG(logERROR) << "Error al inicializar el juego!";
	}
	else {
		bool isRunning = true;
		Timer stepTimer;
		SDL_Rect camera;
		vector<LayerView> layerViews;

		// Initialize menu
		Menu menu = Menu();
		int i = menu.showMenu("disconnect");
		if (i == 2) { isRunning = false; }

		// Connect. TODO: mejorar esto del i
		if (i == 0) {

			// Connect to server
			networkManager.startClient(StringUtils::convert(serverConfig.getHost()), serverConfig.getPortNumber());

			while (networkManager.getPlayerNumber() < 0) {
				Sleep(3000);
			}

			while (networkManager.getFileContent().empty()) {
				Sleep(3000);
			}

			// Parse scenario
			parser = new Parser(configPath, networkManager.getFileContent());
			parser->parse(&scenario);

			scenarioWidth = scenario.getWidth();
			scenarioHeight = scenario.getHeight();

			// Initialize camera
			camera = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };

			// Initialize layers
			vector<Layer> layers = scenario.getLayers();
			for (vector<Layer>::iterator it = layers.begin(); it != layers.end(); ++it) {
				Layer* layer = &(*it);
				LayerView layerView(layer);
				layerViews.push_back(layerView);
			}

			// Initialize entities
			vector<Entity*> entities = scenario.getEntities();
			for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
				Entity* entity = *it;
				EntityView* entityView = EntityViewResolver::resolve(entity);
				entityViews.push_back(entityView);
			}

			// Load layers
			for (vector<LayerView>::iterator it = layerViews.begin(); it != layerViews.end(); ++it) {
				LayerView* layerView = &(*it);
				layerView->loadLayer();
			}

			while (!networkManager.canStartGame()) {
				waitingConnectionsBanner.showBanner();
				SDL_RenderPresent(Renderer::getInstance().gRenderer);
				Sleep(3000);
			}
		}

		// Connect. TODO: mejorar esto del i
		if (i == 0) {

			// Connect to server
			networkManager.startClient(StringUtils::convert(serverConfig.getHost()), serverConfig.getPortNumber());

			while (networkManager.getPlayerNumber() < 0) {
				Sleep(3000);
			}

			while (networkManager.getFileContent().empty()) {
				Sleep(3000);
			}

			// Parse scenario
			parser = new Parser(configPath, networkManager.getFileContent());
			parser->parse(&scenario);

			scenarioWidth = scenario.getWidth();
			scenarioHeight = scenario.getHeight();

			// Initialize camera
			camera = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };

			// Initialize layers
			vector<Layer> layers = scenario.getLayers();
			for (vector<Layer>::iterator it = layers.begin(); it != layers.end(); ++it) {
				Layer* layer = &(*it);
				LayerView layerView(layer);
				layerViews.push_back(layerView);
			}

			// Initialize entities
			vector<Entity*> entities = scenario.getEntities();
			for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
				Entity* entity = *it;
				EntityView* entityView = EntityViewResolver::resolve(entity);
				entityViews.push_back(entityView);
			}

			// Load layers
			for (vector<LayerView>::iterator it = layerViews.begin(); it != layerViews.end(); ++it) {
				LayerView* layerView = &(*it);
				layerView->loadLayer();
			}

			/* Comentar esto para probar el juego, hasta que este el banner. */
			while (!networkManager.canStartGame()) {
				//TODO: mostrar banner de "esperando que se conecte el resto"

				Sleep(3000);
			}
		}

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
				if (i == 1) { isRunning = false; } //show disconnect menu
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

	if (parser != nullptr) {
		delete parser;
	}
	if (localParser != nullptr) {
		delete localParser;
	}

	return 0;
}