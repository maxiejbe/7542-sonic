#include "BonusView.h"

void BonusView::draw(int camX, int camY)
{
	// Load image
	if (texture.getTexture() == nullptr && this->entity->getIsActive() && !texture.loadFromFile(getBonusFilePath())) {
		LOG(logWARNING) << "No se pudo cargar la imagen del bonus '" << getBonusFilePath() << "'.";
		return;
	}

	if (!this->entity->getIsActive()) {
		if (texture.getTexture() == nullptr) return;
		texture.free();
	}

	int x = entity->getCoordinate().getX() - camX;
	int y = entity->getCoordinate().getY() - camY;
	int w = entity->getDimensions().getWidth();
	int h = entity->getDimensions().getHeight();

	texture.render(x, y, w, h);
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