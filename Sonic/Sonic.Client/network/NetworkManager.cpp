#include "NetworkManager.h"

const int CLIENT_NUMBER_MAX_CONNECTED_PLAYERS = -99;

NetworkManager::NetworkManager()
{
	this->client = NULL;
	this->playerNumber = -1;
	this->camera = new Camera();
	this->startGame = false;
	this->gameLevels = nullptr;
}

NetworkManager::~NetworkManager()
{
	for (unordered_map<int, PlayerView*>::iterator it = playerViews.begin(); it != playerViews.end(); ++it) {
		if (it->second) delete it->second;
	}

	for (unordered_map<int, EntityView*>::iterator it = entityViews.begin(); it != entityViews.end(); ++it) {
		if (it->second) delete it->second;
	}

	if (this->camera != nullptr) delete this->camera;
}

void NetworkManager::close()
{
	if (this->client != NULL) { delete client; }
}

bool NetworkManager::startClient(char * host, int port)
{
	if (this->client) {
		//delete previous client
		delete this->client;
		this->client = NULL;
	}

	this->client = new SocketClient(host, port);

	if (!this->client->isConnected()) {
		LOG(logERROR) << "Network Manager: Error al inicializar el cliente";
		delete this->client;
		this->client = NULL;
		return false;
	}

	//TODO: inicializar receiver
	LOG(logINFO) << "Network Manager: Se inicializo el cliente correctamente - host: " << host << " puerto: " << port;

	//start handlers
	this->startConnectionHandlers();

	return true;
}

bool NetworkManager::online()
{
	return (this->client && this->client->isConnected());
}

bool NetworkManager::reconnect() {
	if (!this->client) return false;
	if (this->online()) return true;
	this->stopConnectionHandlers();
	//reset player number
	this->playerNumber = -1;

	if (!this->client->reconnect()) {
		LOG(logERROR) << "Network Manager: Fallo intento de reconexión";
		return false;
	}

	//reconnection success
	this->startConnectionHandlers();
	return true;
}

void NetworkManager::disconnect()
{
	this->playerNumber = -1;
	this->client->disconnectSocket();
	this->stopConnectionHandlers();
}

void NetworkManager::stopConnectionHandlers() {

	if (this->recvThreadHandle != NULL) {
		//WaitForSingleObject(this->recvThreadHandle, INFINITE);
		this->continueReceiving = false;
		CloseHandle(this->recvThreadHandle);
		this->recvThreadHandle = NULL;
	}

	if (this->heartBeatThreadHandle != NULL) {
		//WaitForSingleObject(this->heartBeatThreadHandle, INFINITE);
		this->continueHeartBeating = false;
		CloseHandle(this->heartBeatThreadHandle);
		this->heartBeatThreadHandle = NULL;
	}
}

void NetworkManager::startConnectionHandlers()
{
	this->continueReceiving = true;
	this->recvThreadHandle = CreateThread(0, 0, runRecvSocketHandler, (void*)this, 0, &this->recvThreadId);
}

DWORD WINAPI NetworkManager::runRecvSocketHandler(void * args)
{
	NetworkManager * nManager = (NetworkManager*)args;
	return nManager->recvSocketHandler();
}

DWORD NetworkManager::recvSocketHandler()
{
	char receivedMsg[10000];
	int receivedMsgLen = 10000;
	while (this->online() && this->continueReceiving)
	{
		if (!this->client->receiveMessage(receivedMsg, receivedMsgLen))
		{
			LOG(logERROR) << "Network Manager: Fallo la recepción de mensajes";
		}
		this->handleMessage(receivedMsg);
	}
	return 0;
}

void NetworkManager::handleMessage(char * receivedMessage)
{
	char * constRMessage = receivedMessage;
	char* multipleRootElements = "}{";
	vector<string> messages;

	//Try parse multiple elements. Split!
	string stringMessage = string(constRMessage);
	
	int start_pos = 0;
	int last_start_pos = 0;

	string message;
	while (std::string::npos != (start_pos = stringMessage.find(multipleRootElements, start_pos)))
	{
		++start_pos;
		int length = start_pos - last_start_pos;
		last_start_pos = start_pos;

		//Get next message from string
		message = stringMessage.substr(last_start_pos, start_pos);
		messages.push_back(message);
	}
	
	//Last message from string
	message = stringMessage.substr(last_start_pos, stringMessage.length() - last_start_pos);
	messages.push_back(message);
	
	for (vector<string>::iterator it = messages.begin(); it < messages.end(); it++)
	{
		ServerMessage * sMessage = new ServerMessage();
		if (!sMessage->fromJson(*it)) {
			LOG(logERROR) << "Network Manager: no se pudo deserializar el mensaje";
			delete sMessage;
			return;
		}

		Message* clientResponse = new Message();

		switch (sMessage->getType()) {
			case player_assign:
				LOG(logINFO) << "Network Manager: Assignación de numero de usuario -> " << sMessage->getPlayerNumber();
				if (sMessage->getPlayerNumber() != CLIENT_NUMBER_MAX_CONNECTED_PLAYERS) {
					clientResponse->setType(MessageType::player_assign_ok);
					this->sendMessage(clientResponse);
				}

				this->playerNumber = sMessage->getPlayerNumber();
				this->gameMode = sMessage->getGameMode();
				break;
			case player_entities_status:
				if (this->playerNumber < 0) break;
				this->ms = sMessage->getTime();
				this->updatePlayerViews(sMessage->getPlayers());
				this->updateEntityViews(sMessage->getEntities());
				this->updateCamera(sMessage->getCamera());
				//TODO: handle entities views
				break;
			case levels_content:
				this->gameLevels = sMessage->getLevels();
				break;
			case level_start:
				clientResponse->setType(MessageType::level_start_ok);
				this->actualLevel = sMessage->getLevelToStart();
				this->sendMessage(clientResponse);
				this->startGame = true;
				this->levelFinished = false;

				this->continueHeartBeating = true;
				this->heartBeatThreadHandle = CreateThread(0, 0, runHeartBeatSocketHandler, (void*)this, 0, &this->heartBeatThreadId);

				lastHeartBeat = NULL;
				break;
			case level_finish:
				this->levelFinished = true;
				break;
			case heart_beat_server:
				time(&lastHeartBeat);
				break;
			default:
				break;
		}
		
		delete clientResponse;
		delete sMessage;
	}
}

DWORD WINAPI NetworkManager::runHeartBeatSocketHandler(void * args)
{
	NetworkManager * nManager = (NetworkManager*)args;
	return nManager->heartBeatSocketHandler();
}

DWORD NetworkManager::heartBeatSocketHandler()
{
	while (this->online() && this->continueHeartBeating)
	{
		if (!lastHeartBeat) continue;
		time_t currentDate;
		time(&currentDate);
		int difference = difftime(currentDate, lastHeartBeat);
		if (difference > 3) {
			disconnect();
			continue;
		}
		Sleep(2000);
	}
	return 0;
}

void NetworkManager::sendMessage(Message* message)
{
	this->sendMessage(message, false);
}

void NetworkManager::sendMessage(Message* message, bool disconnect)
{
	if (!this->online()) {
		return;
	}

	//Serialize message before sending to server
	string stringMessage = message->serialize();

	if (!this->client->sendMessage(stringMessage, disconnect)) {
		LOG(logERROR) << "Network Manager: Falló envio de mensaje -> " << stringMessage;
	}

	//LOG(logINFO) << "Network Manager: Se envio mensaje -> " << stringMessage; // TODO: comentar!
}

unordered_map<int, PlayerView*> NetworkManager::getPlayerViews()
{
	return this->playerViews;
}

unordered_map<int, EntityView*> NetworkManager::getEntityViews()
{
	return this->entityViews;
}

Camera * NetworkManager::getCamera()
{
	return this->camera;
}

PlayerView * NetworkManager::getOwnPlayerView()
{
	int index = this->playerNumber - 1;
	if (!playerViews.count(index)) return nullptr;
	return playerViews[index];
}

bool NetworkManager::canStartGame()
{
	return this->startGame;
}

int NetworkManager::getPlayerNumber()
{
	//TODO: MUTEX HERE
	return this->playerNumber;
}

GameMode NetworkManager::getGameMode()
{
	return this->gameMode;
}

vector<Level>* NetworkManager::getLevels()
{
	return this->gameLevels;
}

bool NetworkManager::getLevelFinished()
{
	return this->levelFinished;
}

int NetworkManager::getActualLevel()
{
	return this->actualLevel;
}

void NetworkManager::updatePlayerViews(vector<Player*> players)
{
	//TODO: MUTEX HERE
	for (vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		int index = ((*it)->getNumber()) - 1;
		if (!playerViews.count(index)) {
			//Create new player view and include in map
			Player* player = new Player(*(*it));
			player->setTime(ms);
			PlayerView* playerView = new PlayerView(player);
			playerViews[index] = playerView;
			continue;
		}

		//Player view already exists, just update
		Player* player = playerViews[index]->getPlayer();
		player->setTime(ms);
		player->copyFrom(*(*it));
	}

	//Go remove missing players
	for (unordered_map<int, PlayerView*>::iterator it = playerViews.begin(); it != playerViews.end(); ++it) {
		int playerWasRemoved = true;

		for (vector<Player*>::iterator pit = players.begin(); pit != players.end(); ++pit)
		{
			int playerIndex = (*pit)->getNumber() - 1;
			if (playerIndex == it->first) {
				playerWasRemoved = false;
				break;
			}
		}

		if (playerWasRemoved) {
			it->second->getPlayer()->setIsActive(false);
		}
	}

	//Dispose
	for (vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
		delete *it;
	}
}

void NetworkManager::updateEntityViews(vector<Entity*> entities)
{
	//TODO: MUTEX HERE
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		int index = (*it)->getId() - 1;
		if (!entityViews.count(index)) {
			// Create new entity view and include in map
			Entity* entity = EntityResolver::resolve((*it)->getType());
			entity->setTime(ms);
			EntityView* entityView = EntityViewResolver::resolve(entity);
			entityViews[index] = entityView;
			continue;
		}

		// Player view already exists, just update
		Entity* entity = entityViews[index]->getEntity();
		entity->setTime(ms);
		entity->copyFrom(*(*it));
	}

	//Go remove missing entities
	for (unordered_map<int, EntityView*>::iterator it = entityViews.begin(); it != entityViews.end(); ++it) {
		int entityWasRemoved = true;
		for (vector<Entity*>::iterator pit = entities.begin(); pit != entities.end(); ++pit)
		{
			int idIndex = (*pit)->getId() - 1;
			if (idIndex == it->first) {
				entityWasRemoved = false;
				break;
			}
		}

		if (entityWasRemoved) {
			it->second->getEntity()->setIsActive(false);
		}
	}


	//Dispose
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		delete *it;
	}
}

void NetworkManager::updateCamera(Camera * camera)
{
	//TODO MUTEX HERE;
	this->camera->copyFrom(*camera);
}

bool NetworkManager::connectToServer(ServerConfiguration serverConfig) {
	char* host = StringUtils::convert(serverConfig.getHost());
	this->startClient(host, serverConfig.getPortNumber());
	delete host;

	if (this->online()) {
		return true;
	}

	return false;
}