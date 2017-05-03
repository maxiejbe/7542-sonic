#include "Message.h"

Message::Message(string message)
{
	initializeProperties();
	this->fromString(message);
}

Message::Message(int playerNumber)
{
	initializeProperties();
	this->playerNumber = playerNumber;
}

void Message::setPosition(int positionX, int positionY)
{
	this->positionX = positionX;
	this->positionY = positionY;
}

int Message::getXPosition()
{
	return this->positionX;
}

int Message::getYPosition()
{
	return this->positionY;
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

	int propertiesSize = properties.size();
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
	this->playerNumber = 0;
	this->positionX = 0;
	this->positionY = 0;
	this->connectionStatus = ConnectionStatus::connected;
	this->playerStatus = PlayerStatus::walking;

	properties.push_back(&this->playerNumber);
	properties.push_back(&this->positionX);
	properties.push_back(&this->positionY);
	properties.push_back(&this->connectionStatus);
	properties.push_back(&this->playerStatus);
}




