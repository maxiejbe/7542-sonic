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


Client::Client(Server* server, int clientNumber)
{
	this->clientNumber = clientNumber;
	this->server = server;

	int windowHeight = this->server->getWindow()->getHeight();
	int scenarioWidht = this->server->getScenario()->getWidth();
	int scenarioHeight = this->server->getScenario()->getHeight();
	int scrollSpeed = this->server->getConfiguration()->getScrollSpeed();

	this->player = new Player(this->clientNumber, windowHeight, scenarioWidht, scenarioHeight, scrollSpeed);
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

	LOG(logINFO) << MESSAGE_CLIENT_ACCEPTED_CONNECTION << this->clientNumber;

	if (!this->sendClientNumber()) {
		return false;
	}

	//if (!this->sendFileContent()) {
	//	return false;
	//}
	
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
	string fileContent = this->server->getFileContent();
	if ((bytecount = send(this->socket, fileContent.c_str(), strlen(fileContent.c_str()), 0)) == SOCKET_ERROR) {
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

	//this->server->lock();

	PlayerController::update(message, this->player);

	//this->server->unlock();

	delete message;

	//Then, send broadcast message
	this->server->sendBroadcast();
}

DWORD Client::socketHandler() {
	char recievedMessage[1024];
	int recievedMessageLen = 1024;
	int bytecount = INT_MAX;

	while (bytecount > 0) {
		memset(recievedMessage, 0, recievedMessageLen);
		if ((bytecount = recv(this->socket, recievedMessage, recievedMessageLen, 0)) == SOCKET_ERROR) {
			LOG(logERROR) << MESSAGE_CLIENT_DATA_RECV_INCORRECT << MESSAGE_CLIENT_ERROR_CODE << WSAGetLastError() << " (Cliente " << this->clientNumber << ")";
			return 0;
		}
		
		LOG(logINFO) << MESSAGE_CLIENT_DATA_RECV_SUCCESS << recievedMessage << " (Cliente " << this->clientNumber << ")";

		this->handleRecievedMessage(recievedMessage);
	};

	LOG(logINFO) << MESSAGE_CLIENT_CONNECTION_CLOSED << this->clientNumber;

	this->server->removeClientConnection(this->clientNumber);

	return 0;
}
