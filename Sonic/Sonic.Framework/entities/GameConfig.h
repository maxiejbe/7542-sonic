#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include "common/Serializable.h"
#include <vector>
#include "Level.h"

using namespace std;

class GameConfig : public Serializable {
public:
	GameConfig();

private:
	vector<Level> levels;

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif