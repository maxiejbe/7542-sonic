#ifndef MESSAGE_H
#define MESSAGE_H

#include "../utils/StringUtils.h"
#include <typeinfo>

enum ConnectionStatus { connected, disconnected };
enum PlayerStatus { walking, running, jumping };

class Message {
public:
	Message(string);
	Message(int);
	void setPosition(int, int);

	void fromString(string);
	void toString(string*);

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