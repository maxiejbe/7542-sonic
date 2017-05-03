#include "MockPlayer.h"


MockPlayer::MockPlayer(int number, int posX, int posY, PlayerStatus playerStatus)
{
	this->number = number;
	this->posX = posX;
	this->posY = posY;
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

void MockPlayer::setPosX(int posX)
{
	this->posX = posX;
}

int MockPlayer::getPosX()
{
	return this->posX;
}

void MockPlayer::setPosY(int posY)
{
	this->posY = posY;
}

int MockPlayer::getPosY()
{
	return this->posY;
}

void MockPlayer::setPlayerStatus(PlayerStatus pStatus)
{
	this->playerStatus = pStatus;
}

PlayerStatus MockPlayer::getPlayerStatus()
{
	return this->playerStatus;
}
