#ifndef SERVER_CONFIGURATION_H
#define SERVER_CONFIGURATION_H

#include "entities/common/Serializable.h"
#include "entities/common/Validator.h"

class ServerConfiguration: public Serializable {
public:
	ServerConfiguration();
	int getPortNumber();
	int getMaxAllowedClients();

private:
	int portNumber;
	int maxAllowedClients;

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif