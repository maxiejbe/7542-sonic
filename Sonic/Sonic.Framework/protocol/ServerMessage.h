#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>
#include "SerializableMessage.h"
#include "../entities/common/Validator.h"

enum ServerMessageType {player_assign, content, start_game, players_status, typeless};

class ServerMessage : public SerializableMessage {
public:
	ServerMessage();
	void setType(ServerMessageType);
	ServerMessageType getType();
	void setPlayerNumber(int);
	int getPlayerNumber();

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	ServerMessageType type;
	int playerNumber;
};

#endif