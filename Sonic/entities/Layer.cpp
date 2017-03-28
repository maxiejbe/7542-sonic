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
