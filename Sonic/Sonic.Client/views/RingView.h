#ifndef RINGVIEW_H
#define RINGVIEW_H

#include "EntityView.h"
#include "SoundManager.h"

class RingView : public EntityView {
public:
	RingView(Entity* entity) : EntityView(entity) {
		loadSpriteClips();
	}
	~RingView();

	virtual void draw(int camX, int camY) override;

private:
	void loadSpriteClips();
	SDL_Rect* spriteClips;
};

#endif // !RINGVIEW_H
