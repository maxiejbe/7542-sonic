#ifndef COLLISIONABLE_H
#define COLLISIONABLE_H

#include <math.h>

enum CollisionableType { rectangle, circle };

class Collisionable {
public:
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getRadio() = 0;

	virtual int getXPosition() = 0;
	virtual int getYPosition() = 0;

	virtual CollisionableType getCollisionableType() = 0;
	

	bool isCollisioning(Collisionable*);

	bool isCollisioningCircle(Collisionable*);
	bool isCollisioningRectangle(Collisionable*);
};

#endif