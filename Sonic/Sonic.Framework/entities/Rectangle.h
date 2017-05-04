#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Entity.h"

class Rectangle : public Entity {
public:
	Rectangle() {

	}
	Rectangle(Entity* entity) : Entity(entity) {

	}

	virtual Dimensions getDefaultDimensions() override;
};

#endif // !RECTANGLE_H
