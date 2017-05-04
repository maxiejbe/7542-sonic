#ifndef RECTANGLE_VIEW_H
#define RECTANGLE_VIEW_H

#include "EntityView.h"

class RectangleView : public EntityView {
public:
	RectangleView();
	RectangleView(Entity* entity) : EntityView(entity) {

	}

	virtual void draw(SDL_Rect camera) override;
};

#endif // !RECTANGLE_H
