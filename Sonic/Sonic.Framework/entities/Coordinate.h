#ifndef COORDINATE_H
#define COORDINATE_H

#include "common/Serializable.h"
#include "common/Validator.h"

class Coordinate : public Serializable {
public:
	Coordinate();
	Coordinate(double, double);
	double getX();
	double getY();

	void serialize(Writer<StringBuffer>&writer);
	// Inherited via Serializable
	virtual string serialize() override;
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
private:
	double x;
	double y;
};

#endif