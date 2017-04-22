#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <Ws2tcpip.h>

class Client {
public:
	Client();

private:
	SOCKET socket;
};

#endif
