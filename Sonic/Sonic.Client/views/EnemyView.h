#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include "EntityView.h"
#include "SoundManager.h"

class EnemyView : public EntityView {
public:
	EnemyView(Entity* entity) : EntityView(entity) {
		loadSpriteClips();
	}

	EnemyView(Enemy* enemy);
	~EnemyView();

	virtual void draw(int camX, int camY) override;

	int getFramesDivision();

private:
	int getFramesCount();
	void loadSpriteClips();

	SDL_Rect* spriteClips;
};

#endif // !ENEMYVIEW_H
