#include "SocketClient.h"


SocketClient::SocketClient(char * host, int port)
{
	this->host = host;
	this->port = port;

	this->addressInfo = NULL;
	this->_socket = INVALID_SOCKET;
	this->initialized = false;

	if (!this->initializeWindowsSupport()) { return; }
	if (!this->initializeAddressInfo()) { return; }
	if (!this->initializeSocket()) { return; }

	this->initialized = true;

	//perform socket connection
	this->connectToSocket();
}


SocketClient::~SocketClient()
{
	this->disconnectSocket();
	this->freeResources();
}

bool SocketClient::isInitialized()
{
	return this->initialized;
}

bool SocketClient::isConnected()
{
	return this->connected;
}


bool SocketClient::sendMessage(string message)
{
	if (!this->initialized || !this->connected) {
		return false;
	}

	int byteCount = send(this->_socket, message.c_str(), message.size(), 0);
	if (byteCount == SOCKET_ERROR) {
		//TODO: Log in file
		//fprintf(stderr, "Error sending data %d\n", WSAGetLastError());
		this->disconnectSocket();
		return false;
	}

	/*if (byteCount == 0) {
		this->disconnectSocket();
	}*/

	return true;
}

bool SocketClient::receiveMessage(char * receivedMessage, int receivedMessageLength) {
	if (!this->initialized || !this->connected) {
		return false;
	}

	memset(receivedMessage, 0, receivedMessageLength);
	int bytecount = recv(this->_socket, receivedMessage, receivedMessageLength, 0);
	if (bytecount == SOCKET_ERROR) {
		//TODO: Log in file
		//fprintf(stderr, "Error receiving data %d\n", WSAGetLastError());
		this->disconnectSocket();
		return false;
	}
	/*if (bytecount == 0) {
		this->disconnectSocket();
		return false;
	}*/

	return true;
}

bool SocketClient::checkConnection() 
{
	if (!this->initialized || !this->connected) return false;

	fd_set fd_reader;
	timeval connection_timer;

	connection_timer.tv_sec = 2; // = 2
	connection_timer.tv_usec = 0;

	FD_ZERO(&fd_reader);
	FD_SET(this->_socket, &fd_reader);

	int select_ready = select(0, &fd_reader, NULL, NULL, &connection_timer);

	return(select_ready != SOCKET_ERROR);
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

bool SocketClient::initializeAddressInfo()
{
	struct addrinfo * addrInfoResult = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	char portString[33];
	_itoa_s(this->port, portString, 10);

	int err = getaddrinfo(this->host, portString, &hints, &addrInfoResult);
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
	this->_socket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if (this->_socket == INVALID_SOCKET) {
		//TODO: Log in file
		this->freeResources();
		return false;
	}

	return true;
}

void SocketClient::connectToSocket()
{
	this->connected = (connect(_socket, addressInfo->ai_addr, (int)addressInfo->ai_addrlen) != SOCKET_ERROR);
	//failed to connect to socket
	if (!this->connected) {
		LOG(logERROR) << "Socker client: no se puede conectar. Err: " << WSAGetLastError();
	}
}

bool SocketClient::reconnect()
{
	if (!this->initialized) {
		//TODO: Log in file
		return false;
	}

	if (this->connected) return true;

	//initialize socket again
	if(!this->initializeSocket()) return false;
	this->connectToSocket();
	return this->connected;
}


void SocketClient::disconnectSocket()
{
	this->connected = false;
	if (this->_socket != INVALID_SOCKET) {
		closesocket(this->_socket);
		this->_socket = INVALID_SOCKET;
	}
}

void SocketClient::freeResources()
{
	this->initialized = false;
	if (this->addressInfo) { freeaddrinfo(this->addressInfo); }
	WSACleanup();
}
