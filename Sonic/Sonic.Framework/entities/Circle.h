#ifndef CIRCLE_H
#define CIRCLE_H

#include "Entity.h"
#include <exception>

class Circle : public Entity {
private:
public:
	Circle() {

	}
	Circle(Entity* entity) : Entity(entity) {

	}
	
	virtual Dimensions getDefaultDimensions() override;
};

#endif // !CIRCLE_H
