#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	this->client = NULL;
	this->playerNumber = -1;
	this->camera = new Camera();
}

NetworkManager::~NetworkManager()
{
	for (map<int, PlayerView*>::iterator it = playerViews.begin(); it != playerViews.end(); ++it)
	{
		delete it->second->getPlayer();
		delete it->second;
	}

	if (this->camera) delete this->camera;
}

void NetworkManager::close()
{
	if (this->client) { delete client; }
}

bool NetworkManager::startClient(char * host, int port)
{
	if (this->client) {
		//delete previous client
		delete this->client;
	}

	this->client = new SocketClient(host, port);

	if (!this->client->isConnected()) {
		LOG(logERROR) << "Network Manager: Error al inicializar el cliente";
		delete this->client;
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


void NetworkManager::startConnectionHandlers()
{
	//Receive Handler
	//TODO: kill theads
	CreateThread(0, 0, runRecvSocketHandler, (void*)this, 0, &this->recvThreadId);
	//CreateThread(0, 0, runSendSocketHandler, (void*)this, 0, &this->sendThreadId);
}

DWORD WINAPI NetworkManager::runRecvSocketHandler(void * args)
{
	NetworkManager * nManager = (NetworkManager*)args;
	return nManager->recvSocketHandler();
}

DWORD NetworkManager::recvSocketHandler()
{
	char receivedMsg[1024];
	int receivedMsgLen = 1024;
	while (this->online())
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
		return;
	}

	switch (sMessage->getType()) {
	case player_assign:
		LOG(logINFO) << "Network Manager: Assignación de numero de usuario -> " << sMessage->getPlayerNumber();
		//TODO: MUTEX HERE
		this->playerNumber = sMessage->getPlayerNumber();
		break;
	case players_status:
		this->updatePlayerViews(sMessage->getPlayers());
		this->updateCamera(sMessage->getCamera());
		break;
	default:
		LOG(logERROR) << "Network Manager: Mensaje invalido -> " << receivedMessage;
		break;
	}

	delete sMessage;
}

DWORD WINAPI NetworkManager::runSendSocketHandler(void * args)
{
	NetworkManager * nManager = (NetworkManager*)args;
	return nManager->sendSocketHandler();
}

DWORD NetworkManager::sendSocketHandler()
{
	//send new message
	while (this->online() && this->playerNumber < 0) {
		//wait till user gets number
		if (this->playerNumber > 0) {
			Message * msg = new Message(/*this->player->getNumber()*/);
			this->sendMessage(msg);
			delete msg;
		}
		//wait 3 seconds;
		Sleep(3000);
	}

	return 0;
}

void NetworkManager::sendMessage(Message* message)
{
	if (!this->online()) {
		return;
	}

	//Serialize message before sending to server
	string stringMessage = message->serialize();

	if (this->client->sendMessage(stringMessage)) {
		//LOG(logINFO) << "Network Manager: Se envio mensaje -> " << stringMessage;
	}
	else {
		LOG(logERROR) << "Network Manager: Falló envio de mensaje -> " << stringMessage;
	}
}

map<int, PlayerView*> NetworkManager::getPlayerViews()
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

int NetworkManager::getPlayerNumber()
{
	//TODO: MUTEX HERE
	return this->playerNumber;
}

string NetworkManager::getFileContent()
{
	return this->fileContent;
}

void NetworkManager::updatePlayerViews(vector<Player*> players)
{
	//TODO: MUTEX HERE
	for (vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		int index = (*it)->getNumber();
		if (!playerViews.count(index)) {
			//Create new player view and include in map
			Player* player = new Player(*(*it));
			PlayerView* playerView = new PlayerView(player);
			playerViews[player->getNumber()] = playerView;
			continue;
		}

		//Player view already exists, just update
		Player* player = playerViews[index]->getPlayer();
		player->copyFrom(*(*it));
	}
}

void NetworkManager::updateCamera(Camera * camera)
{
	//TODO MUTEX HERE;
	this->camera->copyFrom(*camera);
}
