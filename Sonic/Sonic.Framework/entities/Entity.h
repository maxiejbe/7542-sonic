#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Dimensions.h"
#include "Coordinate.h"
#include "common/Collisionable.h"
#include "Player.h"
#include "common/Serializable.h"
#include "common/Validator.h"
#include "Camera.h"

using namespace std;

class Entity : public Serializable, public Collisionable {
public:
	Entity();
	Entity(Entity* entity);

	void copyFrom(Entity&);

	virtual bool validate();

	virtual Dimensions getDefaultDimensions();

	//Collisionable
	int getXPosition() override;
	int getYPosition() override;
	int getRadio() override;
	int getWidth() override;
	int getHeight() override;
	CollisionableType getCollisionableType() override;

	double getMaxHorizontalDistance();
	double getMaxVerticalDistance();
	
	bool getIsMoving();

	bool getIsActive();

	void lock();
	void unlock();

	string getType();
	string getImagePath();
	void setImagePath(string);

	void setType(string);

	Coordinate getCoordinate();
	void setCoordinate(Coordinate);
	Dimensions getDimensions();
	void setDimensions(Dimensions);

	void setId(int);
	int getId();

	int getTime();
	void setTime(int time);

	FacingDirection getFacingDirection();
	void setFacingDirection(FacingDirection);

	virtual void onCollision(Player* player, Camera* camera) = 0;

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
	Dimensions dimensions;
	Coordinate coordinate;
	string imagePath;
	int zIndex;
	int time;
	FacingDirection facingDirection;
	double maxHorizontalDistance;
	double maxVerticalDistance;

	bool isActive;
	bool isMoving = false;

	void basePropertiesSerialization(Writer<StringBuffer>& writer);

	mutex entityMutex;
};

#endif