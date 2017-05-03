#ifndef MESSAGE_H
#define MESSAGE_H

#include "../utils/StringUtils.h"
#include <typeinfo>

enum ConnectionStatus { assign, connected, disconnected };
enum PlayerStatus { idle, walking, running, jumping };

class Message {
public:
	Message(string);
	Message(int);

	void setPosition(int, int);
	int getXPosition();
	int getYPosition();

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
	
	int positionX;
	int positionY;

	ConnectionStatus connectionStatus;
	PlayerStatus playerStatus;
};

#endif