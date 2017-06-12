#ifndef BONUSVIEW_H
#define BONUSVIEW_H

#include "RectangleView.h"

class BonusView : public RectangleView {
public:
	BonusView(Entity* entity) : RectangleView(entity) {
	}
	~BonusView();

	virtual void draw(SDL_Rect camera) override;

private:
	SDL_Rect** spriteClips;
};

#endif // !BONUSVIEW_H
