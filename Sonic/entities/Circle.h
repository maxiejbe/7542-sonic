#ifndef CIRCLE_H
#define CIRCLE_H

#include "Entity.h"
#include "common/Drawable.h"

class Circle : public Entity {
public:
	Circle(int id, string type, string color, Dimensions dimensions, Coordinate coordinate, string imagePath, int zIndex);
	virtual void draw(SDL_Rect camera);
};

#endif // !CIRCLE_H
