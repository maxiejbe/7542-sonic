#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Entity.h"
#include "../Renderer.h"

class Rectangle : public Entity {
private:
	SDL_Rect getRenderRectangle(SDL_Rect camera);
public:
	//ONLY FOR TESTING, REMOVE WHEN DONE!
	Rectangle(int x, int y, int w, int h); //TODO: definir atributos propios
	void draw(SDL_Rect camera);
};

#endif // !RECTANGLE_H
