#include "ObstacleView.h"

void ObstacleView::draw(SDL_Rect camera)
{
	// Load image
	if (texture.getTexture() == nullptr && !texture.loadFromFile(getObstacleFilePath())) {
		LOG(logWARNING) << "No se pudo cargar la imagen del obstaculo '" << getObstacleFilePath() << "'.";
		return;
	}

	int x = entity->getCoordinate().getX() - camera.x;
	int y = entity->getCoordinate().getY() - camera.y;

	texture.render(x, y, &camera);
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