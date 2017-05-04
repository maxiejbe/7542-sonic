#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Dimensions.h"
#include "Coordinate.h"
#include "common/Serializable.h"
#include "common/Validator.h"

using namespace std;

class Entity : public Serializable {
public:
	Entity();
	Entity(Entity* entity);
	virtual bool validate();

	virtual Dimensions getDefaultDimensions();
	
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
	bool imageCrop;

	void setColor(string color);

	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif