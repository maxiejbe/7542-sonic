#include "Dimensions.h"

char* DIMENSIONS_NODE = "dimensiones";
const char* DIMENSIONS_WIDTH_NODE = "ancho";
const char* DIMENSIONS_HEIGHT_NODE = "alto";
const char* DIMENSIONS_RADIO_NODE = "radio";

const char* MESSAGE_PARSING_DIMENSIONS_NODE = "Inicio de parseo de nodo dimensiones.";
const char* MESSAGE_END_PARSING_DIMENSIONS_NODE = "Fin de parseo de nodo dimensiones.";

Dimensions::Dimensions() {}

void Dimensions::SetDefaults(int width, int height, int radio)
{
	this->defaultWidth = width;
	this->defaultHeight = height;
	this->defaultRadio = radio;
}

int Dimensions::getWidth()
{
	return width;
}

int Dimensions::getHeight()
{
	return height;
}

int Dimensions::getRadio()
{
	return radio;
}

void Dimensions::Unserialize(Value* nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_DIMENSIONS_NODE;

	std::function<bool(int)> condition = [](int num) { return num > 0; };

	ParseInt(&width, defaultWidth, nodeRef, DIMENSIONS_WIDTH_NODE, condition);

	ParseInt(&height, defaultHeight, nodeRef, DIMENSIONS_HEIGHT_NODE, condition);
	
	ParseInt(&radio, defaultRadio, nodeRef, DIMENSIONS_RADIO_NODE, condition);

	LOG(logINFO) << MESSAGE_END_PARSING_DIMENSIONS_NODE;
}

char* Dimensions::GetNodeName()
{
	return DIMENSIONS_NODE;
}


