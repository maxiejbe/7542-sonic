#ifndef OBSTACLEVIEW_H
#define OBSTACLEVIEW_H

#include "EntityView.h"

class ObstacleView : public EntityView {
public:
	ObstacleView(Entity* entity) : EntityView(entity) {
	}

	virtual void draw(SDL_Rect camera) override;
private:
	string getObstacleFilePath();
};

#endif // !OBSTACLEVIEW_H
