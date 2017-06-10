#ifndef ENTITY_LIMIT_H
#define ENTITY_LIMIT_H

#include "common/Serializable.h"
#include "common/Validator.h"

using namespace std;

class EntityLimit : public Serializable {
public:
	EntityLimit();

private:
	string type;
	int minCount;
	int maxCount;

	int minX;
	int maxX;
	int minY;
	int maxY;


	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif