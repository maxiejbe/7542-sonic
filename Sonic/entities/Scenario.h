#ifndef SCENARIO_H
#define SCENARIO_H

#include "Dimensions.h"
#include "Entity.h"
#include "Layer.h"
#include <iostream>
#include <vector>

using namespace std;

class Scenario {
public:
	Scenario();
	void SetDimensions(Dimensions dimensionsParam);
	void SetLayers(vector<Layer> layersParam);
	void SetEntities(vector<Entity> entitiesParam);

private:
	Dimensions dimensions;
	vector<Layer> layers;
	vector<Entity> entities;
};

#endif