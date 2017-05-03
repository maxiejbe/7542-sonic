#pragma once
#include "entities\Message.h"
class MockPlayer
{
public:
	MockPlayer(int, int, int, PlayerStatus);
	~MockPlayer();
	void setNumber(int);
	int getNumber();
	void setPosX(int);
	int getPosX();
	void setPosY(int);
	int getPosY();
	void setPlayerStatus(PlayerStatus);
	PlayerStatus getPlayerStatus();

private:
	int number;
	int posX;
	int posY;
	PlayerStatus playerStatus;
};

