#include "Rectangle2.h"

Rectangle2::Rectangle2(double x0, double x1, double y0, double y1)
{
	this->x0 = x0;
	this->x1 = x1;
	this->y0 = y0;
	this->y1 = y1;
}

bool Rectangle2::collisionsWith(double x0, double x1, double y0, double y1)
{
	if (x0 <= this->x1 && x1 >= this->x0 && y0 <= this->y1 && y1 >= this->y0) return true;
	return false;

	//bool c = true;
	//if (x0 > this->x1) c = false;
	//if (x1 < this->x0) c = false;
	//if (y0 > this->y1) c = false;
	//if (y1 < this->y0) c = false;
	//return c;
}

bool Rectangle2::collisionsWithX(double x0, double x1)
{
	bool c = true;
	if (x0 > this->x1) c = false;
	if (x1 < this->x0) c = false;
	return c;
}

bool Rectangle2::collisionsWithY(double y0, double y1)
{
	bool c = true;
	if (y0 > this->y1) c = false;
	if (y1 < this->y0) c = false;
	return c;
}
