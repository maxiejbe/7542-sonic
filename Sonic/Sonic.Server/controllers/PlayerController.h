#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <string>
#include "Logger.h"
#include "entities/Player.h"
#include "entities/Message.h"

using namespace std;

class PlayerController
{
public:
	void update(Player* player, float dt);
private:
	void updateInput(Player* player);
	void move(Player* player, float timeStep);
};

#endif // !PLAYERCONTROLLER_H