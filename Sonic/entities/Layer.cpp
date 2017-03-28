#include "Layer.h"

Layer::Layer()
{
}

Layer::Layer(int idParam, int zIndexParam, string imagePathParam)
{
	id = idParam;
	zIndex = zIndexParam;
	imagePath = imagePathParam;
}
