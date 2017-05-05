#include "Message.h"

Message::Message()
{
}

Message::Message(string message)
{
	this->playerNumber = 0;
	this->position.x = 0;
	this->position.y = 0;
	this->connectionStatus = ConnectionStatus::connected;
	this->playerStatus = PlayerStatus::walking;

	initializeProperties();
	this->fromString(message);
}

Message::Message(int playerNumber)
{
	this->playerNumber = playerNumber;
	this->position.x = 0;
	this->position.y = 0;
	this->connectionStatus = ConnectionStatus::connected;
	this->playerStatus = PlayerStatus::walking;

	initializeProperties();
}

Message::Message(float dt, bool isKPLeft, bool isKPSpace, bool isKPRight, bool isKPUp, bool isKULeft, bool isKURight, bool isKUSpace)
{
	this->playerNumber = 0;
	this->position.x = 0;
	this->position.y = 0;
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



void Message::setPosition(Vector2 position)
{
	this->position = position;
}

Vector2 Message::getPosition()
{
	return this->position;
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

int Message::getNumber()
{
	return this->playerNumber;
}

//http://stackoverflow.com/questions/5888022/split-string-by-single-spaces
void Message::fromString(string message)
{
	vector<string> items;
	StringUtils::split(&items, message, DELIMITER);

	for (size_t i = 0; i < items.size(); i++)
	{
		int value;
		istringstream(items[i]) >> value;
		*((int*)properties[i]) = value;
	}
}

//http://stackoverflow.com/questions/662918/how-do-i-concatenate-multiple-c-strings-on-one-line
void Message::toString(string* message)
{
	std::stringstream ss;

	size_t propertiesSize = properties.size();
	for (size_t i = 0; i < propertiesSize; i++)
	{
		ss << to_string(*((int*)properties[i]));
		if (i == (propertiesSize - 1)) continue;
		ss << DELIMITER;
	}
	*message = ss.str();
}

bool Message::validate()
{
	//if (this->playerNumber < 0) return false;
	return true;
}

void Message::initializeProperties()
{
	properties.push_back(&this->playerNumber);
	properties.push_back(&this->position.x);
	properties.push_back(&this->position.y);
	properties.push_back(&this->connectionStatus);
	properties.push_back(&this->playerStatus);

	properties.push_back(&this->dt);
	properties.push_back(&this->isKPLeft);
	properties.push_back(&this->isKPRight);
	properties.push_back(&this->isKPUp);
	properties.push_back(&this->isKPSpace);
	properties.push_back(&this->isKULeft);
	properties.push_back(&this->isKURight);
	properties.push_back(&this->isKUSpace);
}

string Message::getBinaryData()
{
	return this->binaryMsg;
}
