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


Client::Client(Server* server, int clientNumber)
{
	this->clientNumber = clientNumber;
	this->server = server;
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

	//if (!this->sendClientNumber()) {
	//	return false;
	//}

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
	string stringMessage = to_string(this->clientNumber);
	
	if ((bytecount = send(this->socket, stringMessage.c_str(), strlen(stringMessage.c_str()), 0)) == SOCKET_ERROR) {
		LOG(logERROR) << MESSAGE_CLIENT_SEND_MESSAGE_ERROR << stringMessage << ". " << MESSAGE_CLIENT_ERROR_CODE << WSAGetLastError()
			<< " (Cliente " << this->clientNumber << ")";
		return false;
	}
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
	//TODO: Handle message and do certain action.
	
	//Then, send broadcast message
	this->server->sendBroadcast(recievedMessage);
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

		string strMessage(recievedMessage);
		Message message;
		message.unserialize(strMessage);

		//if (message.validate()) {
		//	this->handleRecievedMessage(recievedMessage);
		//}
		
		//string convertedMessage;
		//message.toString(&convertedMessage);

		//printf("Received bytes %d\nReceived string \"%s\"\n", bytecount, recievedMessage /*convertedMessage.c_str()*/);
	};

	LOG(logINFO) << MESSAGE_CLIENT_CONNECTION_CLOSED << this->clientNumber;

	this->server->removeClientConnection(this->clientNumber);

	return 0;
}
