#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Entity.h"

class Rectangle : public Entity {
public:
	Rectangle(int id, string type, string color, Dimensions dimensions, Coordinate coordinate, string imagePath, int zIndex);
	virtual void draw(SDL_Rect camera) override;
};

#endif // !RECTANGLE_H
