#ifndef SQUARE_H
#define SQUARE_H

#include "Entity.h"
#include "Rectangle.h"

class Square : public Entity {
public:
	Square();
	Square(int x, int y, int width, LTexture texture); //TODO: definir atributos propios
	void draw(SDL_Rect camera);
};

#endif // !SQUARE_H
