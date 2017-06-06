#ifndef CRAB_H
#define CRAB_H

#include "Enemy.h"

const double CRAB_VELOCITY_X = 2;
const double CRAB_VELOCITY_Y = 0;
const double CRAB_POINTS = 100;

class Crab : public Enemy
{
public:
	Crab(int posX, int posY) : Enemy(posX, posY) 
	{
		this->velocity = Vector2(CRAB_VELOCITY_X,CRAB_VELOCITY_Y);
		this->points = CRAB_POINTS;
	}
	~Crab();
};

#endif

