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

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

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

	Message * lastMessage = nullptr;

	// Parse local window and config
	Parser* localParser = new Parser(configPath, "");
	localParser->parse(&window);
	localParser->parse(&serverConfig);

	if (!SDLWindow::getInstance().create(window.getWidth(), window.getHeight()) || !Renderer::getInstance().create()) {
		LOG(logERROR) << "Error al inicializar el juego!";
	}
	else {

		Banner reconnectionBanner = Banner("Reconnecting", { 0,0,0,150 }, "img/menu-background.jpg");
		Banner waitingConnectionsBanner = Banner("Waiting for other connections", { 0,0,0,150 }, "img/menu-background.jpg");
		Banner errorServerBanner = Banner("Server Error", { 0,0,0,150 });

		bool isRunning = true;

		Timer stepTimer;

		Timer fpsTimer;
		Timer capTimer;
		int countedFrames = 0;
		fpsTimer.start();


		SDL_Rect camera;
		vector<LayerView> layerViews;

		// Initialize menu
		Menu menu = Menu();
		int i = menu.showMenu();
		if (i == 2) { isRunning = false; }

		// Connect. TODO: mejorar esto del i
		if (i == 0) {

			// Connect to server
			NetworkManager::getInstance().startClient(StringUtils::convert(serverConfig.getHost()), serverConfig.getPortNumber());

			while (NetworkManager::getInstance().getPlayerNumber() < 0) {
				Sleep(3000);
			}

			while (NetworkManager::getInstance().getFileContent().empty()) {
				Sleep(3000);
			}

			// Parse scenario
			parser = new Parser(configPath, NetworkManager::getInstance().getFileContent());
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

			// Show waiting banner
			if (!NetworkManager::getInstance().canStartGame()) {
				waitingConnectionsBanner.showBanner();
				SDL_RenderPresent(Renderer::getInstance().gRenderer);

				while (!NetworkManager::getInstance().canStartGame()) {
					Sleep(1000);
				}
			}
		}

		while (isRunning) {

			capTimer.start();

			if (!NetworkManager::getInstance().online()) {
				double reconnetionTimeStep = capTimer.getTicks() / 1000.;
				reconnectionAttemp = 1;
				bool reconnected = false;
				while (!NetworkManager::getInstance().online() && reconnectionAttemp <= 3) {
					reconnectionBanner.showBanner();
					SDL_RenderPresent(Renderer::getInstance().gRenderer);

					double currentTime = capTimer.getTicks() / 1000.;
					if ((currentTime - reconnetionTimeStep) > 5) {
						reconnected = NetworkManager::getInstance().reconnect();
						reconnectionAttemp++;
						reconnetionTimeStep = capTimer.getTicks() / 1000.;
					}
				}

				if (!reconnected) connectionLostAbort = true;
			}

			if (connectionLostAbort) {
				int i = menu.showMenu();
				if (i == 2) { isRunning = false; }
				if (i == 1) {
					NetworkManager::getInstance().disconnect();
					i = menu.showMenu();
					if (i == 0) {
						NetworkManager::getInstance().reconnect();
						continue;
					}
					if (i == 2) {
						isRunning = false;
						continue;
					}
				}
				if (i == 0) {
					NetworkManager::getInstance().reconnect();
					continue;
				}
			}

			InputManager* input = InputManager::getInstance();
			input->update();

			if (input->quitRequested()) {
				isRunning = false;
				LOG(logINFO) << "El usuario ha solicitado la terminación del juego.";
			}


			if (input->isKeyDown(KEY_ESCAPE) || input->isKeyDown(KEY_Q)) {
				i = menu.showMenu();
				if (i == 2) { isRunning = false; }
				if (i == 1) //show disconnect menu
				{
					NetworkManager::getInstance().disconnect();
					i = menu.showMenu();
					if (i == 0) {
						NetworkManager::getInstance().reconnect();
						continue;
					}
					if (i == 2) {
						isRunning = false;
						continue;
					}
				}
				if (i == 0) {
					NetworkManager::getInstance().reconnect();
					continue;
				}
				LOG(logINFO) << "El usuario ha solicitado ingresar al menu del juego.";
			}

			//Calculate and correct fps
			float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
			if (avgFPS > 2000000)
			{
				avgFPS = 0;
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
			message->setType(MessageType::status);

			if (lastMessage == nullptr) {
				NetworkManager::getInstance().sendMessage(message);
				lastMessage = message;
			}
			else if (!lastMessage->equals(*message)) {
				NetworkManager::getInstance().sendMessage(message);
				delete lastMessage;
				lastMessage = message;
			}
			else {
				delete message;
			}

			stepTimer.start();

			// Initialize player
			PlayerView* playerView = NetworkManager::getInstance().getOwnPlayerView();
			Player* player = nullptr;
			if (playerView != nullptr) {
				player = playerView->getPlayer();
			}

			cameraModel = NetworkManager::getInstance().getCamera();
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
			unordered_map<int, PlayerView*> playerViews = NetworkManager::getInstance().getPlayerViews();
			if (!playerViews.empty()) {
				for (unordered_map<int, PlayerView*>::iterator it = playerViews.begin(); it != playerViews.end(); ++it) {
					it->second->render(camera.x, camera.y);
				}
			}

			SDL_RenderPresent(Renderer::getInstance().gRenderer);

			++countedFrames;

			//If frame finished early
			int frameTicks = capTimer.getTicks();
			if (frameTicks < SCREEN_TICK_PER_FRAME)
			{
				//Wait remaining time
				SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
			}
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