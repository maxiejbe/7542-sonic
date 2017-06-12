#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Dimensions.h"
#include "Coordinate.h"
#include "Player.h"
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
	string getColor();
	string getImagePath();
	void setImagePath(string);

	void setType(string);

	Coordinate getCoordinate();
	void setCoordinate(Coordinate);
	Dimensions getDimensions();
	void setDimensions(Dimensions);

	virtual void onCollision(Player* player) = 0;

	bool operator< (const Entity &other) const {
		return zIndex < other.zIndex;
	}
	
	void serialize(Writer<StringBuffer>& writer);
	// Inherited via Serializable
	virtual string serialize() override;
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
protected:
	int id;
	string type;
	string color;
	Dimensions dimensions;
	Coordinate coordinate;
	string imagePath;
	int zIndex;
	
	void setColor(string color);
	void basePropertiesSerialization(Writer<StringBuffer>& writer);
};

#endif