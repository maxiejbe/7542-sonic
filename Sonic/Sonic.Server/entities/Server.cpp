#include "Server.h"

Server::~Server()
{
	for (vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (*it != NULL) {
			closesocket((*it)->getSocket());
			delete *it;
		}
	}
}

Server::Server(int portNumber, int maxAllowedClients)
{
	this->portNumber = portNumber;
	this->maxAllowedClients = maxAllowedClients;
	this->isValid = false;

	this->connectedClients = 0;
	clients.clear();

	for (int i = 0; i < this->maxAllowedClients; i++) {
		clients.insert(clients.begin() + i, NULL);
	}

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
	if (::bind(_socket, (struct sockaddr *)&this->address, sizeof(this->address)) < 0)
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

int Server::getAvailableIndex()
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i] == NULL) return i;
	}
	return 0;
}

void Server::acceptClientConnection()
{
	int index = getAvailableIndex();
	int clientNumber = index + 1;

	Client* client = new Client(this, clientNumber);
	if (!client->acceptSocket()) {
		delete client;
		return;
	}

	clients[index] = client;
	this->connectedClients++;
}

void Server::removeClientConnection(int clientNumber)
{
	int index = clientNumber - 1;
	
	Client* clientPointer = clients[index];
	clientPointer->closeSocket();
	delete clientPointer;

	clients[index] = NULL;

	this->connectedClients--;
}

SOCKET Server::getSocket()
{
	return this->_socket;
}

void Server::waitForClientConnections()
{
	bool keepWaiting = true;

	while (this->connectedClients < this->maxAllowedClients) {
		printf("waiting for a connection\n");

		this->acceptClientConnection();	
	}
}

void Server::sendBroadcast(char* message)
{
	for (vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (*it == NULL) continue;

		int bytecount;
		if ((bytecount = send((*it)->getSocket(), message, strlen(message), 0)) == SOCKET_ERROR) {
			fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
			continue;
		}
		printf("Sent bytes %d\n", bytecount);
	}
}

bool Server::validate()
{
	return this->isValid;
}
