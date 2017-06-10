#include "Coordinate.h"

char* COORDINATE_NODE = "coordenada";
const char* COORDINATE_X_NODE = "x";
const char* COORDINATE_Y_NODE = "y";

const char* MESSAGE_PARSING_COORDINATE_NODE = "Inicio de parseo de nodo coordenada.";
const char* MESSAGE_END_PARSING_COORDINATE_NODE = "Fin de parseo de nodo coordenada.";

const int COORDINATE_DEFAULT_X = -1;
const int COORDINATE_DEFAULT_Y = -1;

Coordinate::Coordinate(){}

Coordinate::Coordinate(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Coordinate::getX() {
	return x;
}

int Coordinate::getY() {
	return y;
}

void Coordinate::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	
	LOG(logINFO) << MESSAGE_PARSING_COORDINATE_NODE;

	parseInt(&x, COORDINATE_DEFAULT_X, nodeRef, COORDINATE_X_NODE, Validator::intGreaterThanOrEqualToZero);
	
	parseInt(&y, COORDINATE_DEFAULT_Y, nodeRef, COORDINATE_Y_NODE, Validator::intGreaterThanOrEqualToZero);

	LOG(logINFO) << MESSAGE_END_PARSING_COORDINATE_NODE;
}

char * Coordinate::getNodeName()
{
	return COORDINATE_NODE;
}
