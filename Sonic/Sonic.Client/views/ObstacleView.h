#ifndef OBSTACLEVIEW_H
#define OBSTACLEVIEW_H

#include "EntityView.h"

class ObstacleView : public EntityView {
public:
	ObstacleView(Entity* entity) : EntityView(entity) {
	}
	~ObstacleView();

	virtual void draw(int camX, int camY) override;
private:
	string getObstacleFilePath();
};

#endif // !OBSTACLEVIEW_H
