#include "protocol/Message.h"
#include "entities/Server.h"
#include "Parser.h"

int main(int argc, char* args[])
{
	Logger::init();
	Logger::loggingLevel() = logLOW;

	string configParamName = "--config";
	string configPath = "";

	//Take config file from param
	if (argc > 2) {
		string arg = args[1];
		if (arg == configParamName) {
			configPath = args[2];
		}
	}

	Parser* parser = new Parser(configPath, "");
	ServerConfiguration serverConfig;
	Window window;
	Configuration config;
	Scenario scenario;

	parser->parse(&serverConfig);
	parser->parse(&window);
	parser->parse(&config);
	parser->parse(&scenario);

	Server server(&serverConfig, parser->getFileContent(), &window, &config, &scenario);
	if (!server.validate()) {
		return 0;
	}
	server.waitForClientConnections();
	
	delete parser;
	return 0;
}

