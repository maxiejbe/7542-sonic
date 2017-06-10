#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include "RectangleView.h"

class EnemyView : RectangleView {
public:
	EnemyView(Entity* entity) : RectangleView(entity) {
	}

	virtual void draw(SDL_Rect camera) override;
};

#endif // !ENEMYVIEW_H
