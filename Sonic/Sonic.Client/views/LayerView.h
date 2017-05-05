#ifndef LAYER_VIEW_H
#define LAYER_VIEW_H

#include <string>
#include "entities/Layer.h"
#include "Texture.h"

using namespace std;

class LayerView {
public:
	LayerView(Layer* layer);
	void loadLayer();
	void renderLayer(int x, int y, SDL_Rect* rect);
	void destroyLayer();
private:
	Texture texture;
	Layer* layer;
};

#endif