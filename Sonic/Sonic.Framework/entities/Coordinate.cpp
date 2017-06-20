#include "Coordinate.h"

char* COORDINATE_NODE = "coo";
const char* COORDINATE_X_NODE = "x";
const char* COORDINATE_Y_NODE = "y";

const char* MESSAGE_PARSING_COORDINATE_NODE = "Inicio de parseo de nodo coordenada.";
const char* MESSAGE_END_PARSING_COORDINATE_NODE = "Fin de parseo de nodo coordenada.";

const int COORDINATE_DEFAULT_X = -1;
const int COORDINATE_DEFAULT_Y = -1;

Coordinate::Coordinate() {}

Coordinate::Coordinate(double x, double y)
{
	this->x = x;
	this->y = y;
}

double Coordinate::getX() {
	return x;
}

double Coordinate::getY() {
	return y;
}

void Coordinate::serialize(Writer<StringBuffer>&writer)
{
	writer.SetMaxDecimalPlaces(4);
	writer.StartObject();
	writer.String(COORDINATE_X_NODE);
	writer.Double(x);
	writer.String(COORDINATE_Y_NODE);
	writer.Double(y);
	writer.EndObject();
}

string Coordinate::serialize()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	serialize(writer);
	return s.GetString();
}

void Coordinate::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_COORDINATE_NODE;

	parseDouble(&x, COORDINATE_DEFAULT_X, nodeRef, COORDINATE_X_NODE);

	parseDouble(&y, COORDINATE_DEFAULT_Y, nodeRef, COORDINATE_Y_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_COORDINATE_NODE;
}

char * Coordinate::getNodeName()
{
	return COORDINATE_NODE;
}
