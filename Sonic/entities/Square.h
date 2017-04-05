#ifndef SQUARE_H
#define SQUARE_H

#include "Entity.h"
#include "Rectangle.h"
#include "common/Drawable.h"

class Square : public Entity {
private:
	Rectangle rectangle;
public:
	Square();
	Square(Entity* entity) : Entity(entity) {
		rectangle = Rectangle(entity);
	}
	virtual void draw(SDL_Rect camera) override;

	virtual Dimensions GetDefaultDimensions() override;
};

#endif // !SQUARE_H
