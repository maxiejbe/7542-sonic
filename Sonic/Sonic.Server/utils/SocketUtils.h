#ifndef SOCKETUTILS_H
#define SOCKETUTILS_H

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <Ws2tcpip.h>
#include <string>

using namespace std;

class SocketUtils {
public:
	static string getIpFromAddress(sockaddr_in address);
};

#endif

