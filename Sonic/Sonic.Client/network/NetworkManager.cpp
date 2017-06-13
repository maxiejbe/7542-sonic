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
	char receivedMsg[4096];
	int receivedMsgLen = 4096;
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
	const char * constRMessage = receivedMessage;
	ServerMessage * sMessage = new ServerMessage();
	if (!sMessage->fromJson(string(constRMessage))) {
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
		break;
	case player_entities_status:
		if (this->playerNumber < 0) break;
		this->updatePlayerViews(sMessage->getPlayers());
		this->updateCamera(sMessage->getCamera());
		//TODO: handle entities views
		break;
	case levels_content:
		this->gameLevels = sMessage->getLevels();
		break;
	case level_start:
		clientResponse->setType(MessageType::level_start_ok);
		//TODO: SETEAR CONFIGURACION DE NIVEL RECIBIDO
		this->sendMessage(clientResponse);
		this->startGame = true;

		this->continueHeartBeating = true;
		this->heartBeatThreadHandle = CreateThread(0, 0, runHeartBeatSocketHandler, (void*)this, 0, &this->heartBeatThreadId);

		lastHeartBeat = NULL;
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

vector<Level>* NetworkManager::getLevels()
{
	return this->gameLevels;
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
			PlayerView* playerView = new PlayerView(player);
			playerViews[index] = playerView;
			continue;
		}

		//Player view already exists, just update
		Player* player = playerViews[index]->getPlayer();
		player->copyFrom(*(*it));

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