#include "Game.h"
#include "PlayState.h"
#include "MenuState.h"
#include "WaitingState.h"
#include "PauseState.h"

const int CLIENT_NUMBER_MAX_CONNECTED_PLAYERS = -99;
const int CLIENT_NUMBER_NOT_ACTIVE_PLAYER = -100;

PlayState PlayState::m_PlayState;

void PlayState::load(Game* game)
{
	int teamId = 0;

	if (!clientNumberSet()) {
		NetworkManager::getInstance().disconnect();
		game->changeState(MenuState::Instance());
		return;
	}

	while (NetworkManager::getInstance().getLevels() == nullptr || NetworkManager::getInstance().getLevels()->size() < 1) {
		Sleep(3000);
	}

	int levelNumber = NetworkManager::getInstance().getActualLevel() - 1;
	if (levelNumber < 0) levelNumber = 0;
	Level level = NetworkManager::getInstance().getLevels()->at(levelNumber);

	Scenario* scenario = level.getScenario();

	scenarioWidth = scenario->getWidth();
	scenarioHeight = scenario->getHeight();

	// Initialize camera
	camera = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };

	// Initialize layers
	vector<Layer> layers = scenario->getLayers();
	for (vector<Layer>::iterator it = layers.begin(); it != layers.end(); ++it) {
		Layer* layer = &(*it);
		LayerView layerView(layer);
		layerViews.push_back(layerView);
	}

	// Load layers
	for (vector<LayerView>::iterator it = layerViews.begin(); it != layerViews.end(); ++it) {
		LayerView* layerView = &(*it);
		layerView->loadLayer();
	}

	PlayerView* playerView = NetworkManager::getInstance().getOwnPlayerView();

	// Put player at the start and reset his values
	if (playerView != NULL) {
		playerView->getPlayer()->reset();
		teamId = playerView->getPlayer()->getTeamId();
	}
	else {
		teamId = this->team;
	}

	// Load statistics player panel
	statisticsPanel = new InGameStatisticsPanel(game->getGameMode(), teamId);

	game->pushState(WaitingState::Instance());

	SoundManager::getInstance().stopMusic();
	SoundManager::getInstance().close();

	if (levelNumber == 0)
		SoundManager::getInstance().playMusic("sounds/level1_song.mp3");
	else if (levelNumber == 1)
		SoundManager::getInstance().playMusic("sounds/level2_song.mp3");
	else if (levelNumber == 2)
		SoundManager::getInstance().playMusic("sounds/level3_song.mp3");

	// Show level name
	showLevelBackgroundName(level.getNumber());
}

int PlayState::unload()
{
	unordered_map<int, EntityView*> entityViews = NetworkManager::getInstance().getEntityViews();
	entityViews.clear();
	layerViews.clear();
	if (this->statisticsPanel) {
		statisticsPanel->freeSurfaceStatistics();
		delete statisticsPanel;
		statisticsPanel = NULL;
	}

	SoundManager::getInstance().stopMusic();
	SoundManager::getInstance().close();

	return 0;
}

void PlayState::update(Game* game, float dt)
{
	InputManager* input = InputManager::getInstance();
	input->update();

	if (input->quitRequested()) {
		LOG(logINFO) << "El usuario ha solicitado la terminación del juego.";
		game->quit();
		return;
	}

	if (input->isKeyDown(KEY_ESCAPE) || input->isKeyDown(KEY_Q)) {
		LOG(logINFO) << "El usuario ha solicitado ingresar al menu del juego.";
		stepTimer.pause();
		game->pushState(PauseState::Instance());
		stepTimer.unpause();
	}

	// Still online?
	if (!NetworkManager::getInstance().online()) {
		stepTimer.pause();
		game->pushState(ConnectState::Instance());
		stepTimer.unpause();
		lastMessage = nullptr; // new
	}

	/*if (reconnected) {
		lastMessage = nullptr;
	}*/

	double timeStep = stepTimer.getTicks() / 1000.;

	// Handle player input
	bool isKPLeft = input->isKeyPressed(KEY_LEFT);
	bool isKPSpace = input->isKeyPressed(KEY_SPACE);
	bool isKPRight = input->isKeyPressed(KEY_RIGHT);
	bool isKPUp = input->isKeyPressed(KEY_UP);
	bool isKPShift = input->isKeyPressed(KEY_LEFT_SHIFT);

	bool isKULeft = input->isKeyUp(KEY_LEFT);
	bool isKURight = input->isKeyUp(KEY_RIGHT);
	bool isKUSpace = input->isKeyUp(KEY_SPACE);
	bool isKUShift = input->isKeyUp(KEY_LEFT_SHIFT);
	bool isKUTest = input->isKeyUp(KEY_P);

	// Send message
	Message* message = new Message(timeStep, isKPLeft, isKPSpace, isKPRight, isKPUp, isKPShift, isKULeft, isKURight, isKUSpace, isKUShift, isKUTest);
	message->setType(MessageType::status);

	if (lastMessage == nullptr) {
		NetworkManager::getInstance().sendMessage(message);
		lastMessage = message;
		lastMessageFlag = true;
	}
	else if (!lastMessage->equals(*message)) {
		NetworkManager::getInstance().sendMessage(message);
		delete lastMessage;
		lastMessage = message;
		lastMessageFlag = true;
	}
	else {
		if (lastMessageFlag) {
			NetworkManager::getInstance().sendMessage(message);
			lastMessageFlag = false;
		}
		delete message;
	}

	stepTimer.start();

	// Get own player
	PlayerView* playerView = NetworkManager::getInstance().getOwnPlayerView();
	if (playerView != nullptr) {
		this->ownPlayer = playerView->getPlayer();
		if (input->isKeyDown(KEY_UP) && !this->ownPlayer->getIsJumping()) {
			SoundManager::getInstance().playSound("sounds/jump.wav");
		}
		if (!this->ownPlayer->getIsActive()) {
			game->changeState(GameOverState::Instance());
			return;
		}
	}

	// Update camera
	cameraModel = NetworkManager::getInstance().getCamera();
	if (cameraModel) {
		camera.x = (int)round(cameraModel->getPosition().x);
		camera.y = (int)round(cameraModel->getPosition().y);
	}

	// Check level or game finished
	if (NetworkManager::getInstance().getLevelFinished() || NetworkManager::getInstance().getGameFinished()) {
		game->changeState(EndLevelState::Instance());
	}
}

void PlayState::render(Game* game)
{
	// Clear screen
	SDL_SetRenderDrawColor(Renderer::getInstance().gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(Renderer::getInstance().gRenderer);

	// Render layers
	for (vector<LayerView>::iterator it = layerViews.begin(); it != layerViews.end(); ++it) {
		LayerView* layerView = &(*it);
		layerView->renderLayer(0, 0, &camera);
	}

	// Render Entities
	unordered_map<int, EntityView*> entityViews = NetworkManager::getInstance().getEntityViews();
	if (!entityViews.empty()) {
		for (unordered_map<int, EntityView*>::iterator it = entityViews.begin(); it != entityViews.end(); ++it) {
			it->second->draw(camera.x, camera.y);
		}
	}

	// Render players
	unordered_map<int, PlayerView*> playerViews = NetworkManager::getInstance().getPlayerViews();
	if (!playerViews.empty()) {
		for (unordered_map<int, PlayerView*>::iterator it = playerViews.begin(); it != playerViews.end(); ++it) {
			it->second->render(camera.x, camera.y);
		}
	}

	// Render statistics panel
	if (this->ownPlayer != nullptr) {
		statisticsPanel->showStatistics(this->ownPlayer);
	}

	entityViews.clear();
	playerViews.clear();
}

bool PlayState::clientNumberSet()
{
	while (NetworkManager::getInstance().getPlayerNumber() < 0) {
		if (NetworkManager::getInstance().getPlayerNumber() == CLIENT_NUMBER_MAX_CONNECTED_PLAYERS) {
			Banner maxClientsReached = Banner("Max players reached", { 0,0,0,150 }, "img/menu-background.jpg");
			maxClientsReached.showBanner();
			Sleep(1000);

			return false;
		}

		if (NetworkManager::getInstance().getPlayerNumber() == CLIENT_NUMBER_NOT_ACTIVE_PLAYER) {
			Banner maxClientsReached = Banner("You've lost, game has already started", { 0,0,0,150 }, "img/menu-background.jpg");
			maxClientsReached.showBanner();
			Sleep(1000);

			return false;
		}

		Sleep(10);
	}

	this->playerNumber = NetworkManager::getInstance().getPlayerNumber();
	return true;
}

void PlayState::showLevelBackgroundName(int level)
{
	Texture levelNameImage;
	string path = "img/level" + to_string(level) + "back.jpg";
	levelNameImage.loadFromFile(path);
	levelNameImage.render(0, 0, (int)(levelNameImage.getWidth()), (int)(levelNameImage.getHeight()));
	SDL_RenderPresent(Renderer::getInstance().gRenderer);

	Sleep(2000);
}