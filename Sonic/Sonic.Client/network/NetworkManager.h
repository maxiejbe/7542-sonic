#pragma once
#include "SocketClient.h"
#include "entities\Message.h"
#include "Logger.h"

class NetworkManager
{
public:
	~NetworkManager();
	static NetworkManager& getInstance() {
		static NetworkManager instance;
		return instance;
	}
	void close();

	bool startClient(char * host, int port);
	bool online();
	bool sendMessage(Message * message);

private:
	NetworkManager();
	static NetworkManager * instance;

	SocketClient * client;

};

