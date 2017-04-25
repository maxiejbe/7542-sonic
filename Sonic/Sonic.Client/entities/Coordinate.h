#ifndef COORDINATE_H
#define COORDINATE_H

#include "entities/Serializable.h"
#include "common/Validator.h"

class Coordinate : public Serializable {
public:
	Coordinate();
	int getX();
	int getY();
private:
	int x;
	int y;

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif