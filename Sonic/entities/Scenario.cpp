#include "Scenario.h"

Scenario::Scenario()
{
}

void Scenario::SetDimensions(Dimensions dimensionsParam)
{
	dimensions = dimensionsParam;
}

void Scenario::SetLayers(vector<Layer> layersParam)
{
	layers = layersParam;
}

void Scenario::SetEntities(vector<Entity> entitiesParam)
{
	entities = entitiesParam;
}
