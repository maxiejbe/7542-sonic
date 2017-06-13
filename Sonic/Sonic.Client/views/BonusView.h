#ifndef BONUSVIEW_H
#define BONUSVIEW_H

#include "RectangleView.h"

class BonusView : public RectangleView {
public:
	BonusView(Entity* entity) : RectangleView(entity) {
	}

	virtual void draw(SDL_Rect camera) override;

private:
	string getBonusFilePath();
};

#endif // !BONUSVIEW_H
