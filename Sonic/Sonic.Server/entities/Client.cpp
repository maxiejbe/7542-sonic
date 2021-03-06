#include "Client.h"

const char* MESSAGE_CLIENT_INCOMING_CONNECTION = "Conexi�n entrante desde IP: ";
const char* MESSAGE_CLIENT_REJECTED_CONNECTION = "Error aceptando conexi�n. ";
const char* MESSAGE_CLIENT_ACCEPTED_CONNECTION = "Conexi�n aceptada. Asignado el n�mero de cliente ";

const char* MESSAGE_CLIENT_CONNECTION_CLOSED = "Se cerr� la conexi�n con el cliente ";

const char* MESSAGE_CLIENT_ERROR_CODE = "C�digo de error: ";

const char* MESSAGE_CLIENT_DATA_RECV_INCORRECT = "No se pudo recibir correctamente el mensaje. ";
const char* MESSAGE_CLIENT_DATA_RECV_SUCCESS = "Se recibi� correctamente el mensaje: ";

const char* MESSAGE_CLIENT_SEND_MESSAGE_ERROR = "No se pudo enviar el mensaje ";
const char* MESSAGE_CLIENT_SEND_FILE_CONTENT_ERROR = "No se pudo enviar el contenido del archivo de configuraci�n";
const char* MESSAGE_CLIENT_SEND_MESSAGE_SUCCESS = "Se envi� correctamente el mensaje ";
const char* MESSAGE_CLIENT_SEND_LEVEL_ERROR = "No se pudo enviar los niveles";


Client::Client(Server* server)
{
	this->server = server;
}

Client::~Client()
{
	if (this->player && this->player != nullptr) {
		delete this->player;
	}

	this->terminateThreads();

	if (this->refreshThreadHandle != NULL)
	{
		this->continueRefreshing = false;
		CloseHandle(this->refreshThreadHandle);
		this->refreshThreadHandle = NULL;
	}
}

int Client::getClientNumber()
{
	return this->clientNumber;
}

bool Client::acceptSocket()
{
	int addressSize = sizeof(address);
	this->socket = accept(this->server->getSocket(), (struct sockaddr *)&address, &addressSize);
	if (this->socket == INVALID_SOCKET) {
		LOG(logERROR) << MESSAGE_CLIENT_REJECTED_CONNECTION << MESSAGE_CLIENT_ERROR_CODE << WSAGetLastError();
		return false;
	}

	string clientIp = SocketUtils::getIpFromAddress(address);
	LOG(logINFO) << MESSAGE_CLIENT_INCOMING_CONNECTION << clientIp;

	if (this->socket == INVALID_SOCKET) {
		LOG(logERROR) << MESSAGE_CLIENT_REJECTED_CONNECTION << MESSAGE_CLIENT_ERROR_CODE << WSAGetLastError() << " (IP: " << clientIp << ")";
		return false;
	}

	//Set send timeouts to 3 seconds
	int timeoutSeconds = 3;
	DWORD timeout = timeoutSeconds * 1000;
	setsockopt(this->socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));

	char i;
	setsockopt(this->socket, IPPROTO_TCP, TCP_NODELAY, (char *)&i, sizeof(i));

	return true;
}

bool Client::welcome(int clientNumber, Player* player)
{
	this->clientNumber = clientNumber;
	int windowHeight = this->server->getWindow()->getHeight();
	int scenarioWidht = this->server->getScenario()->getWidth();
	int scenarioHeight = this->server->getScenario()->getHeight();
	int scrollSpeed = this->server->getConfiguration()->getScrollSpeed();

	//Player and last received message can handle reconnection
	this->player = new Player(this->clientNumber, windowHeight, scenarioWidht, scenarioHeight, scrollSpeed, this->server->getTeamPoints(),
		this->server->getTeamRings(), this->server->getGameConfig()->getMode());
	if (player != nullptr) {
		this->player->copyFrom(*player);
		//this->player = player;
		this->player->setIsConnected(true);
	}

	this->lastReceivedMessage = nullptr;

	LOG(logINFO) << MESSAGE_CLIENT_ACCEPTED_CONNECTION << this->clientNumber;

	if (!this->sendClientNumber()) {
		return false;
	}

	this->continueReceiving = true;
	this->recvThreadHandle = CreateThread(0, 0, runReceiveSocketHandler, (void*)this, 0, &this->threadId);

	return true;
}

void Client::closeSocket()
{
	closesocket(this->socket);
}

void Client::terminateThreads()
{
	if (this->recvThreadHandle != NULL) {
		this->continueReceiving = false;
		CloseHandle(this->recvThreadHandle);
		this->recvThreadHandle = NULL;
	}

	if (this->heartBeatThreadHandle != NULL) {
		this->continueHeartBeating = false;
		CloseHandle(this->heartBeatThreadHandle);
		this->heartBeatThreadHandle = NULL;
	}

	if (this->sendThreadHandle != NULL)
	{
		this->continueSending = false;
		CloseHandle(this->sendThreadHandle);
		this->sendThreadHandle = NULL;
	}

	if (this->sendEntitiesThreadHandle != NULL)
	{
		this->continueSendingEntites = false;
		CloseHandle(this->sendEntitiesThreadHandle);
		this->sendEntitiesThreadHandle = NULL;
	}
}

bool Client::sendMessage(const char* serializedMessage, bool dispose = false)
{
	char fixedSerializedMessage[2048] = "";
	for (size_t i = 0; i < strlen(serializedMessage); i++)
	{
		fixedSerializedMessage[i] = serializedMessage[i];
	}
	int messageLength = strlen(fixedSerializedMessage);

	int bytecount;
	if ((bytecount = send(this->getSocket(), fixedSerializedMessage, 2048, 0)) == SOCKET_ERROR) {
		LOG(logERROR) << MESSAGE_CLIENT_SEND_MESSAGE_ERROR << serializedMessage << ". " << MESSAGE_CLIENT_ERROR_CODE << WSAGetLastError()
			<< " (Cliente " << this->getClientNumber() << ")";
		if (dispose) delete serializedMessage;
		return false;
	}
	if (dispose) delete serializedMessage;
	return true;
}

bool Client::sendHeartBeat() {
	int bytecount;
	ServerMessage sMessage;
	sMessage.setType(heart_beat_server);
	string serializedMsg = sMessage.serialize();
	const char* messageToSend = serializedMsg.c_str();

	return this->sendMessage(messageToSend);
}

bool Client::sendClientNumber()
{
	int bytecount;
	ServerMessage sMessage;
	sMessage.setType(player_assign);
	sMessage.setGameMode(this->server->getGameConfig()->getMode());
	sMessage.setPlayerNumber(this->clientNumber);
	string serializedMsg = sMessage.serialize();
	const char* messageToSend = serializedMsg.c_str();

	return this->sendMessage(messageToSend);
}

bool Client::sendLevels()
{
	int bytecount;

	ServerMessage * message = new ServerMessage();
	message->setType(levels_content);
	message->setLevels(this->server->getLevels());
	string serializedMessage = message->serialize();
	const char* levelsMessage = serializedMessage.c_str();
	delete message;

	return this->sendMessage(levelsMessage);
}

bool Client::sendStatus()
{
	int bytecount;

	ServerMessage * message = this->server->getStatusMessage();
	char * serializedMessage = StringUtils::convert(message->serialize());
	delete message;

	return this->sendMessage(serializedMessage, true);
}

bool Client::sendEntitiesStatus()
{
	int bytecount;

	ServerMessage * message = this->server->getEntitiesStatusMessage();
	char * serializedMessage = StringUtils::convert(message->serialize());
	delete message;

	return this->sendMessage(serializedMessage, true);
}

bool Client::sendLevelStart()
{
	int bytecount;

	ServerMessage* message = new ServerMessage();
	message->setType(ServerMessageType::level_start);
	message->setLevelToStart(this->server->getCurrentLevel());
	char* serializedMessage = StringUtils::convert(message->serialize());
	delete message;

	int result = this->sendMessage(serializedMessage, true);
	this->gameStartSent = true;
	return result;
}

bool Client::sendLevelFinish()
{
	int bytecount;

	ServerMessage * message = this->server->getStatusMessage();
	message->setType(level_finish);
	char * serializedMessage = StringUtils::convert(message->serialize());
	delete message;

	return this->sendMessage(serializedMessage, true);
}

bool Client::sendGameFinish()
{
	int bytecount;

	ServerMessage * message = this->server->getStatusMessage();
	message->setType(game_finish);
	char * serializedMessage = StringUtils::convert(message->serialize());
	delete message;

	return this->sendMessage(serializedMessage, true);
}

Player* Client::getPlayer()
{
	return this->player;
}

void Client::setPlayer(Player * player)
{
	this->player = player;
}

Message * Client::getLastMessage()
{
	return this->lastReceivedMessage;
}

SOCKET Client::getSocket()
{
	return this->socket;
}

bool Client::parseReceivedMessage()
{
	return false;
}

void Client::handleReceivedMessage(char* recievedMessage)
{
	string strMessage(recievedMessage);
	Message* message = new Message();
	if (!message->fromJson(strMessage)) {
		delete message;
		return;
	}

	switch (message->getType())
	{
	case player_assign_ok:
		if (message->getTeamId() > 0) {
			this->player->setTeamId(message->getTeamId());
		}
		sendLevels();
		break;
	case levels_content_ok:
		this->server->addConnectedClients();
		break;
	case level_start_ok:
		startRefereshing();
		startSending();
		startSendingEntities();
		startHeartBeating();
	case status:
		if (this->lastReceivedMessage != nullptr) delete this->lastReceivedMessage;
		this->lastReceivedMessage = message;
		return; // Avoid deleting message
	default:
		break;
	}

	delete message;
}

void Client::startRefereshing()
{
	if (this->continueRefreshing) return;

	this->continueRefreshing = true;
	this->refreshThreadHandle = CreateThread(0, 0, refreshSocketHandler, (void*)this, 0, &this->refreshThreadId);
}

void Client::startSending()
{
	if (this->continueSending) return;

	this->continueSending = true;
	this->sendThreadHandle = CreateThread(0, 0, runSendSocketHandler, (void*)this, 0, &this->sendThreadId);
}

void Client::startSendingEntities()
{
	if (this->continueSendingEntites) return;

	this->continueSendingEntites = true;
	this->sendEntitiesThreadHandle = CreateThread(0, 0, runSendEntitiesSocketHandler, (void*)this, 0, &this->sendEntitiesThreadId);
}

void Client::startHeartBeating()
{
	if (this->continueHeartBeating) return;

	this->continueHeartBeating = true;
	this->heartBeatThreadHandle = CreateThread(0, 0, runHeartBeatSocketHandler, (void*)this, 0, &this->heartBeatThreadId);
}

DWORD WINAPI Client::runReceiveSocketHandler(void * args)
{
	Client * client = (Client*)args;
	return client->receiveSocketHandler();
}

DWORD Client::receiveSocketHandler() {
	char recievedMessage[2048];
	int recievedMessageLen = 2048;
	int bytecount = INT_MAX;

	while (bytecount > 0 && this->continueReceiving) {
		memset(recievedMessage, 0, recievedMessageLen);
		if ((bytecount = recv(this->socket, recievedMessage, recievedMessageLen, 0)) == SOCKET_ERROR) {
			LOG(logERROR) << MESSAGE_CLIENT_DATA_RECV_INCORRECT << MESSAGE_CLIENT_ERROR_CODE << WSAGetLastError() << " (Cliente " << this->clientNumber << ")";
			continue;
		}

		LOG(logINFO) << MESSAGE_CLIENT_DATA_RECV_SUCCESS << recievedMessage << " (Cliente " << this->clientNumber << ")";

		this->handleReceivedMessage(recievedMessage);
	};

	LOG(logINFO) << MESSAGE_CLIENT_CONNECTION_CLOSED << this->clientNumber;

	return 0;
}

DWORD WINAPI Client::refreshSocketHandler(void * args)
{
	Client * client = (Client*)args;
	return client->refreshSocketHandler();
}

DWORD Client::refreshSocketHandler()
{
	while (this->continueRefreshing) {
		this->refreshPlayer();

		if (this->getLastMessage() == NULL) {
			Sleep(10);
			continue;
		}

		int sleepingTime = this->getLastMessage()->getTimeStep() * 1000 - 2;
		if (sleepingTime > 0 && sleepingTime < 100) {
			Sleep(sleepingTime);
		}
		else {
			Sleep(16);
		}
	}

	return 0;
}

DWORD WINAPI Client::runSendSocketHandler(void * args)
{
	Client * client = (Client*)args;
	return client->sendSocketHandler();
}

DWORD Client::sendSocketHandler()
{
	while (this->continueSending) {
		this->sendStatus();

		if (this->getLastMessage() == NULL) {
			Sleep(10);
			continue;
		}

		int sleepingTime = this->getLastMessage()->getTimeStep() * 1000 - 2;
		if (sleepingTime > 0 && sleepingTime < 100) {
			Sleep(sleepingTime);
		}
		else {
			Sleep(16);
		}
	}

	return 0;
}

DWORD Client::runSendEntitiesSocketHandler(void * args)
{
	Client * client = (Client*)args;
	return client->sendEntitiesSocketHandler();
}

DWORD Client::sendEntitiesSocketHandler()
{
	while (this->continueSendingEntites) {
		this->sendEntitiesStatus();
		Sleep(10);
	}

	return 0;
}

bool Client::refreshPlayer() {
	if (this->player == nullptr) return false;

	if (this->getLastMessage() != nullptr && this->getLastMessage()->getType() == MessageType::status) {
		PlayerController::update(this->getLastMessage(), this->getPlayer(), this->server->getCamera(), this->server->getScenario(), timer.elapsed());
		if ((this->getPlayer()->getPosition().x + this->getPlayer()->getWidth()) >= (this->server->getScenario()->getWidth() - 100)) {
			//level final reached
			this->server->levelFinished();
		}
	}

	player->serializePlayer();
	return true;
}

bool Client::notifyLevelFinished()
{
	//send finish level
	this->sendLevelFinish();
	return true;
}

bool Client::notifyStartNewLevel()
{
	//reset user position
	this->player->reset();
	this->sendLevelStart();
	return true;
}

bool Client::notifyGameFinished()
{
	this->sendGameFinish();
	return true;
}

void Client::setClientNumber(int clientNumber)
{
	this->clientNumber = clientNumber;
}

DWORD WINAPI Client::runHeartBeatSocketHandler(void * args)
{
	Client * client = (Client*)args;
	return client->heartBeatSocketHandler();
}

DWORD Client::heartBeatSocketHandler()
{
	while (this->continueHeartBeating)
	{
		if (!this->sendHeartBeat()) {
			this->server->removeClientConnection(this->clientNumber);
		}
		Sleep(2000);
	}
	return 0;
}


