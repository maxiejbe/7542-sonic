#include "protocol/Message.h"
#include "protocol/SerializableMessage.h"
#include "entities/Server.h"
#include "Parser.h"

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

	Server server(&serverConfig, parser->getFileContent(), &window, &config, &scenario, &camera);
	if (!server.validate()) {
		return 0;
	}
	server.waitForClientConnections();
	
	delete parser;
	return 0;
}

/*
	EJEMPLO SERVER MESSAGE

	Player* player1 = new Player(10, 10, 10, 20);
	Player* player2 = new Player(5, 5, 5, 12);
	vector<Player*> players = vector<Player*>();
	players.push_back(player1);
	players.push_back(player2);

	ServerMessage * message = new ServerMessage();
	message->setType(players_status);
	message->setPlayers(players);

	string serializedMessage = message->serialize();

	ServerMessage * message2 = new ServerMessage();
	message2->fromJson(serializedMessage);

	delete message;
	delete message2;

*/