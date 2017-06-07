#ifndef ENTITY_LIMIT_H
#define ENTITY_LIMIT_H

#include "common/Serializable.h"
#include "common/Validator.h"

using namespace std;

class EntityLimit : public Serializable {
public:
	EntityLimit();

private:
	int minCount;
	int maxCount;

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif