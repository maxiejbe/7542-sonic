#pragma once
#include <string>

using namespace std;
class SocketHandler
{
public:
	SocketHandler();
	~SocketHandler();
	virtual void onMessage(char* message) = 0;
	//virtual void onError();
};

