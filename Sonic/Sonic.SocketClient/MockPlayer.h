#pragma once
#include "entities/Message.h"
#include "Vector2.h"
class MockPlayer
{
public:
	MockPlayer(int number, Vector2 position, PlayerStatus playerStatus);
	~MockPlayer();
	void setNumber(int);
	int getNumber();
	void setPosition(Vector2 position);
	Vector2 getPosition();
	void setPlayerStatus(PlayerStatus);
	PlayerStatus getPlayerStatus();

private:
	int number;
	Vector2 position;
	PlayerStatus playerStatus;
};

