#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Entity.h"
#include "common/Drawable.h"

class Rectangle : public Entity, public Drawable {
public:
	//ONLY FOR TESTING, REMOVE WHEN DONE!
	Rectangle(int x, int y, int w, int h); //TODO: definir atributos propios
	Rectangle(Coordinate coordinate, Dimensions dimensions);
	virtual void draw(SDL_Rect camera) override;
};

#endif // !RECTANGLE_H
