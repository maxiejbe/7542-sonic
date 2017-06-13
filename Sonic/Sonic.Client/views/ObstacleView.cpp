#include "ObstacleView.h"

void ObstacleView::draw(int camX, int camY)
{
	// Load image
	if (texture.getTexture() == nullptr && !texture.loadFromFile(getObstacleFilePath())) {
		LOG(logWARNING) << "No se pudo cargar la imagen del obstaculo '" << getObstacleFilePath() << "'.";
		return;
	}

	int x = entity->getCoordinate().getX() - camX;
	int y = entity->getCoordinate().getY() - camY;
	int w = entity->getDimensions().getWidth() * 3;
	int h = entity->getDimensions().getHeight() * 3;

	texture.render(x, y, w, h);
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