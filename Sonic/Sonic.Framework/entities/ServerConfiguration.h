#ifndef SERVER_CONFIGURATION_H
#define SERVER_CONFIGURATION_H

#include "common/Serializable.h"
#include "common/Validator.h"

class ServerConfiguration: public Serializable {
public:
	ServerConfiguration();
	string getHost();
	int getPortNumber();
	int getMaxAllowedClients();

private:
	string host;
	int portNumber;
	int maxAllowedClients;

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif