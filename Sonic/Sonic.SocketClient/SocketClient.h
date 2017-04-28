#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0) 

class SocketClient
{
public:
	SocketClient(char* host, int port);
	~SocketClient();
	bool isInitialized();
	bool sendMessage(char * message);
private:
	SOCKET socket;
	char* host;
	int port;
	struct addrinfo * addressInfo;
	bool initialized;
	/*** INITIALIZATION ***/

	bool initializeWindowsSupport();
	bool initializeAddressInfo(char* host, int port);
	bool initializeSocket();
	bool connectToSocket();
	
	void freeResources();
};

#endif