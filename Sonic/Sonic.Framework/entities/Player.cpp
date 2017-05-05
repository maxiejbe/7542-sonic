#include "Player.h"

Player::Player(string filePath, float x, float y, float velX, float velY, int scenW, int scenH, int scrollSpeed)
{
	this->position = Vector2(x, y);
	this->velocity = Vector2(velX, velY);
	this->scenarioWidth = scenW;
	this->scenarioHeight = scenH;
	this->scrollSpeed = scrollSpeed;
	this->groundPos = y;
	this->isJumping = false;
	this->facingDirection = FACING_RIGHT;
	this->spriteState = PlayerStatus::idle;
	this->filePath = filePath;
}

Vector2 Player::getPosition()
{
	return this->position;
}

Vector2 Player::getVelocity()
{
	return this->velocity;
}

void Player::setWidth(int w)
{
	this->width = w;
}

void Player::setHeight(int h)
{
	this->height = h;
}

FacingDirection Player::getFacingDirection()
{
	return facingDirection;
}

PlayerStatus Player::getSpriteState()
{
	return spriteState;
}

string Player::getFilePath()
{
	return filePath;
}

int Player::getNumber()
{
	return this->number;
}

void Player::setNumber(int number)
{
	this->number = number;
}