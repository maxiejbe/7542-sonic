#ifndef SQUARE_H
#define SQUARE_H

#include "Entity.h"
#include "Rectangle.h"

class Square : public Entity {
private:
	Rectangle rectangle;
public:
	Square();
	Square(Entity* entity) : Entity(entity) {
		rectangle = Rectangle(entity);
	}
	
	virtual Dimensions getDefaultDimensions() override;
};

#endif // !SQUARE_H
