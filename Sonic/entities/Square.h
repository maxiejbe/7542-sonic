#ifndef SQUARE_H
#define SQUARE_H

#include "Entity.h"
#include "Rectangle.h"
#include "common/Drawable.h"

class Square : public Entity {
public:
	Square(Entity* entity) : Entity(entity) {

	}
	virtual void draw(SDL_Rect camera) override;
};

#endif // !SQUARE_H
