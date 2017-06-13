#include "BonusView.h"

void BonusView::draw(SDL_Rect camera) {

	if (this->entity->getImagePath() != "") {
		this->entity->setImagePath(getBonusFilePath());
	}

	RectangleView::draw(camera);
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