#include "SocketUtils.h"

string SocketUtils::getIpFromAddress(sockaddr_in address)
{
	char stringIp[sizeof(address)];
	inet_ntop(AF_INET, &(address.sin_addr), stringIp, INET_ADDRSTRLEN);
	return stringIp;
}
