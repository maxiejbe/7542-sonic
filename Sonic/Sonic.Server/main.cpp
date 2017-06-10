#include "protocol/Message.h"
#include "protocol/SerializableMessage.h"
#include "entities/Server.h"
#include "entities/GameConfig.h"
#include "Parser.h"

int getRandomBetween(int min, int max) {
	return min + (rand() % static_cast<int>(max - min + 1));
}

vector<Entity*> generateLevelEntities(Level level) {
	vector<Entity*> levelEntities;
	levelEntities.clear();
	vector<EntityLimit> limits = level.getLimits();
	for (vector<EntityLimit>::iterator elit = limits.begin(); elit != limits.end(); ++elit) {
		//Random entities count
		int entitiesCount = getRandomBetween(elit->getMinCount(), elit->getMaxCount());
			
		for (size_t i = 0; i < entitiesCount; i++)
		{
			Entity* entity = EntityResolver::resolve(elit->getType());
			if (entity == nullptr) continue;

			int x = getRandomBetween(elit->getMinX(), elit->getMaxX());
			int y = getRandomBetween(elit->getMinY(), elit->getMaxY());
			Coordinate coordinate(x, y);
			entity->setCoordinate(coordinate);

			//TODO: Set random position
			levelEntities.push_back(entity);
		}
	}
	return levelEntities;
}

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
	GameConfig gameConfig;
	
	parser->parse(&serverConfig);
	parser->parse(&window);
	parser->parse(&config);
	parser->parse(&gameConfig);

	vector<Level>* levels = gameConfig.getLevels();
	for (vector<Level>::iterator it = levels->begin(); it != levels->end(); ++it)
	{
		vector<Entity*> entities = generateLevelEntities(*it);
		(*it).setEntities(entities);
	}


	Server* server = new Server(&serverConfig, parser->getFileContent(), &window, &config, &gameConfig);
	
	if (!server->validate()) {
		return 0;
	}
	server->waitForClientConnections();

	// Will exit when game ends.
	delete parser;
	delete server;
	return 0;
}