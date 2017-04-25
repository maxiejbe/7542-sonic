#include "entities/Server.h"
#include "Parser.h"
#include "entities\common\ServerConfiguration.h"

int main(int argc, char* args[])
{
	Logger::init();
	Logger::loggingLevel() = logHIGH;

	string configParamName = "--config";
	string configPath = "";

	//Take config file from param
	if (argc > 2) {
		string arg = args[1];
		if (arg == configParamName) {
			configPath = args[2];
		}
	}

	Parser* parser = new Parser(configPath);
	ServerConfiguration config;
	parser->parse(&config);

	cout << "Trying to start server" << endl;
	Server server(config.getPortNumber(), config.getMaxAllowedClients());
	if (!server.validate()) {
		//TODO: Move to log
		cout << "Could not start server" << endl;
		return 0;
	}
	server.waitForClientConnections();
	
	getchar();
	return 0;
}

