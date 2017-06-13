#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include "EntityView.h"

class EnemyView : public EntityView {
public:
	EnemyView(Entity* entity) : EntityView(entity) {
		loadSpriteClips();
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
