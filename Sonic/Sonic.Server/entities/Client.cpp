#include "Client.h"

const char* MESSAGE_CLIENT_INCOMING_CONNECTION = "Conexión entrante desde IP: ";
const char* MESSAGE_CLIENT_REJECTED_CONNECTION = "Error aceptando conexión. ";
const char* MESSAGE_CLIENT_ACCEPTED_CONNECTION = "Conexión aceptada. Asignado el número de cliente ";

const char* MESSAGE_CLIENT_CONNECTION_CLOSED = "Se cerró la conexión con el cliente ";

const char* MESSAGE_CLIENT_ERROR_CODE = "Código de error: ";

const char* MESSAGE_CLIENT_DATA_RECV_INCORRECT = "No se pudo recibir correctamente el mensaje. ";
const char* MESSAGE_CLIENT_DATA_RECV_SUCCESS = "Se recibió correctamente el mensaje: ";

const char* MESSAGE_CLIENT_SEND_MESSAGE_ERROR = "No se pudo enviar el mensaje ";
const char* MESSAGE_CLIENT_SEND_FILE_CONTENT_ERROR = "No se pudo enviar el contenido del archivo de configuración";
const char* MESSAGE_CLIENT_SEND_MESSAGE_SUCCESS = "Se envió correctamente el mensaje ";


Client::Client(Server* server, Player* player)
{
	this->server = server;
}

Client::~Client()
{
	delete this->player;
}

int Client::getClientNumber()
{
	return this->clientNumber;
}

bool Client::acceptSocket()
{
	int addressSize = sizeof(address);
	this->socket = accept(this->server->getSocket(), (struct sockaddr *)&address, &addressSize);

	string clientIp = SocketUtils::getIpFromAddress(address);
	LOG(logINFO) << MESSAGE_CLIENT_INCOMING_CONNECTION << clientIp;

	if (this->socket == INVALID_SOCKET) {
		LOG(logERROR) << MESSAGE_CLIENT_REJECTED_CONNECTION << MESSAGE_CLIENT_ERROR_CODE << WSAGetLastError() << " (IP: " << clientIp << ")";
		return false;
	}
}

bool Client::welcome(int clientNumber, Player* player)
{
	this->clientNumber = clientNumber;
	int windowHeight = this->server->getWindow()->getHeight();
	int scenarioWidht = this->server->getScenario()->getWidth();
	int scenarioHeight = this->server->getScenario()->getHeight();
	int scrollSpeed = this->server->getConfiguration()->getScrollSpeed();
	
	//Player and last received message can handle reconnection
	if (player != nullptr) {
		this->player = player;
		this->player->setIsConnected(true);
	}
	else {
		this->player = new Player(this->clientNumber, windowHeight, scenarioWidht, scenarioHeight, scrollSpeed);
	}

	if (player != nullptr) {
		this->player = player;
	}
	else {
		this->player = new Player(this->clientNumber, windowHeight, scenarioWidht, scenarioHeight, scrollSpeed);
	}

	this->lastReceivedMessage = nullptr;

	LOG(logINFO) << MESSAGE_CLIENT_ACCEPTED_CONNECTION << this->clientNumber;

	if (!this->sendClientNumber()) {
		return false;
	}

	Sleep(10);

	if (!this->sendFileContent()) {
		return false;
	}

	CreateThread(0, 0, runSocketHandler, (void*)this, 0, &this->threadId);
	return true;
}

void Client::closeSocket()
{
	closesocket(this->socket);
}

bool Client::sendClientNumber()
{
	int bytecount;
	ServerMessage sMessage;
	sMessage.setType(player_assign);
	sMessage.setPlayerNumber(this->clientNumber);
	string serializedMsg = sMessage.serialize();
	const char* messageToSend = serializedMsg.c_str();

	if ((bytecount = send(this->socket, messageToSend, strlen(messageToSend), 0)) == SOCKET_ERROR) {
		LOG(logERROR) << MESSAGE_CLIENT_SEND_MESSAGE_ERROR << messageToSend << ". " << MESSAGE_CLIENT_ERROR_CODE << WSAGetLastError()
			<< " (Cliente " << this->clientNumber << ")";
		return false;
	}

	return true;
}

bool Client::sendFileContent()
{
	int bytecount;

	ServerMessage * message = new ServerMessage();
	message->setType(content);
	message->setFileContent(this->server->getFileContent());
	string serializedMessage = message->serialize();

	const char* fileContentMessage = serializedMessage.c_str();
	delete message;

	if ((bytecount = send(this->socket, fileContentMessage, strlen(fileContentMessage), 0)) == SOCKET_ERROR) {
		LOG(logERROR) << MESSAGE_CLIENT_SEND_FILE_CONTENT_ERROR << ". " << MESSAGE_CLIENT_ERROR_CODE << WSAGetLastError()
			<< " (Cliente " << this->clientNumber << ")";
		return false;
	}
	return true;
}

Player* Client::getPlayer()
{
	return this->player;
}

Message * Client::getLastMessage()
{
	return this->lastReceivedMessage;
}

SOCKET Client::getSocket()
{
	return this->socket;
}

bool Client::parseRecievedMessage()
{
	return false;
}

void Client::handleRecievedMessage(char* recievedMessage)
{
	string strMessage(recievedMessage);
	Message* message = new Message();
	message->fromJson(strMessage);

	if (this->lastReceivedMessage != nullptr) delete this->lastReceivedMessage;

	this->lastReceivedMessage = message;
}

DWORD Client::socketHandler() {
	char recievedMessage[1024];
	int recievedMessageLen = 1024;
	int bytecount = INT_MAX;

	while (bytecount > 0) {
		memset(recievedMessage, 0, recievedMessageLen);
		if ((bytecount = recv(this->socket, recievedMessage, recievedMessageLen, 0)) == SOCKET_ERROR) {
			LOG(logERROR) << MESSAGE_CLIENT_DATA_RECV_INCORRECT << MESSAGE_CLIENT_ERROR_CODE << WSAGetLastError() << " (Cliente " << this->clientNumber << ")";
			break;
		}

		LOG(logINFO) << MESSAGE_CLIENT_DATA_RECV_SUCCESS << recievedMessage << " (Cliente " << this->clientNumber << ")";

		this->handleRecievedMessage(recievedMessage);
	};

	LOG(logINFO) << MESSAGE_CLIENT_CONNECTION_CLOSED << this->clientNumber;

	this->server->removeClientConnection(this->clientNumber);

	return 0;
}
