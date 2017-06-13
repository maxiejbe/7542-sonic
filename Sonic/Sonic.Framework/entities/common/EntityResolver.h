#ifndef I_ENTITY_RESOLVER_H
#define I_ENTITY_RESOLVER_H

#include "../Dimensions.h"
#include "../enemies/Enemy.h"
#include <string>

enum EntityType { obstaculo_pinche, obstaculo_piedra, moneda, bonus_super_ring, bonus_invencibilidad, bonus_escudo, enemigo_cangrejo, enemigo_pez, enemigo_mosca, null };
enum EntityColor { red, yellow, green, blue };

class EntityResolver {
public:
	static Entity* resolve(string);
	static Entity* parse(Value* nodeRef);

	static Dimensions getDefaultDimensions(Entity* entity);

	static EntityType fromTypeString(string entityType);
	static string toTypeString(EntityType entityType);

	static EntityColor fromColorString(string entityColor);
	static string toColorString(EntityColor entityColor);
};
#endif
