#ifndef I_ENTITY_RESOLVER_H
#define I_ENTITY_RESOLVER_H

#include "../Rectangle.h"
#include "../Circle.h"
#include "../Square.h"
#include "../Dimensions.h"
#include <string>

//enum EntityType { obstaculo_pinche, obstaculo_piedra, moneda, bonus_super_ring, bonus_invencibilidad, bonus_escudo, cangrejo, pez, mosca, null };
enum EntityType { rectangle, circle, square, null };

enum EntityColor {  red, yellow, green, blue };

class EntityResolver {
public: 
	static Entity* resolve(Entity* origin);
	static Entity* resolve(string);

	static Dimensions getDefaultDimensions(Entity* entity);

	static EntityType fromTypeString(string entityType);
	static string toTypeString(EntityType entityType);

	static EntityColor fromColorString(string entityColor);
	static string toColorString(EntityColor entityColor);
};
#endif
