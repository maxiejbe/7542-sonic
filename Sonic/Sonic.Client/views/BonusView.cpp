#include "BonusView.h"

void BonusView::draw(SDL_Rect camera)
{
	// Load image
	if (texture.getTexture() == nullptr && !texture.loadFromFile(getBonusFilePath())) {
		LOG(logWARNING) << "No se pudo cargar la imagen del bonus '" << getBonusFilePath() << "'.";
		return;
	}

	int x = entity->getCoordinate().getX() - camera.x;
	int y = entity->getCoordinate().getY() - camera.y;

	texture.render(x, y, &camera);
}

string BonusView::getBonusFilePath() {
	string type = this->entity->getType();

	if (type == EntityResolver::toTypeString(EntityType::bonus_escudo))
		return "img/bonus-shield.png";
	if (type == EntityResolver::toTypeString(EntityType::bonus_invencibilidad))
		return "img/bonus-invincibility.png";
	if (type == EntityResolver::toTypeString(EntityType::bonus_super_ring))
		return "img/bonus-rings.png";

	return "";

}