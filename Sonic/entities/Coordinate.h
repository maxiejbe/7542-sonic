#ifndef COORDINATE_H
#define COORDINATE_H

#include "common/Serializable.h"

class Coordinate : public Serializable {
public:
	Coordinate();
private:
	int x;
	int y;

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif