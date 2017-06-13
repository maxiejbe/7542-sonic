#include "EntityResolver.h"

const char* ENTITYRESOLVER_ENTITY_TYPE_NODE = "tipo";

Entity * EntityResolver::resolve(string entityType)
{
	Entity* destination = nullptr;

	if (entityType == toTypeString(EntityType::obstaculo_pinche) ||
		entityType == toTypeString(EntityType::obstaculo_piedra)) {
		destination = new Obstacle(entityType);
	}
	else if (entityType == toTypeString(EntityType::anillo)) {
		destination = new Ring(entityType);
	}
	else if (entityType == toTypeString(EntityType::bonus_super_ring) ||
		entityType == toTypeString(EntityType::bonus_invencibilidad) ||
		entityType == toTypeString(EntityType::bonus_escudo)) {
		destination = new Bonus(entityType);
	}
	else if (entityType == toTypeString(EntityType::enemigo_cangrejo) ||
		entityType == toTypeString(EntityType::enemigo_pez) ||
		entityType == toTypeString(EntityType::enemigo_mosca)) {
		destination = new Enemy(entityType);
	}

	return destination;
}

Entity * EntityResolver::parse(Value* nodeRef)
{
	Value& node = *nodeRef;
	if (nodeRef == nullptr || !node.HasMember(ENTITYRESOLVER_ENTITY_TYPE_NODE)) return nullptr;

	const Value& entityType = node[ENTITYRESOLVER_ENTITY_TYPE_NODE];

	if (!entityType.IsString()) return nullptr;

	Entity* entity = resolve(string(entityType.GetString()));
	entity->unserialize(nodeRef);
	return entity;
}

Dimensions EntityResolver::getDefaultDimensions(Entity * entity)
{
	Dimensions dimensions;
	/*if (entity->getType() == toTypeString(EntityType::rectangle)) {
		dimensions = Rectangle().getDefaultDimensions();
	}
	else if (entity->getType() == toTypeString(EntityType::circle)) {
		dimensions = Circle().getDefaultDimensions();
	}
	else if (entity->getType() == toTypeString(EntityType::square)) {
		dimensions = Square().getDefaultDimensions();
	}*/
	return dimensions;
}

EntityType EntityResolver::fromTypeString(string entityType)
{
	if (entityType == "obstaculo_pinche")
		return EntityType::obstaculo_pinche;
	else if (entityType == "obstaculo_piedra")
		return EntityType::obstaculo_piedra;
	else if (entityType == "anillo")
		return EntityType::anillo;
	else if (entityType == "bonus_super_ring")
		return EntityType::bonus_super_ring;
	else if (entityType == "bonus_invencibilidad")
		return EntityType::bonus_invencibilidad;
	else if (entityType == "bonus_escudo")
		return EntityType::bonus_escudo;
	else if (entityType == "enemigo_cangrejo")
		return EntityType::enemigo_cangrejo;
	else if (entityType == "enemigo_pez")
		return EntityType::enemigo_pez;
	else if (entityType == "enemigo_mosca")
		return EntityType::enemigo_mosca;
	else
		return EntityType::null;
}

string EntityResolver::toTypeString(EntityType entityType)
{
	switch (entityType) {
	case EntityType::obstaculo_pinche:
		return "obstaculo_pinche";
	case EntityType::obstaculo_piedra:
		return "obstaculo_piedra";
	case EntityType::anillo:
		return "anillo";
	case EntityType::bonus_super_ring:
		return "bonus_super_ring";
	case EntityType::bonus_invencibilidad:
		return "bonus_invencibilidad";
	case EntityType::bonus_escudo:
		return "bonus_escudo";
	case EntityType::enemigo_cangrejo:
		return "enemigo_cangrejo";
	case EntityType::enemigo_pez:
		return "enemigo_pez";
	case EntityType::enemigo_mosca:
		return "enemigo_mosca";
	default:
		return "";
	}
}

EntityColor EntityResolver::fromColorString(string entityColor)
{
	if (entityColor == "rojo")
		return EntityColor::red;
	else if (entityColor == "amarillo")
		return EntityColor::yellow;
	else if (entityColor == "verde")
		return EntityColor::green;
	else if (entityColor == "azul")
		return EntityColor::blue;
	else
		return EntityColor::red;
}

string EntityResolver::toColorString(EntityColor entityColor)
{
	switch (entityColor) {
	case EntityColor::red:
		return "rojo";
	case EntityColor::yellow:
		return "amarillo";
	case EntityColor::green:
		return "verde";
	case EntityColor::blue:
		return "azul";
	default:
		return "";
	}
}
