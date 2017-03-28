#include "Configuration.h"

Configuration::Configuration()
{
}

Configuration::Configuration(int scrollSpeedParam)
{
	scrollSpeed = scrollSpeedParam;
}

int Configuration::GetScrollSpeed()
{
	return scrollSpeed;
}
