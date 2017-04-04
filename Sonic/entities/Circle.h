#ifndef CIRCLE_H
#define CIRCLE_H

#include "Entity.h"
#include "common/Drawable.h"

class Circle : public Entity {
public:
	Circle(Entity* entity) : Entity(entity) {

	}
	virtual void draw(SDL_Rect camera) override;
};

#endif // !CIRCLE_H
