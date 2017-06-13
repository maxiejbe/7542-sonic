#include "ObstacleView.h"

void ObstacleView::draw(SDL_Rect camera)
{
	if (this->entity->getImagePath() == "") {
		this->entity->setImagePath(getObstacleFilePath());
	}

	RectangleView::draw(camera);
}

string ObstacleView::getObstacleFilePath()
{
	string type = this->entity->getType();
	if (type == EntityResolver::toTypeString(EntityType::obstaculo_pinche))
		return "img/spikes.png";
	else if (type == EntityResolver::toTypeString(EntityType::obstaculo_piedra))
		return "img/block.png";
	return "";
}