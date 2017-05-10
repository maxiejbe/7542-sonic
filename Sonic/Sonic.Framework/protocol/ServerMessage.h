#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>
#include "SerializableMessage.h"
#include "../entities/common/Validator.h"
#include "../entities/Player.h"
#include "../entities/Camera.h"

enum ServerMessageType {player_assign, content, start_game, players_status, typeless};

//TODO: Apply polimorphism with server message type 
class ServerMessage : public SerializableMessage {
public:
	ServerMessage();
	~ServerMessage();
	void setType(ServerMessageType);
	ServerMessageType getType();
	void setPlayerNumber(int);
	int getPlayerNumber();
	vector<Player*> getPlayers();
	Camera * getCamera();
	void setCamera(Camera * camera);
	void setPlayers(vector<Player*> players);
	void setFileContent(string content);
	string getFileContent();

	void serializePlayers(Writer<StringBuffer>& writer);
	void serializeCamera(Writer<StringBuffer>& writer);
	void parsePlayersStatus(Value *);
	void parseCameraStatus(Value *);
	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	ServerMessageType type;
	vector<Player*> players;
	Camera * camera;
	string fileContent;
	int playerNumber;
	void freePlayers();
};

#endif