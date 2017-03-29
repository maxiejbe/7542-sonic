#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Entity.h"

class Rectangle : public Entity {
public:
	//ONLY FOR TESTING, REMOVE WHEN DONE!
	Rectangle(int x, int y, int w, int h); //TODO: definir atributos propios
	Rectangle(Coordinate coordinate, Dimensions dimensions);
	void draw(SDL_Rect camera);
};

#endif // !RECTANGLE_H
