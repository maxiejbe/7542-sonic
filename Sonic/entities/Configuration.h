#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "common/Serializable.h"
#include "common/Validator.h"

class Configuration : public Serializable {
public:
	Configuration();
	
	int GetScrollSpeed();
private:
	int scrollSpeed;

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif