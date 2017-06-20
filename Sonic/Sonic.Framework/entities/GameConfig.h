#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include "common/Serializable.h"
#include <vector>
#include "Level.h"

using namespace std;

enum GameMode { individual, grupal, colaborativo };

class GameConfig : public Serializable {
public:
	GameConfig();

	vector<Level>* getLevels();
	Level * getLevel(int);

	GameMode getMode();
	int getRingPointsMultiplier();
	int getRingsForBonus();
	int getBonusRingPointsMultiplier();
private:
	vector<Level> levels;

	GameMode fromStringMode(string mode);
	string toStringMode(GameMode mode);

	GameMode mode;
	int ringPointsMultiplier;
	int ringsForBonus;
	int	bonusRingPointsMultiplier;

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif