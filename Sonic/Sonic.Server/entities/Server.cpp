#include "Server.h"

Server::Server(int portNumber, int maxAllowedClients)
{
	this->portNumber = portNumber;
	this->maxAllowedClients = maxAllowedClients;
	this->isValid = false;

	clients.clear();

	if (!initializeWindowsSupport()) {
		return;
	}
	if (!initSocket()) {
		return;
	}
	if (!configureAddress()) {
		return;
	}
	if (!bindSocket()) {
		return;
	}
	if (!startListening()) {
		return;
	}

	this->isValid = true;
}

bool Server::initializeWindowsSupport()
{
	WSADATA wsaData;
	unsigned short wVersionRequested = MAKEWORD(2, 2);
	int initResult = WSAStartup(wVersionRequested, &wsaData);
	if (initResult != 0 || (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)) {
		//TODO: Log in file
		fprintf(stderr, "Could not find useable sock dll %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool Server::initSocket()
{
	//create socket
	this->_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->_socket == INVALID_SOCKET)
	{
		//TODO: Log in file
		cout << "Cannot open socket" << endl;
		cout << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

bool Server::configureAddress()
{
	//Take a look at: http://stackoverflow.com/questions/3492647/what-are-the-alternative-for-win32-to-alarm-bzero-bcopy-when-porting-c-code
	bzero((char*)&this->address, sizeof(this->address));

	this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = INADDR_ANY;
	this->address.sin_port = htons(this->portNumber);

	return true;
}

bool Server::bindSocket()
{
	//bind socket
	if (bind(_socket, (struct sockaddr *)&this->address, sizeof(this->address)) < 0)
	{
		//TODO: Log in file
		cerr << "Cannot bind" << endl;
		return false;
	}
	return true;
}

bool Server::startListening()
{
	if (listen(_socket, 5) < 0) {
		fprintf(stderr, "Error listening %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

bool Server::waitForClientConnections()
{
	struct sockaddr_in clientAddress;
	int addressSize = sizeof(clientAddress);

	while (true) {
		printf("waiting for a connection\n");

		SOCKET clientSocket = accept(this->_socket, (struct sockaddr *)&clientAddress, &addressSize);
		if (clientSocket == INVALID_SOCKET) {
			fprintf(stderr, "Error accepting %d\n", WSAGetLastError());
			return 0;
		}

		Client client(this, clientSocket, clientAddress);

		//char stringIp[sizeof(clientAddress)];
		//inet_ntop(AF_INET, &(clientAddress.sin_addr), stringIp, INET_ADDRSTRLEN);
		//cout << "Recieved connection from " << stringIp << endl;
	}
}

bool Server::validate()
{
	return this->isValid;
}
