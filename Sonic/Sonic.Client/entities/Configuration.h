#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "entities/Serializable.h"
#include "common/Validator.h"

class Configuration : public Serializable {
public:
	Configuration();
	
	int getScrollSpeed();
private:
	int scrollSpeed;

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif