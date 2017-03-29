#ifndef CIRCLE_H
#define CIRCLE_H

#include "Entity.h"

class Circle : public Entity {
public:
	Circle(); //TODO: definir atributos propios
	Circle(int x, int y, int radio);
	void draw(SDL_Rect camera);
};

#endif // !CIRCLE_H
