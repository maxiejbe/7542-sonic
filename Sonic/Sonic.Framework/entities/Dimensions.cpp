#include "Dimensions.h"

char* DIMENSIONS_NODE = "dimensiones";

const char* DIMENSIONS_WIDTH_NODE = "ancho";
const char* DIMENSIONS_HEIGHT_NODE = "alto";
const char* DIMENSIONS_RADIO_NODE = "radio";

const char* MESSAGE_PARSING_DIMENSIONS_NODE = "Inicio de parseo de nodo dimensiones.";
const char* MESSAGE_END_PARSING_DIMENSIONS_NODE = "Fin de parseo de nodo dimensiones.";

Dimensions::Dimensions() {}

Dimensions::Dimensions(int width, int height, int radio)
{
	this->width = width;
	this->height = height;
	this->radio = radio;
}

void Dimensions::setDefaults(int width, int height, int radio)
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

string Dimensions::serialize()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	writer.StartObject();
	writer.String(DIMENSIONS_WIDTH_NODE);
	writer.Int(width);
	writer.String(DIMENSIONS_HEIGHT_NODE);
	writer.Int(height);
	writer.String(DIMENSIONS_RADIO_NODE);
	writer.Int(radio);
	writer.EndObject();

	return s.GetString();
}

void Dimensions::unserialize(Value* nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_DIMENSIONS_NODE;

	if (defaultWidth > 0) {
		parseInt(&width, defaultWidth, nodeRef, DIMENSIONS_WIDTH_NODE, Validator::intGreaterThanZero);
	}
	
	if (defaultHeight > 0) {
		parseInt(&height, defaultHeight, nodeRef, DIMENSIONS_HEIGHT_NODE, Validator::intGreaterThanZero);
	}
	
	if (defaultRadio > 0) {
		parseInt(&radio, defaultRadio, nodeRef, DIMENSIONS_RADIO_NODE, Validator::intGreaterThanZero);
	}
	
	LOG(logINFO) << MESSAGE_END_PARSING_DIMENSIONS_NODE;
}

char* Dimensions::getNodeName()
{
	return DIMENSIONS_NODE;
}


