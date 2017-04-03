#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Entity.h"

class Rectangle : public Entity {
public:
	virtual void draw(SDL_Rect camera) override;
};

#endif // !RECTANGLE_H
