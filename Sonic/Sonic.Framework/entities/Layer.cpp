#include "Layer.h"

const char* LAYER_ID_NODE = "id";
const char* LAYER_ZINDEX_NODE = "index_z";
const char* LAYER_IMAGE_PATH_NODE = "ruta_imagen";

const char* MESSAGE_PARSING_LAYER_NODE = "Inicio de parseo de nodo capa.";
const char* MESSAGE_END_PARSING_LAYER_NODE = "Fin de parseo de nodo capa.";

const int LAYER_DEFAULT_ID = 1;
const int LAYER_DEFAULT_ZINDEX = 0;
const string LAYER_DEFAULT_IMAGE_PATH = "img/layer-not-found.png";

Layer::Layer()
{
}

void Layer::serialize(Writer<StringBuffer> &writer)
{
	writer.StartObject();
	writer.String(LAYER_ID_NODE);
	writer.Int(id);
	writer.String(LAYER_ZINDEX_NODE);
	writer.Int(zIndex);
	writer.String(LAYER_IMAGE_PATH_NODE);
	writer.String(imagePath.c_str());
	writer.EndObject();
}

string Layer::serialize()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	serialize(writer);
	return s.GetString();
}

void Layer::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	
	LOG(logINFO) << MESSAGE_PARSING_LAYER_NODE;

	parseInt(&id, LAYER_DEFAULT_ID, nodeRef, LAYER_ID_NODE, Validator::intGreaterThanZero);

	parseInt(&zIndex, LAYER_DEFAULT_ZINDEX, nodeRef, LAYER_ZINDEX_NODE);

	parseString(&imagePath, LAYER_DEFAULT_IMAGE_PATH, nodeRef, LAYER_IMAGE_PATH_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_LAYER_NODE;
}

char* Layer::getNodeName()
{
	return nullptr;
}

int Layer::getZIndex()
{
	return zIndex;
}

string Layer::getImagePath()
{
	return imagePath;
}

void Layer::setImagePath(string imagePath)
{
	this->imagePath = imagePath;
}

