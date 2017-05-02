#pragma once
#include "SocketClient.h";
class MultiplayerManager
{
public:
	MultiplayerManager();
	~MultiplayerManager();
private:
	SocketClient* socketClient;
};

