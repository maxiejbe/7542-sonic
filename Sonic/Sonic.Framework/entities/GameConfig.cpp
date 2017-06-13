#include "GameConfig.h"

char* GAME_CONFIG_NODE = "juego";
char* GAME_CONFIG_LEVELS_NODE = "niveles";

const char* MESSAGE_PARSING_GAME_CONFIG_NODE = "Inicio de parseo de nodo de configuración del juego.";
const char* MESSAGE_END_PARSING_GAME_CONFIG_NODE = "Fin de parseo de nodo de configuración del juego.";

GameConfig::GameConfig()
{
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

void GameConfig::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_GAME_CONFIG_NODE;

	levels.clear();
	parseCollection<Level>(&levels, nodeRef, GAME_CONFIG_LEVELS_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_GAME_CONFIG_NODE;
}

char* GameConfig::getNodeName()
{
	return GAME_CONFIG_NODE;
}