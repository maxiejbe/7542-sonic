#include "EntityResolver.h"
#include "EntityResolver.h"	

Entity* EntityResolver::resolve(Entity* origin)
{
	Entity* destination = nullptr;

	if (origin->getType() == toTypeString(EntityType::obstaculo_pinche) ||
		origin->getType() == toTypeString(EntityType::obstaculo_piedra)) {
		//destination = new Obstacle(origin->getType()); //TODO
	}
	else if (origin->getType() == toTypeString(EntityType::moneda)) {
		//destination = new Ring(origin->getType()); //TODO
	}
	else if (origin->getType() == toTypeString(EntityType::bonus_super_ring) ||
		origin->getType() == toTypeString(EntityType::bonus_invencibilidad) ||
		origin->getType() == toTypeString(EntityType::bonus_escudo)) {
		//destination = new Bonus(origin->getType()); //TODO
	}
	else if (origin->getType() == toTypeString(EntityType::enemigo_cangrejo) ||
		origin->getType() == toTypeString(EntityType::enemigo_pez) ||
		origin->getType() == toTypeString(EntityType::enemigo_mosca)) {
		destination = new Enemy(origin->getType());
	}

	return destination;
}

Entity * EntityResolver::resolve(string entityType)
{
	Entity entity;
	entity.setType(entityType);
	return resolve(&entity);
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
	else if (entityType == "moneda")
		return EntityType::moneda;
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
	case EntityType::moneda:
		return "moneda";
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
