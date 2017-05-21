#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <Ws2tcpip.h>
#include "Logger.h"
#pragma comment(lib, "Ws2_32.lib")

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0) 

using namespace std;

class SocketClient
{
public:
	SocketClient(char* host, int port);
	~SocketClient();
	bool isInitialized();
	bool isConnected();
	bool reconnect();
	bool sendMessage(string message);
	bool sendMessage(string message, bool disconnect);
	bool receiveMessage(char * receivedMessage, int receivedMessageLength);
	
	void disconnectSocket();
private:
	SOCKET _socket;
	char* host;
	int port;
	struct addrinfo * addressInfo;
	bool initialized;
	bool connected;

	/*** INITIALIZATION ***/
	bool initializeWindowsSupport();
	bool initializeAddressInfo();
	bool initializeSocket();

	/* SOCKET CONNECTION*/
	void connectToSocket();
	void freeResources();
};

#endif