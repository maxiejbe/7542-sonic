#include "GameConfig.h"

char* GAME_CONFIG_NODE = "juego";
char* GAME_CONFIG_MODE_NODE = "modo";
char* GAME_CONFIG_LEVELS_NODE = "niveles";

const char* MESSAGE_PARSING_GAME_CONFIG_NODE = "Inicio de parseo de nodo de configuración del juego.";
const char* MESSAGE_END_PARSING_GAME_CONFIG_NODE = "Fin de parseo de nodo de configuración del juego.";

string GAME_CONFIG_MODE_DEFAULT = "individual";

GameConfig::GameConfig()
{
}

GameMode GameConfig::fromStringMode(string gameMode)
{
	if (gameMode == "individual")
		return GameMode::individual;
	else if (gameMode == "grupal")
		return GameMode::grupal;
	else if (gameMode == "colaborativo")
		return GameMode::colaborativo;
	else
		return GameMode::individual;
}

string GameConfig::toStringMode(GameMode mode)
{
	switch (mode)
	{
	case individual:
		return "individual";
		break;
	case grupal:
		return "grupal";
		break;
	case colaborativo:
		return "colaborativo";
		break;
	default:
		return "";
		break;
	}
}

vector<Level>* GameConfig::getLevels()
{
	return &(this->levels);
}

Level * GameConfig::getLevel(int levelNumber)
{
	int lvlIdx = levelNumber - 1;
	if (lvlIdx < 0 || lvlIdx >= this->levels.size()) return nullptr;

	return &this->levels[lvlIdx];
}

GameMode GameConfig::getMode()
{
	return this->mode;
}

void GameConfig::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_GAME_CONFIG_NODE;

	string stringMode;
	parseString(&stringMode, GAME_CONFIG_MODE_DEFAULT, nodeRef, GAME_CONFIG_MODE_NODE);
	this->mode = fromStringMode(stringMode);

	levels.clear();
	parseCollection<Level>(&levels, nodeRef, GAME_CONFIG_LEVELS_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_GAME_CONFIG_NODE;
}

char* GameConfig::getNodeName()
{
	return GAME_CONFIG_NODE;
}