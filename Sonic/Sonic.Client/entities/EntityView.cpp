#include "EntityView.h"

const string ENTITY_VIEW_EMPTY_IMAGE_PATH = ""; // Vacio = no hay imagen (solo color)

EntityView::EntityView(Entity * entity)
{
	this->entity = entity;

	this->imageCrop = true;
	if (this->entity->getImagePath() == ENTITY_VIEW_EMPTY_IMAGE_PATH) {
		this->imageCrop = false;
	}
}

void EntityView::draw(SDL_Rect camera)
{
}

Uint32 EntityView::getColorRgba()
{
	int full = 255; //Full of one color
	int r = 0;
	int g = 0;
	int b = 0;

	switch (EntityResolver::fromColorString(this->entity->getColor()))
	{
		case EntityColor::red:
			r = full;
			break;
		case EntityColor::yellow:
			r = full;
			g = full;
			break;
		case EntityColor::green:
			g = full;
			break;
		case EntityColor::blue:
			b = full;
			break;
		default:
			return Uint32();
			break;
	}

	Uint32 colorCode = 0;
	if (SDLWindow::getInstance().gWindow != NULL) {
		colorCode = SDL_MapRGBA(SDL_GetWindowSurface(SDLWindow::getInstance().gWindow)->format, r, g, b, 255);
	}
	else {
		LOG(logERROR) << "No se puede recuperar el color en formato Uint32 - Error: La ventana es nula";
	}

	return colorCode;
}

