#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "Dimensions.h"
#include "Coordinate.h"
#include "../Renderer.h"
#include "Texture.h"

using namespace std;

class Entity : public Serializable {
public:
	Entity();
	//TODO: create class Camera and make it a singleton
protected:
	int id;
	string type;
	string color;
	Dimensions dimensions;
	Coordinate coordinate;
	string imagePath;
	int zIndex;

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif