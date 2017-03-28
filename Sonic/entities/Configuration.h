#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration {
public:
	Configuration();
	Configuration(int scrollSpeedParam);

	int GetScrollSpeed();
private:
	int scrollSpeed;
};

#endif