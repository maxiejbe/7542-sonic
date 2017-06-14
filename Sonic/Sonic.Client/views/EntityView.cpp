#include "EntityView.h"

const string ENTITY_VIEW_EMPTY_IMAGE_PATH = ""; // Vacio = no hay imagen (solo color)

EntityView::EntityView()
{
}

EntityView::EntityView(Entity * entity)
{
	this->entity = entity;

	this->imageCrop = true;
	if (this->entity->getImagePath() == ENTITY_VIEW_EMPTY_IMAGE_PATH) {
		this->imageCrop = false;
	}
}

EntityView::~EntityView()
{

}

void EntityView::draw(int camX, int camY)
{
}

Entity * EntityView::getEntity()
{
	return this->entity;
}

