#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "common/Serializable.h"

class Configuration : public Serializable {
public:
	Configuration();
	
	int GetScrollSpeed();
	string GetLogLevel();
private:
	int scrollSpeed;
	string logLevel;

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif