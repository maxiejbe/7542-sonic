#include "protocol/Message.h"
#include "protocol/SerializableMessage.h"
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
	Camera camera;

	parser->parse(&serverConfig);
	parser->parse(&window);
	parser->parse(&config);
	parser->parse(&scenario);

	camera = Camera(0, 0, window.getWidth(), window.getHeight(), window.getWidth(), window.getHeight(), scenario.getWidth(), scenario.getHeight());

	//only for testing
	vector<Enemy*> enemies = vector<Enemy*>();
	enemies.push_back(new Enemy(10, 10, 20, 20, crab));

	Server server(&serverConfig, parser->getFileContent(), &window, &config, &scenario, &camera, enemies);
	if (!server.validate()) {
		return 0;
	}
	server.waitForClientConnections();

	delete parser;
	return 0;
}