#ifndef RECTANGLE_VIEW_H
#define RECTANGLE_VIEW_H

#include "EntityView.h"

class RectangleView : public EntityView {
public:
	RectangleView();
	RectangleView(Entity* entity) : EntityView(entity) {

	}

	virtual void draw(SDL_Rect camera) override;
	void draw_ex(SDL_Rect camera, SDL_Rect* clip, SDL_Rect dest, SDL_RendererFlip flip);
private:
};

#endif // !RECTANGLE_H
