#include "Client.h"

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
	if (this->socket == INVALID_SOCKET) {
		//TODO: Log in file
		fprintf(stderr, "Error accepting %d\n", WSAGetLastError());
		return false;
	}

	CreateThread(0, 0, runSocketHandler, (void*)this, 0, &this->threadId);
	return true;
}

void Client::closeSocket()
{
	closesocket(this->socket);
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
	int bytecount;

	do {
		memset(recievedMessage, 0, recievedMessageLen);
		if ((bytecount = recv(this->socket, recievedMessage, recievedMessageLen, 0)) == SOCKET_ERROR) {
			//TODO: Log in file
			fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
			return 0;
		}
		printf("Received bytes %d\nReceived string \"%s\"\n", bytecount, recievedMessage);
		
		this->handleRecievedMessage(recievedMessage);

	} while (bytecount > 0);

	this->server->removeClientConnection(this->clientNumber);

	cout << "Connection closed." << endl;
	return 0;
}
