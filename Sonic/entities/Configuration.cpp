#include "Configuration.h"

char* CONFIGURATION_NODE = "configuracion";
const char* CONFIGURATION_SCROLL_SPEED_NODE = "vel_scroll";

Configuration::Configuration()
{
}

int Configuration::GetScrollSpeed()
{
	return scrollSpeed;
}

void Configuration::Unserialize(Value* nodeRef)
{
	Value& node = *nodeRef;

	if (node.HasMember(CONFIGURATION_SCROLL_SPEED_NODE) && node[CONFIGURATION_SCROLL_SPEED_NODE].IsInt()) {
		scrollSpeed = node[CONFIGURATION_SCROLL_SPEED_NODE].GetInt();
	}
}

char * Configuration::GetNodeName()
{
	return CONFIGURATION_NODE;
}
