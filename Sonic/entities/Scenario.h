#ifndef SCENARIO_H
#define SCENARIO_H

#include "Dimensions.h"
#include "Entity.h"
#include "Layer.h"
#include <iostream>
#include <vector>

using namespace std;

class Scenario : public Serializable {
public:
	Scenario();
	void SetDimensions(Dimensions);
	void SetLayers(vector<Layer>);
	void SetEntities(vector<Entity>);

private:
	Dimensions dimensions;
	vector<Layer> layers;
	vector<Entity> entities;
	
	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif