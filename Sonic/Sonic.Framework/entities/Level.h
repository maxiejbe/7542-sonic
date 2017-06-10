#ifndef LEVEL_H
#define LEVEL_H

#include "Scenario.h"
#include "EntityLimit.h"
//#include "Entity.h"
#include <iostream>
#include <vector>

using namespace std;

class Level : public Serializable {
public:
	Level();
	~Level();

	vector<EntityLimit> getLimits();
	Scenario getScenario();

	void setEntities(vector<Entity*> entities);

private:
	Scenario scenario;
	vector<EntityLimit> limits;

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif