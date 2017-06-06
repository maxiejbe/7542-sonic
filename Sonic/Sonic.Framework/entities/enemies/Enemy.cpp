#include "Enemy.h"

const int ENEMY_DEFAULT_WIDTH = 20;
const int ENEMY_DEFAULT_HEIGHT = 20;
const int ENEMY_DEFAULT_POINTS = 10;

Enemy::Enemy(double posX, double posY)
{
	this->position = Vector2(posX, posY);
	this->velocity = Vector2(0, 0);
	this->height = ENEMY_DEFAULT_HEIGHT;
	this->width = ENEMY_DEFAULT_WIDTH;
	this->points = ENEMY_DEFAULT_POINTS;
	this->alive = true;
}


Enemy::~Enemy()
{
}

Vector2 Enemy::getPosition()
{
	return this->position;
}

Vector2 Enemy::getVelocity()
{
	return this->velocity;
}

void Enemy::setPositionX(double posX)
{
	this->position.x = posX;
}

void Enemy::setPositionY(double posY)
{
	this->position.y = posY;
}

int Enemy::getHeight()
{
	return this->height;
}

int Enemy::getWidth()
{
	return this->width;
}

bool Enemy::isAlive()
{
	return this->alive;
}

void Enemy::kill()
{
	this->alive = false;
}

int Enemy::getPoints()
{
	return this->points;
}
