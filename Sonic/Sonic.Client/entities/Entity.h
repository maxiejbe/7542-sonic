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
	virtual bool validate();

	virtual Dimensions getDefaultDimensions();
	
	Uint32 getColorRgba();

	string getType();
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

	void setColor(string color);

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif