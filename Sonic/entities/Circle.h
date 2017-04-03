#ifndef CIRCLE_H
#define CIRCLE_H

#include "Entity.h"
#include "common/Drawable.h"

class Circle : public Entity, public Drawable {
public:
	Circle(); //TODO: definir atributos propios
	Circle(int x, int y, int radio);
	virtual void draw(SDL_Rect camera) override;
};

#endif // !CIRCLE_H
