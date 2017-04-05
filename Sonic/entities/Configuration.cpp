#include "Configuration.h"

char* CONFIGURATION_NODE = "configuracion";
const char* CONFIGURATION_SCROLL_SPEED_NODE = "vel_scroll";
const char* CONFIGURATION_LOG_LEVEL_NODE = "nivel_log";

const char* MESSAGE_PARSING_CONFIGURATION_NODE = "Inicio de parseo de nodo configuración.";
const char* MESSAGE_END_PARSING_CONFIGURATION_NODE = "Fin de parseo de nodo configuración.";

const int DEFAULT_SCROLL_SPEED = 600;

Configuration::Configuration()
{
}

int Configuration::getScrollSpeed()
{
	return scrollSpeed;
}

void Configuration::unserialize(Value* nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_CONFIGURATION_NODE;

	parseInt(&scrollSpeed, DEFAULT_SCROLL_SPEED, nodeRef, CONFIGURATION_SCROLL_SPEED_NODE, Validator::intGreaterThanZero);
	
	LOG(logINFO) << MESSAGE_END_PARSING_CONFIGURATION_NODE;
}

char * Configuration::getNodeName()
{
	return CONFIGURATION_NODE;
}
