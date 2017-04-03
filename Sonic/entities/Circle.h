#ifndef CIRCLE_H
#define CIRCLE_H

#include "Entity.h"
#include "common/Drawable.h"

class Circle : public Entity {
public:
	virtual void draw(SDL_Rect camera);
};

#endif // !CIRCLE_H
