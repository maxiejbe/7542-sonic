#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Dimensions.h"
#include "Coordinate.h"

using namespace std;

class Entity {
public:
	Entity();
	Entity(int idParam, string typeParam, string colorParam, Dimensions dimensionsParam, Coordinate coordinateParam, string imagePathParam, int zIndexParam);
private:
	int id;
	string type;
	string color;
	Dimensions dimensions;
	Coordinate coordinate;
	string imagePath;
	int zIndex;
};

#endif