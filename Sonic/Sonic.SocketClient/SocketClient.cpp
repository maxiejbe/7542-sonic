#include "SocketClient.h"
using namespace std;

SocketClient::SocketClient(char * host, int port)
{
	this->host = host;
	this->port = port;
	this->addressInfo = NULL;
	this->socket = INVALID_SOCKET;
	this->initialized = true;

	if (!this->initializeWindowsSupport()) { return; }
	if (!this->initializeAddressInfo(host,port)) { return; }
	if (!this->initializeSocket()) { return; }
	if (!this->connectToSocket()) { return; }

	this->initialized = true;
}

SocketClient::~SocketClient()
{
	this->freeResources();
}

bool SocketClient::isInitialized()
{
	return this->initialized;
}

bool SocketClient::sendMessage(char * message)
{	
	char buffer[1024];
	int bufferSize = 1024;
	int byteCount;
	if (byteCount = send(this->socket, message, strlen(message), 0) == SOCKET_ERROR) {
		//TODO: Log in file
		this->freeResources();
		fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
		return false;
	}

	if (byteCount = recv(this->socket, buffer, bufferSize, 0) == SOCKET_ERROR) {
		this->freeResources();
		fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
		return false;
	}

	printf("Received: (%d) %s", byteCount, buffer);
	return true;
}

bool SocketClient::initializeWindowsSupport()
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

bool SocketClient::initializeAddressInfo(char * host, int port)
{
	struct addrinfo * addrInfoResult = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	char portString[33];
	_itoa(port, portString, 10);

	int err = getaddrinfo(host, portString, &hints, &addrInfoResult);
	if (err != 0) {
		//TODO: Log in file
		this->freeResources();
		return false;
	}

	this->addressInfo = addrInfoResult;
	return true;
}

bool SocketClient::initializeSocket()
{
	this->socket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if (this->socket == INVALID_SOCKET) {
		//TODO: Log in file
		this->freeResources();
		return false;
	}
	
	return true;
}

bool SocketClient::connectToSocket()
{
	if (connect(socket, addressInfo->ai_addr, (int)addressInfo->ai_addrlen) == SOCKET_ERROR) {
		//TODO: Log in file
		this->freeResources();
		return false;
	}

	return true;
}

void SocketClient::freeResources() 
{
	if (this->addressInfo) { freeaddrinfo(this->addressInfo); }
	if(this->socket) 
	{ 
		closesocket(this->socket); 
		this->socket = INVALID_SOCKET;
	}

	WSACleanup();
}
