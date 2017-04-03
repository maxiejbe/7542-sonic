#include "Coordinate.h"

char* COORDINATE_NODE = "coordenada";
const char* COORDINATE_X_NODE = "x";
const char* COORDINATE_Y_NODE = "y";

const char* MESSAGE_PARSING_COORDINATE_NODE = "Inicio de parseo de nodo coordenada.";
const char* MESSAGE_END_PARSING_COORDINATE_NODE = "Fin de parseo de nodo coordenada.";

const int COORDINATE_DEFAULT_X = -1;
const int COORDINATE_DEFAULT_Y = -1;

Coordinate::Coordinate(){}

int Coordinate::getX() {
	return x;
}

int Coordinate::getY() {
	return y;
}

void Coordinate::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	
	LOG(logINFO) << MESSAGE_PARSING_COORDINATE_NODE;

	ParseInt(&x, COORDINATE_DEFAULT_X, nodeRef, COORDINATE_X_NODE);
	
	ParseInt(&y, COORDINATE_DEFAULT_Y, nodeRef, COORDINATE_Y_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_COORDINATE_NODE;
}

char * Coordinate::GetNodeName()
{
	return COORDINATE_NODE;
}
