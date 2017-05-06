#include "Message.h"

Message::Message()
{
}

Message::Message(float dt, bool isKPLeft, bool isKPSpace, bool isKPRight, bool isKPUp, bool isKULeft, bool isKURight, bool isKUSpace)
{
	this->playerNumber = 0;
	this->connectionStatus = ConnectionStatus::connected;
	this->playerStatus = PlayerStatus::walking;
	this->dt = dt;
	this->isKPLeft = isKPLeft;
	this->isKPSpace = isKPSpace;
	this->isKPRight = isKPRight;
	this->isKPUp = isKPUp;
	this->isKULeft = isKULeft;
	this->isKURight = isKURight;
	this->isKUSpace = isKUSpace;
}

void Message::setConnectionStatus(ConnectionStatus connectionStatus)
{
	this->connectionStatus = connectionStatus;
}

ConnectionStatus Message::getConnectionStatus()
{
	return this->connectionStatus;
}

void Message::setPlayerNumber(int number)
{
	this->playerNumber = number;
}

int Message::getPlayerNumber()
{
	return this->playerNumber;
}

bool Message::validate()
{
	//if (this->playerNumber < 0) return false;
	return true;
}

string Message::getBinaryData()
{
	return this->binaryMsg;
}

void Message::unserialize(Value * nodeRef)
{
	return;
}

char * Message::getNodeName()
{
	return nullptr;
}
