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

void Player::setXPosition(float x)
{
	this->position.x = x;
}

void Player::setYPosition(float y)
{
	this->position.y = y;
}

Vector2 Player::getVelocity()
{
	return this->velocity;
}

void Player::setXVelocity(float x)
{
	this->velocity.x = x;
}

void Player::setYVelocity(float y)
{
	this->velocity.y = y;
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

void Player::setFacingDirection(FacingDirection facingDirection)
{
	this->facingDirection = facingDirection;
}

PlayerStatus Player::getSpriteState()
{
	return spriteState;
}

void Player::setSpriteState(PlayerStatus spriteState)
{
	this->spriteState = spriteState;
}

string Player::getFilePath()
{
	return filePath;
}

float Player::getTargetVelX()
{
	return this->targetVelX;
}

void Player::setTargetVelX(float targetVelX)
{
	this->targetVelX = targetVelX;
}

int Player::getScenarioWidth()
{
	return this->scenarioWidth;
}

int Player::getScenarioHeight()
{
	return this->scenarioHeight;
}

void Player::setIsJumping(bool isJumping)
{
	this->isJumping = isJumping;
}

bool Player::getIsJumping()
{
	return this->isJumping;
}

float Player::getGroundPos()
{
	return this->groundPos;
}

int Player::getScrollSpeed()
{
	return this->scrollSpeed;
}

int Player::getNumber()
{
	return this->number;
}

void Player::setNumber(int number)
{
	this->number = number;
}

int Player::getWidth()
{
	return this->width;
}