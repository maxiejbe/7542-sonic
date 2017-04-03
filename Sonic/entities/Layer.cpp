#include "Layer.h"

const char* LAYER_ID_NODE = "id";
const char* LAYER_ZINDEX_NODE = "index_z";
const char* LAYER_IMAGE_PATH_NODE = "ruta_imagen";

Layer::Layer()
{
}

void Layer::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	const char* nodeName = GetNodeName();

	if (node.HasMember(LAYER_ID_NODE) && node[LAYER_ID_NODE].IsInt()) {
		id = node[LAYER_ID_NODE].GetInt();
	}

	if (node.HasMember(LAYER_ZINDEX_NODE) && node[LAYER_ZINDEX_NODE].IsInt()) {
		zIndex = node[LAYER_ZINDEX_NODE].GetInt();
	}

	if (node.HasMember(LAYER_IMAGE_PATH_NODE) && node[LAYER_IMAGE_PATH_NODE].IsString()) {
		imagePath = node[LAYER_IMAGE_PATH_NODE].GetString();
	}
}

char* Layer::GetNodeName()
{
	return "0";
}

bool Layer::loadLayer()
{
	if (!layer.loadFromFile("img/level2.jpg")) //TODO: imagePath that gets from json
	{
		printf("Failed to load background texture!\n");
		return false;
	}
	return true;
}

void Layer::renderLayer(int x, int y, SDL_Rect* rect)
{
	layer.render(x,y,rect);
}

void Layer::destroyLayer() 
{
	layer.free();
}

int Layer::getZIndex()
{
	return zIndex;
}

string Layer::getImagePath()
{
	return imagePath;
}

