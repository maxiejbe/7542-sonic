#ifndef ENTITY_VIEW_H
#define ENTITY_VIEW_H

#include <string>
#include <SDL.h>
#include "../Renderer.h"
#include "Texture.h"
#include "common/Drawable.h"
#include "entities/common/EntityResolver.h"
#include <iostream>

using namespace std;

class EntityView : public Drawable {
public:
	EntityView();
	EntityView(Entity* entity);

	void draw(SDL_Rect camera) override;
	Uint32 getColorRgba();

protected:
	Texture texture;
	bool imageCrop;

	Entity* entity;
};

#endif