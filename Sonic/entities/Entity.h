#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "Dimensions.h"
#include "Coordinate.h"
#include "../Renderer.h"
#include "LTexture.h"

using namespace std;

class Entity : public Serializable {
public:
	Entity();
	//TODO: create class Camera and make it a singleton
	virtual void draw(SDL_Rect camera);
protected:
	int id;
	string type;
	string color;
	Dimensions dimensions;
	Coordinate coordinate;
	string imagePath;
	int zIndex;
	LTexture gTexture;

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif