#include "EntityController.h"

bool EntityController::isEntityVisible(Entity * entity, Camera * camera)
{
	int entityPosition = entity->getCoordinate().getX();

	int maxCameraRightBorder = camera->getPosition().x + camera->getScreenWidth() + entity->getMaxHorizontalDistance() + entity->getDimensions().getWidth();
	int maxCameraLeftBorder = camera->getPosition().x - entity->getMaxHorizontalDistance() - entity->getDimensions().getWidth();

	if (entityPosition > maxCameraRightBorder) {
		return false;
	}

	if (entityPosition < maxCameraLeftBorder) {
		return false;
	}

	return true;
}