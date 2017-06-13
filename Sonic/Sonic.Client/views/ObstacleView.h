#ifndef OBSTACLEVIEW_H
#define OBSTACLEVIEW_H

#include "RectangleView.h"

class ObstacleView : public RectangleView {
public:
	ObstacleView(Entity* entity) : RectangleView(entity) {
	}

	virtual void draw(SDL_Rect camera) override;
private:
	string getObstacleFilePath();
};

#endif // !OBSTACLEVIEW_H
