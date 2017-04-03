#include "Configuration.h"

char* CONFIGURATION_NODE = "configuracion";
const char* CONFIGURATION_SCROLL_SPEED_NODE = "vel_scroll";
const char* CONFIGURATION_LOG_LEVEL_NODE = "nivel_log";

const char* MESSAGE_PARSING_CONFIGURATION_NODE = "Inicio de parseo de nodo configuración.";
const char* MESSAGE_END_PARSING_CONFIGURATION_NODE = "Fin de parseo de nodo configuración.";

const int DEFAULT_SCROLL_SPEED = 600;
const string DEFAULT_LOG_LEVEL = "medium";

Configuration::Configuration()
{
}

int Configuration::GetScrollSpeed()
{
	return scrollSpeed;
}

string Configuration::GetLogLevel() {
	return logLevel;
}

void Configuration::Unserialize(Value* nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_CONFIGURATION_NODE;

	ParseInt(&scrollSpeed, DEFAULT_SCROLL_SPEED, nodeRef, CONFIGURATION_SCROLL_SPEED_NODE);
	
	ParseString(&logLevel, DEFAULT_LOG_LEVEL, nodeRef, CONFIGURATION_LOG_LEVEL_NODE);
	
	LOG(logINFO) << MESSAGE_END_PARSING_CONFIGURATION_NODE;
}

char * Configuration::GetNodeName()
{
	return CONFIGURATION_NODE;
}
