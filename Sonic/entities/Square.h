#ifndef SQUARE_H
#define SQUARE_H

#include "Entity.h"
#include "Rectangle.h"
#include "common/Drawable.h"

class Square : public Entity {
public:
	Square(int id, string type, string color, Dimensions dimensions, Coordinate coordinate, string imagePath, int zIndex);
	virtual void draw(SDL_Rect camera);
};

#endif // !SQUARE_H
