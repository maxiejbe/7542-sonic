#ifndef LAYER_H
#define LAYER_H

#include <string>
#include "common/Serializable.h"
#include "Texture.h"

using namespace std;

class Layer : public Serializable {
public:
	Layer();

	int getZIndex();
	
	string getImagePath();

	bool loadLayer();

	void renderLayer(int x, int y, SDL_Rect* rect);

	void destroyLayer();

private:
	int id;
	int zIndex;
	string imagePath;
	Texture layer;

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif