#include "protocol/Message.h"
#include "protocol/SerializableMessage.h"
#include "entities/Server.h"
#include "entities/GameConfig.h"
#include "Parser.h"
#include "Rectangle2.h"

vector<Rectangle2> rectangles;

int getRandomBetween(int min, int max) {
	return rand() % ((max - min) + 1) + min;
}

vector<Entity*> generateLevelEntities(Level level, int* entityId) {
	vector<Entity*> levelEntities;
	levelEntities.clear();
	vector<EntityLimit> limits = level.getLimits();
	srand(time(0));

	for (vector<EntityLimit>::iterator elit = limits.begin(); elit != limits.end(); ++elit) {
		//Random entities count
		int entitiesCount = getRandomBetween(elit->getMinCount(), elit->getMaxCount());

		for (size_t i = 0; i < entitiesCount; i++)
		{
			Entity* entity = EntityResolver::resolve(elit->getType());
			if (entity == nullptr) continue;

			entity->setId(*entityId);

			int x = getRandomBetween(elit->getMinX(), elit->getMaxX());
			int y = getRandomBetween(elit->getMinY(), elit->getMaxY());
			entity->setCoordinate(Coordinate(x, y));

			bool isCollisioning = true;
			while (isCollisioning) {
				isCollisioning = false;
				for (Rectangle2 r : rectangles) {
					if (r.collisionsWith(entity->getLeft(), entity->getRight(), entity->getTop(), entity->getBottom())) {
						isCollisioning = true;
						break;
					}
				}

				if (!isCollisioning) break;
				x = getRandomBetween(elit->getMinX(), elit->getMaxX());
				y = getRandomBetween(elit->getMinY(), elit->getMaxY());
				entity->setCoordinate(Coordinate(x, y));
			}

			rectangles.push_back(Rectangle2(entity->getLeft(), entity->getRight(), entity->getTop(), entity->getBottom()));

			levelEntities.push_back(entity);
			(*entityId)++;
		}
	}

	rectangles.clear();
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
	int entityId = 1;
	for (vector<Level>::iterator it = levels->begin(); it != levels->end(); ++it)
	{
		vector<Entity*> entities = generateLevelEntities(*it, &entityId);
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