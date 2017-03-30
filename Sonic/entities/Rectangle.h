#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Entity.h"

class Rectangle : public Entity {
public:
	//ONLY FOR TESTING, REMOVE WHEN DONE!
	Rectangle(int x, int y, int w, int h, LTexture texture); //TODO: definir atributos propios
	Rectangle(Coordinate coordinate, Dimensions dimensions, LTexture texture);
	void draw(SDL_Rect camera);
};

#endif // !RECTANGLE_H
