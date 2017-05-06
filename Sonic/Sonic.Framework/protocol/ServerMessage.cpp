#include "ServerMessage.h"

const char* SERVER_MESSAGE_TYPE_NODE = "t";
const char* SERVER_MESSAGE_PLAYER_NUMBER_NODE = "pn";

ServerMessage::ServerMessage() 
{
	this->playerNumber = -1;
	this->type = typeless;
}

void ServerMessage::setType(ServerMessageType type)
{
	this->type = type;
}

ServerMessageType ServerMessage::getType()
{
	return this->type;
}

void ServerMessage::setPlayerNumber(int playerNumber)
{
	this->playerNumber = playerNumber;
}

int ServerMessage::getPlayerNumber()
{
	return this->playerNumber;
}

void ServerMessage::unserialize(Value * nodeRef)
{
	//type
	parseInt((int*)&type, typeless, nodeRef, SERVER_MESSAGE_TYPE_NODE, Validator::intGreaterThanOrEqualToZero);
	//player number
	parseInt(&playerNumber, -1, nodeRef, SERVER_MESSAGE_PLAYER_NUMBER_NODE, Validator::intGreaterThanOrEqualToZero);
}

char * ServerMessage::getNodeName()
{
	return nullptr;
}

string ServerMessage::serialize()
{
	if (this->type == typeless) {
		return "";
	}

	StringBuffer s;
	Writer<StringBuffer> writer(s);
	//serialize
	writer.StartObject();
	//type
	writer.String(SERVER_MESSAGE_TYPE_NODE);
	writer.Int(this->type);
	//player number
	writer.String(SERVER_MESSAGE_PLAYER_NUMBER_NODE);
	writer.Int(this->playerNumber);
	writer.EndObject();

	return s.GetString();
}

