#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <string>
#include "Logger.h"
#include "entities/Player.h"
#include "protocol/Message.h"

using namespace std;

class PlayerController
{
public:
	PlayerController();
	static void update(Message* message, Player* player);
private:
	static void updateInput(Message* message, Player* player);
	static void move(Player* player, double timeStep);
};

#endif // !PLAYERCONTROLLER_H