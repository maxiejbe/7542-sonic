#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>
#include "SerializableMessage.h"
#include "../entities/common/Validator.h"
#include "../entities/Camera.h"
#include "../entities/enemies/Enemy.h"

enum ServerMessageType {player_assign, content, start_game, players_status, enemies_status, typeless, heart_beat_server };

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
	vector<Enemy*> getEnemies();
	Camera * getCamera();
	void setCamera(Camera * camera);
	void setPlayers(vector<Player*> players);
	void setEnemies(vector<Enemy*> enemies);
	void setFileContent(string content);
	string getFileContent();

	void serializePlayers(Writer<StringBuffer>& writer);
	//void serializeEnemies(Writer<StringBuffer>& writer);
	void serializeCamera(Writer<StringBuffer>& writer);
	void parsePlayersStatus(Value *);
	//void parseEnemiesStatus(Value *);
	void parseCameraStatus(Value *);
	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	ServerMessageType type;
	vector<Player*> players;
	vector<Enemy*> enemies;
	Camera * camera;
	string fileContent;
	int playerNumber;
};

#endif