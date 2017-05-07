#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>
#include "SerializableMessage.h"
#include "../entities/common/Validator.h"
#include "../entities/Player.h"

enum ServerMessageType {player_assign, content, start_game, players_status, typeless};

class ServerMessage : public SerializableMessage {
public:
	ServerMessage();
	~ServerMessage();
	void setType(ServerMessageType);
	ServerMessageType getType();
	void setPlayerNumber(int);
	int getPlayerNumber();
	vector<Player*> getPlayers();
	void setPlayers(vector<Player*> players);

	void serializePlayers(Writer<StringBuffer>& writer);
	void parsePlayersStatus(Value *);
	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	ServerMessageType type;
	vector<Player*> players;
	int playerNumber;
	void freePlayers();
};

#endif