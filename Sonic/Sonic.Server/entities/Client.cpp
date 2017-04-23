#include "Client.h"

DWORD WINAPI socketHandler(void*);

Client::Client(Server* server, SOCKET clientSocket, sockaddr_in clientAddress)
{
	this->server = server;
	this->socket = clientSocket;
	this->address = clientAddress;

	CreateThread(0, 0, &socketHandler, (void*)this->socket, 0, &this->threadId);
}


DWORD WINAPI socketHandler(void* cs) {
	SOCKET clientSocket = (SOCKET)cs;

	char buffer[1024];
	int buffer_len = 1024;
	int bytecount;

	do {
		memset(buffer, 0, buffer_len);
		if ((bytecount = recv(clientSocket, buffer, buffer_len, 0)) == SOCKET_ERROR) {
			fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
			return 0;
		}
		printf("Received bytes %d\nReceived string \"%s\"\n", bytecount, buffer);

		if ((bytecount = send(clientSocket, buffer, strlen(buffer), 0)) == SOCKET_ERROR) {
			fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
			return 0;
		}

		printf("Sent bytes %d\n", bytecount);

	} while (bytecount > 0);

	cout << "Connection closed." << endl;
	return 0;
}
