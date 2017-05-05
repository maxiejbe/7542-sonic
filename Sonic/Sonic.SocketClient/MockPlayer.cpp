#include "MockPlayer.h"

MockPlayer::MockPlayer(int number, Vector2 position, PlayerStatus playerStatus)
{
	this->number = number;
	this->position = position;
	this->playerStatus = playerStatus;
}

MockPlayer::~MockPlayer()
{
}

void MockPlayer::setNumber(int number)
{
	this->number = number;
}

int MockPlayer::getNumber()
{
	return this->number;
}

void MockPlayer::setPosition(Vector2 position)
{
	this->position = position;
}

Vector2 MockPlayer::getPosition()
{
	return this->position;
}

void MockPlayer::setPlayerStatus(PlayerStatus pStatus)
{
	this->playerStatus = pStatus;
}

PlayerStatus MockPlayer::getPlayerStatus()
{
	return this->playerStatus;
}
