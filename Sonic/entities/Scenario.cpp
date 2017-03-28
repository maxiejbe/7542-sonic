#include "Scenario.h"

Scenario::Scenario()
{
}

Scenario::Scenario(Dimensions dimensionsParam, vector<Layer> layersParam, vector<Entity> entitiesParam)
{
	dimensions = dimensionsParam;
	layers = layersParam;
	entities = entitiesParam;
}
