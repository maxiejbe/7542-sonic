#include "entities/Server.h"

#include "entities/Server.h"

int main(int argc, char* argv[])
{
	//TODO: Read from file
	int portNumber = 65535;
	int maxAllowedClients = 10;

	cout << "Trying to start server" << endl;
	Server server(portNumber, maxAllowedClients);
	if (!server.validate()) {
		//TODO: Move to log
		cout << "Could not start server" << endl;
		return 0;
	}
	server.waitForClientConnections();
	return 0;
}

