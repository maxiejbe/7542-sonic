#pragma once
#include "SocketHandler.h"

class TestSocketHandler : public SocketHandler
{
public:
	TestSocketHandler();
	~TestSocketHandler();
	void onMessage(char* message);
};

