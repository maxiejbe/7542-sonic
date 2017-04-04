#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SDL.h>
#include "Dimensions.h"
#include "Coordinate.h"
#include "../Renderer.h"
#include "Texture.h"
#include "common/Drawable.h"

using namespace std;

class Entity : public Serializable, public Drawable {
public:
	Entity();
	Entity(Entity* entity);
	void draw(SDL_Rect camera) override;

	string GetType();
	bool operator< (const Entity &other) const {
		return zIndex < other.zIndex;
	}
protected:
	int id;
	string type;
	string color;
	Dimensions dimensions;
	Coordinate coordinate;
	string imagePath;
	int zIndex;
	Texture texture;
	bool imageCrop;

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif