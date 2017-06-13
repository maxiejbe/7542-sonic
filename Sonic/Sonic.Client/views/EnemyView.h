#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include "RectangleView.h"

class EnemyView : public RectangleView {
public:
	EnemyView(Entity* entity) : RectangleView(entity) {
	}

	EnemyView(Enemy* enemy);
	~EnemyView();

	virtual void draw(SDL_Rect camera) override;

private:
	int getFramesCount();
	void loadSpriteClips();

	SDL_Rect* spriteClips;
};

#endif // !ENEMYVIEW_H
