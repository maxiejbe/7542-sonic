#include "Dimensions.h"

char* DIMENSIONS_NODE = "dimensiones";
const char* DIMENSIONS_WIDTH_NODE = "ancho";
const char* DIMENSIONS_HEIGHT_NODE = "alto";
const char* DIMENSIONS_RADIO_NODE = "radio";

Dimensions::Dimensions() {}

Dimensions::Dimensions(int width, int height, int radio)
{
	this->width = width;
	this->height = height;
	this->radio = radio;
}

int Dimensions::getWidth() {
	return width;
}

int Dimensions::getHeight() {
	return height;
}

int Dimensions::getRadio() {
	return radio;
}

void Dimensions::Unserialize(Value* nodeRef)
{
	Value& node = *nodeRef;

	if (node.HasMember(DIMENSIONS_WIDTH_NODE) && node[DIMENSIONS_WIDTH_NODE].IsInt()) {
		width = node[DIMENSIONS_WIDTH_NODE].GetInt();
	}

	if (node.HasMember(DIMENSIONS_HEIGHT_NODE) && node[DIMENSIONS_HEIGHT_NODE].IsInt()) {
		height = node[DIMENSIONS_HEIGHT_NODE].GetInt();
	}

	if (node.HasMember(DIMENSIONS_RADIO_NODE) && node[DIMENSIONS_RADIO_NODE].IsInt()) {
		radio = node[DIMENSIONS_RADIO_NODE].GetInt();
	}
}

char* Dimensions::GetNodeName()
{
	return DIMENSIONS_NODE;
}
