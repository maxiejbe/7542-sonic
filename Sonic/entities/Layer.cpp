#include "Layer.h"

const char* LAYER_ID_NODE = "id";
const char* LAYER_ZINDEX_NODE = "index_z";
const char* LAYER_IMAGE_PATH_NODE = "ruta_imagen";

const char* MESSAGE_PARSING_LAYER_NODE = "Inicio de parseo de nodo capa.";
const char* MESSAGE_END_PARSING_LAYER_NODE = "Fin de parseo de nodo capa.";

const int LAYER_DEFAULT_ID = 0;
const int LAYER_DEFAULT_ZINDEX = 0;
const string LAYER_DEFAULT_IMAGE_PATH = "";

Layer::Layer()
{
}

void Layer::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	const char* nodeName = GetNodeName();

	LOG(logINFO) << MESSAGE_PARSING_LAYER_NODE;

	ParseInt(&id, LAYER_DEFAULT_ID, nodeRef, LAYER_ID_NODE);
	
	ParseInt(&zIndex, LAYER_DEFAULT_ZINDEX, nodeRef, LAYER_ZINDEX_NODE);

	ParseString(&imagePath, LAYER_DEFAULT_IMAGE_PATH, nodeRef, LAYER_IMAGE_PATH_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_LAYER_NODE;
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

