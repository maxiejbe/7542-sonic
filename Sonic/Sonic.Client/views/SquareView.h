#ifndef SQUARE_VIEW_H
#define SQUARE_VIEW_H

#include "EntityView.h"
#include "RectangleView.h"
#include "common/Drawable.h"

class SquareView : public EntityView {
private:
	RectangleView rectangleView;
public:
	SquareView(Entity* entity) : EntityView(entity) {
		rectangleView = RectangleView(entity);
	}
	virtual void draw(SDL_Rect camera) override;
};

#endif // !SQUARE_H
