#ifndef SQUARE_H
#define SQUARE_H

#include "Entity.h"

class Square : public Entity {
public:
	Square();
	Square(Entity* entity) : Entity(entity) {
	}
	
	virtual Dimensions getDefaultDimensions() override;
};

#endif // !SQUARE_H
