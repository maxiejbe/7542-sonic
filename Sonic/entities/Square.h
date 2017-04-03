#ifndef SQUARE_H
#define SQUARE_H

#include "Entity.h"
#include "Rectangle.h"
#include "common/Drawable.h"

class Square : public Entity, public Drawable {
public:
	Square();
	Square(int x, int y, int width); //TODO: definir atributos propios
	virtual void draw(SDL_Rect camera) override;
};

#endif // !SQUARE_H
