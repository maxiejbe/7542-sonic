#include "Entity.h"
#include "common/EntityResolver.h"

#include <iostream>

const char* ENTITY_NODE = "entidades";
const char* ENTITY_ID_NODE = "id";
const char* ENTITY_TYPE_NODE = "tipo";
const char* ENTITY_IMAGE_PATH_NODE = "ruta_imagen";
const char* ENTITY_IS_ACTIVE_NODE = "act";

const char* MESSAGE_PARSING_ENTITY_NODE = "Inicio de parseo de nodo entidad.";
const char* MESSAGE_END_PARSING_ENTITY_NODE = "Fin de parseo de nodo entidad.";

const char* ERROR_ENTITY_NO_TYPE = "No puede dibujarse la entidad ya que no tiene un tipo válido.";
const char* ERROR_ENTITY_NO_COORDINATE_X = "No puede dibujarse la entidad ya que no tiene coordenada X válida.";
const char* ERROR_ENTITY_NO_COORDINATE_Y = "No puede dibujarse la entidad ya que no tiene coordenada Y válida.";

const int ENTITY_DEFAULT_ID = 1;
const string ENTITY_DEFAULT_TYPE = "";
const int ENTITY_DEFAULT_TYPEID = 0;
const string ENTITY_DEFAULT_IMAGE_PATH = ""; // Vacio = no hay imagen (solo color)
const double ENTITY_DEFAULT_MAX_DISTANCE = 0;

Entity::Entity()
{
	this->maxHorizontalDistance = ENTITY_DEFAULT_MAX_DISTANCE;
	this->maxVerticalDistance = ENTITY_DEFAULT_MAX_DISTANCE;
}

Entity::Entity(Entity* entity)
{
	this->id = entity->id;
	this->type = entity->type;
	this->dimensions = entity->dimensions;
	this->coordinate = entity->coordinate;
	this->imagePath = entity->imagePath;
	this->isActive = entity->isActive;
	this->facingDirection = entity->facingDirection;
	this->time = entity->time;
	this->maxHorizontalDistance = ENTITY_DEFAULT_MAX_DISTANCE;
	this->maxVerticalDistance = ENTITY_DEFAULT_MAX_DISTANCE;
	this->isRecovering = false;
}

void Entity::copyFrom(Entity & anotherEntity)
{
	this->id = anotherEntity.id;
	this->type = anotherEntity.type;
	this->dimensions = anotherEntity.dimensions;
	this->coordinate = anotherEntity.coordinate;
	this->imagePath = anotherEntity.imagePath;
	this->isActive = anotherEntity.isActive;
	this->facingDirection = anotherEntity.facingDirection;
	this->maxHorizontalDistance = ENTITY_DEFAULT_MAX_DISTANCE;
	this->maxVerticalDistance = ENTITY_DEFAULT_MAX_DISTANCE;
	this->isRecovering = anotherEntity.isRecovering;
}

bool Entity::validate()
{
	if (type.empty())
	{
		LOG(logERROR) << ERROR_ENTITY_NO_TYPE;
		return false;
	}

	if (coordinate.getX() < 0) {
		LOG(logERROR) << ERROR_ENTITY_NO_COORDINATE_X;
		return false;
	}
	if (coordinate.getY() < 0)
	{
		LOG(logERROR) << ERROR_ENTITY_NO_COORDINATE_Y;
		return false;
	}
	return true;
}

Dimensions Entity::getDefaultDimensions()
{
	return Dimensions();
}

int Entity::getXPosition()
{
	return coordinate.getX();
}

int Entity::getYPosition()
{
	return coordinate.getY();
}

int Entity::getRadio()
{
	//Use when entity is a circle
	return dimensions.getRadio();
}

int Entity::getWidth()
{
	return dimensions.getWidth();
}

int Entity::getHeight()
{
	return dimensions.getHeight();
}

CollisionableType Entity::getCollisionableType()
{
	//For now, every entity is a rectangle
	//We should override this on each child
	return CollisionableType::rectangle;
}

double Entity::getMaxHorizontalDistance()
{
	return this->maxHorizontalDistance;
}

double Entity::getMaxVerticalDistance() {
	return this->maxVerticalDistance;
}

bool Entity::getIsMoving()
{
	return this->isMoving;
}

void Entity::setIsActive(bool isActive)
{
	this->isActive = isActive;
}

bool Entity::getIsActive()
{
	return this->isActive;
}

void Entity::lock()
{
	this->entityMutex.lock();
}

void Entity::unlock()
{
	this->entityMutex.unlock();
}

string Entity::getType()
{
	return type;
}

void Entity::setImagePath(string imagePath)
{
	this->imagePath = imagePath;
}

void Entity::setType(string type)
{
	this->type = type;
}

string Entity::getImagePath()
{
	return imagePath;
}

Coordinate Entity::getCoordinate()
{
	return coordinate;
}

void Entity::setCoordinate(Coordinate coordinate)
{
	this->coordinate = coordinate;
}

Dimensions Entity::getDimensions()
{
	return dimensions;
}

void Entity::setDimensions(Dimensions dimensions)
{
	this->dimensions = dimensions;
}

void Entity::serialize(Writer<StringBuffer> &writer)
{
	writer.StartObject();
	basePropertiesSerialization(writer);
	writer.EndObject();
}

string Entity::serialize()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	serialize(writer);
	return s.GetString();
}

void Entity::basePropertiesSerialization(Writer<StringBuffer>& writer)
{
	writer.String(ENTITY_ID_NODE);
	writer.Int(id);
	writer.String(ENTITY_TYPE_NODE);
	writer.Int(EntityResolver::fromTypeString(type));
	//writer.String(ENTITY_ZINDEX_NODE);
	//writer.Int(zIndex);
	writer.String(ENTITY_IS_ACTIVE_NODE);
	writer.Bool(isActive);
	//writer.String(ENTITY_TIME_NODE);
	//writer.Int(time);
	writer.String(coordinate.getNodeName());
	coordinate.serialize(writer);
}

void Entity::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;
	const char* nodeName = getNodeName();

	LOG(logINFO) << MESSAGE_PARSING_ENTITY_NODE;

	parseInt(&id, ENTITY_DEFAULT_ID, nodeRef, ENTITY_ID_NODE, Validator::intGreaterThanZero);

	int typeId;
	parseInt(&typeId, ENTITY_DEFAULT_TYPEID, nodeRef, ENTITY_TYPE_NODE, Validator::intGreaterThanOrEqualToZero);
	type = EntityResolver::toTypeString((EntityType)typeId);

	coordinate.parseObject(nodeRef);

	parseString(&imagePath, ENTITY_DEFAULT_IMAGE_PATH, nodeRef, ENTITY_IMAGE_PATH_NODE);

	//parseInt(&zIndex, ENTITY_DEFAULT_ZINDEX, nodeRef, ENTITY_ZINDEX_NODE);

	parseBool(&isActive, true, nodeRef, ENTITY_IS_ACTIVE_NODE);

	//parseInt(&time, 0, nodeRef, ENTITY_TIME_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_ENTITY_NODE;
}

char* Entity::getNodeName()
{
	return nullptr;
}

int Entity::getTime()
{
	return this->time;
}

void Entity::setTime(int time)
{
	this->time = time;
}

void Entity::setId(int id)
{
	this->id = id;
}

int Entity::getId()
{
	return this->id;
}

FacingDirection Entity::getFacingDirection()
{
	return this->facingDirection;
}

void Entity::setFacingDirection(FacingDirection facingDirection)
{
	this->facingDirection = facingDirection;
}

bool Entity::getIsRecovering()
{
	return this->isRecovering;
}

void Entity::setIsRecovering(bool isRecovering)
{
	this->isRecovering = isRecovering;
}
