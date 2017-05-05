#ifndef MESSAGE_H
#define MESSAGE_H

#include "../utils/StringUtils.h"
#include "../Vector2.h"
#include <typeinfo>

enum ConnectionStatus { assign, connected, disconnected };
enum PlayerStatus { idle, walking, running, jumping };

class Message {
public:
	Message(string);
	Message(int);
	Message::Message(float dt, bool isKPLeft, bool isKPSpace, bool isKPRight, bool isKPUp, bool isKULeft, bool isKURight, bool isKUSpace);

	void setPosition(Vector2 position);
	Vector2 getPosition();

	void setConnectionStatus(ConnectionStatus);
	ConnectionStatus getConnectionStatus();

	void setPlayerNumber(int);
	int getNumber();

	void fromString(string);
	void toString(string*);

	bool validate();

	void initializeProperties();
private:
	const string DELIMITER = "|";
	vector<void*> properties;
	int playerNumber;
	Vector2 position;
	ConnectionStatus connectionStatus;
	PlayerStatus playerStatus;

	float dt;
	bool isKPLeft, isKPRight, isKPUp, isKPSpace, isKULeft, isKURight, isKUSpace;
};

#endif