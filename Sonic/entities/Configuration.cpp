#include "Configuration.h"

char* CONFIGURATION_NODE = "configuracion";
const char* CONFIGURATION_SCROLL_SPEED_NODE = "vel_scroll";
const char* CONFIGURATION_LOG_LEVEL_NODE = "nivel_log";

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

	if (node.HasMember(CONFIGURATION_SCROLL_SPEED_NODE) && node[CONFIGURATION_SCROLL_SPEED_NODE].IsInt()) {
		scrollSpeed = node[CONFIGURATION_SCROLL_SPEED_NODE].GetInt();
	}

	if (node.HasMember(CONFIGURATION_LOG_LEVEL_NODE) && node[CONFIGURATION_LOG_LEVEL_NODE].IsString()) {
		logLevel = node[CONFIGURATION_LOG_LEVEL_NODE].GetString();
	}
}

char * Configuration::GetNodeName()
{
	return CONFIGURATION_NODE;
}
