#ifndef COORDINATE_H
#define COORDINATE_H

#include "common/Serializable.h"
#include "common/Validator.h"

class Coordinate : public Serializable {
public:
	Coordinate();
	Coordinate(int, int);
	int getX();
	int getY();

	// Inherited via Serializable
	virtual string serialize() override;
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
private:
	int x;
	int y;
};

#endif