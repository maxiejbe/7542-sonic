#include "EntityViewResolver.h"

EntityView * EntityViewResolver::resolve(Entity * origin)
{
	EntityView* destination = nullptr;

	if (origin->getType() == EntityResolver::toTypeString(EntityType::obstaculo_pinche) ||
		origin->getType() == EntityResolver::toTypeString(EntityType::obstaculo_piedra)) {
		destination = new ObstacleView(origin);
	}
	else if (origin->getType() == EntityResolver::toTypeString(EntityType::moneda)) {
		destination = new RingView(origin);
	}
	else if (origin->getType() == EntityResolver::toTypeString(EntityType::bonus_super_ring) ||
		origin->getType() == EntityResolver::toTypeString(EntityType::bonus_invencibilidad) ||
		origin->getType() == EntityResolver::toTypeString(EntityType::bonus_escudo)) {
		destination = new BonusView(origin);
	}
	else if (origin->getType() == EntityResolver::toTypeString(EntityType::enemigo_cangrejo) ||
		origin->getType() == EntityResolver::toTypeString(EntityType::enemigo_pez) ||
		origin->getType() == EntityResolver::toTypeString(EntityType::enemigo_mosca)) {
		destination = new EnemyView(origin);
	}

	return destination;
}
