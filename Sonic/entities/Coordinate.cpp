#include "Coordinate.h"

char* COORDINATE_NODE = "coordenada";
const char* COORDINATE_X_NODE = "x";
const char* COORDINATE_Y_NODE = "y";

const char* MESSAGE_PARSING_COORDINATE_NODE = "Inicio de parseo de nodo coordenada.";
const char* MESSAGE_END_PARSING_COORDINATE_NODE = "Fin de parseo de nodo coordenada.";

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

	ParseInt(&x, 0, nodeRef, COORDINATE_X_NODE);
	
	ParseInt(&y, 0, nodeRef, COORDINATE_Y_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_COORDINATE_NODE;
}

char * Coordinate::GetNodeName()
{
	return COORDINATE_NODE;
}
