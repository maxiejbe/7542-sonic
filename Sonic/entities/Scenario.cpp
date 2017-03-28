#include "Scenario.h"

char* SCENARIO_NODE = "escenario";
char* SCENARIO_LAYERS_NODE = "capas";
char* SCENARIO_ENTITIES_NODE = "entidades";

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

void Scenario::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	
	dimensions.ParseObject(nodeRef);

	//TODO: Extract layers and entities code blocks to new method
	Value& layersNode = node[SCENARIO_LAYERS_NODE];
	layers.clear();

	if (layersNode.IsArray()) {
		for (SizeType i = 0; i < layersNode.Size(); i++) {
			Value& layerNode = layersNode[i];
			Layer layer;
			layer.ParseCurrentObject(&layerNode);
			layers.push_back(layer);
		}
	}

	Value& entitiesNode = node[SCENARIO_ENTITIES_NODE];
	entities.clear();

	if (entitiesNode.IsArray()) {
		for (SizeType i = 0; i < entitiesNode.Size(); i++) {
			Value& entityNode = entitiesNode[i];
			Entity entity;
			entity.ParseCurrentObject(&entityNode);
			entities.push_back(entity);
		}
	}
}

char * Scenario::GetNodeName()
{
	return SCENARIO_NODE;
}
