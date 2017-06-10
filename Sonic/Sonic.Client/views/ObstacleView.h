#ifndef OBSTACLEVIEW_H
#define OBSTACLEVIEW_H

#include "RectangleView.h"

class ObstacleView : RectangleView {
public:
	ObstacleView(Entity* entity) : RectangleView(entity) {
	}

	virtual void draw(SDL_Rect camera) override;
};

#endif // !OBSTACLEVIEW_H
