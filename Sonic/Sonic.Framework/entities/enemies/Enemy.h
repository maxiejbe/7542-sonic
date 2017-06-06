#ifndef PLAYER_H
#define PLAYER_H

#include "../../Vector2.h"

class Enemy
{
public:
	Enemy(double, double);
	~Enemy();

	Vector2 getPosition();
	Vector2 getVelocity();
	void setPositionX(double);
	void setPositionY(double);
	int getHeight();
	int getWidth();
	bool isAlive();
	void kill();
	int getPoints();

protected:
	Vector2 position;
	Vector2 velocity;
	int width;
	int height;
	bool alive;
	int points;
};

#endif

