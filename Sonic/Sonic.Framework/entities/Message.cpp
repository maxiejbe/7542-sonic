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

	for (size_t i = 0; i < properties.size(); i++)
	{
		ss << to_string(*((int*)properties[i])) << "|";
	}
	*message = ss.str();
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




