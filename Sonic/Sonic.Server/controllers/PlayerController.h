#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <string>
#include "Logger.h"
#include "entities/Player.h"
#include "protocol/Message.h"
#include "entities/Camera.h"

using namespace std;

class PlayerController
{
public:
	PlayerController();
	static void update(Message* message, Player* player, Camera* camera, int milliseconds);
private:
	static void updateInput(Message* message, Player* player);
	static void move(Player* player, double timeStep, Camera* camera);
};

#endif // !PLAYERCONTROLLER_H