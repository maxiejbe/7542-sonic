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
	Scenario(Dimensions dimensionsParam, vector<Layer> layersParam, vector<Entity> entitiesParam);

private:
	Dimensions dimensions;
	vector<Layer> layers;
	vector<Entity> entities;
};

#endif