#include "Collisionable.h"

bool Collisionable::isCollisioning(Collisionable * otherCollisionable)
{
	if (otherCollisionable->getCollisionableType() == CollisionableType::circle) return isCollisioningCircle(otherCollisionable);
	return isCollisioningRectangle(otherCollisionable);
}

bool Collisionable::isCollisioningRectangle(Collisionable * otherCollisionable)
{
	bool collision = true;

	int borderLeft = getXPosition();
	int borderRight = getXPosition() + getWidth();
	int borderTop = getYPosition();
	int borderBotton = getYPosition() + getHeight();

	int otherBorderLeft = otherCollisionable->getXPosition();
	int otherBorderRight = otherCollisionable->getXPosition() + otherCollisionable->getWidth();
	int otherBorderTop = otherCollisionable->getYPosition();
	int otherBorderBotton = otherCollisionable->getYPosition() + otherCollisionable->getHeight();

	//RECTANGLE COLLISION							
	if (borderLeft >= otherBorderRight)
	{
		collision = false;
	}
	
	if (borderRight <= otherBorderLeft)
	{
		collision = false;
	}
	
	if (borderTop >= otherBorderBotton)
	{
		collision = false;
	}
	
	if (borderBotton <= otherBorderTop)
	{
		collision = false;
	}
	
	return collision;
}

bool Collisionable::isCollisioningCircle(Collisionable * otherCollisionable)
{
	bool collision = true;

	int borderLeft = getXPosition();
	int borderRight = getXPosition() + getWidth();
	int borderTop = getYPosition();
	int borderBotton = getYPosition() + getHeight();

	//CIRCULAR COLLISSION						
	//Closest point on collision box
	int cX, cY;

	int circleX = otherCollisionable->getXPosition();
	int circleY = otherCollisionable->getYPosition();
	int circleR = otherCollisionable->getRadio();

	//Find closest X offset
	if (circleX < borderLeft)
	{
		cX = borderLeft;
	}
	else if (circleX > borderLeft + getWidth())
	{
		cX = borderLeft + getWidth();
	}
	else
	{
		cX = circleX;
	}

	//Find closest Y offset
	if (circleY < borderTop)
	{
		cY = borderTop;
	}
	else if (circleY > borderTop + getHeight())
	{
		cY = borderTop + getHeight();
	}
	else
	{
		cY = circleY;
	}

	//If the closest point is inside the circle
	float distanceSquared = sqrt(circleX*circleX + circleY*circleY + cX*cX + cY*cY);
	int circleDiameter = circleR * circleR;
	if (!distanceSquared > circleDiameter)
	{
		//This box and the circle have not collided
		collision = false;
	}

	return collision;
}
