#ifndef RINGVIEW_H
#define RINGVIEW_H

#include "CircleView.h"

class RingView : public CircleView {
public:
	RingView(Entity* entity) : CircleView(entity) {
	}

	virtual void draw(SDL_Rect camera) override;
};

#endif // !RINGVIEW_H
