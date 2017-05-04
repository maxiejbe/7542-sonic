#include "LayerView.h"

const string LAYER_VIEW_DEFAULT_IMAGE_PATH = "img/layer-not-found.png";

LayerView::LayerView(Layer * layer)
{
	this->layer = layer;
}

void LayerView::loadLayer()
{
	string imagePath = this->layer->getImagePath();
	if (!texture.loadFromFile(imagePath)) {
		this->layer->setImagePath(LAYER_VIEW_DEFAULT_IMAGE_PATH);
		loadLayer();
	}
}

void LayerView::renderLayer(int x, int y, SDL_Rect* rect)
{
	texture.render(x, y, rect);
}

void LayerView::destroyLayer()
{
	texture.free();
}


