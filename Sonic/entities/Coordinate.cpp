#include "Coordinate.h"

char* COORDINATE_NODE = "coordenada";
const char* COORDINATE_X_NODE = "x";
const char* COORDINATE_Y_NODE = "y";

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

void Coordinate::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	
	if (node.HasMember(COORDINATE_X_NODE) && node[COORDINATE_X_NODE].IsInt()) {
		x = node[COORDINATE_X_NODE].GetInt();
	}

	if (node.HasMember(COORDINATE_Y_NODE) && node[COORDINATE_Y_NODE].IsInt()) {
		y = node[COORDINATE_Y_NODE].GetInt();
	}
}

char * Coordinate::GetNodeName()
{
	return COORDINATE_NODE;
}
