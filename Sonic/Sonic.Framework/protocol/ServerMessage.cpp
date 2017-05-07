#include "ServerMessage.h"

const char* SERVER_MESSAGE_TYPE_NODE = "t";
const char* SERVER_MESSAGE_PLAYER_NUMBER_NODE = "pn";
const char* SERVER_MESSAGE_PLAYERS_STATUS_NODE = "ps";

ServerMessage::ServerMessage() 
{
	this->playerNumber = -1;
	this->type = typeless;
	this->players = vector<Player*>();
}

ServerMessage::~ServerMessage() 
{
	freePlayers();
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


vector<Player*> ServerMessage::getPlayers()
{
	return this->players;
}

void ServerMessage::setPlayers(vector<Player*> players)
{
	this->players = players;
}


void ServerMessage::unserialize(Value * nodeRef)
{
	//type
	parseInt((int*)&type, typeless, nodeRef, SERVER_MESSAGE_TYPE_NODE, Validator::intGreaterThanOrEqualToZero);
	switch (this->type)
	{
	case player_assign:
		//player number
		parseInt(&playerNumber, -1, nodeRef, SERVER_MESSAGE_PLAYER_NUMBER_NODE, Validator::intGreaterThanOrEqualToZero);
		break;
	case players_status:
		parsePlayersStatus(nodeRef);
		break;
	default:
		break;
	}
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
	switch (this->type)
	{
	case player_assign:
		writer.String(SERVER_MESSAGE_PLAYER_NUMBER_NODE);
		writer.Int(this->playerNumber);
		break;
	case players_status:
		this->serializePlayers(writer);
	default:
		break;
	}

	writer.EndObject();

	return s.GetString();
}

void ServerMessage::serializePlayers(Writer<StringBuffer>& writer)
{
	writer.String(SERVER_MESSAGE_PLAYERS_STATUS_NODE);
	writer.StartArray();

	vector<Player*>::iterator it = this->players.begin();
	while (it != this->players.end()) {
		if (*it == NULL) continue;
		string serializedplayer = (*it)->serialize();
		writer.String(serializedplayer.c_str());
		it++;
	}
	writer.EndArray();
}

void ServerMessage::parsePlayersStatus(Value * nodeRef)
{
	//free players and clear vector
	freePlayers();
	Value& node = *nodeRef;
	
	//LOG(logINFO) << MESSAGE_PARSING_NODE_FIELD + string(fieldName);

	if (nodeRef == nullptr || !node.HasMember(SERVER_MESSAGE_PLAYERS_STATUS_NODE)) {
		LOG(logWARNING) << "Server Message: Fallo parseo de jugadores";
		return;
	}

	//string childNodeValue = getNodeContent(&node[SERVER_MESSAGE_PLAYERS_STATUS_NODE]);
	const Value& playersStatus = node[SERVER_MESSAGE_PLAYERS_STATUS_NODE];
	if (!playersStatus.IsArray()) {
		LOG(logWARNING) << "Server Message: Campo incorrecto de jugadores " << SERVER_MESSAGE_PLAYERS_STATUS_NODE;
		return;
	}

	//unserialize players
	Document jsonPlayer;
	for (Value::ConstValueIterator itr = playersStatus.Begin(); itr != playersStatus.End(); ++itr) {
		if (jsonPlayer.Parse((*itr).GetString()).HasParseError()) {
			//LOG
			continue;
		}

		//unsearialize player and add to vector
		Player * newPlayer = new Player();
		newPlayer->unserialize(&jsonPlayer);
		this->players.push_back(newPlayer);
	}
}

void ServerMessage::freePlayers()
{
	if (this->players.empty()) {
		return;
	}

	vector<Player*>::iterator it = this->players.begin();
	while(it != this->players.end())
	{
		Player * currentPlayer = (*it);
		if (currentPlayer == nullptr) continue;
		delete(currentPlayer);
		it++;
	}

	this->players.clear();
}

