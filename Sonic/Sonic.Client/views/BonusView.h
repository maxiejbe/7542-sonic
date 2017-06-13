#ifndef BONUSVIEW_H
#define BONUSVIEW_H

#include "EntityView.h"

class BonusView : public EntityView {
public:
	BonusView(Entity* entity) : EntityView(entity) {
	}

	virtual void draw(SDL_Rect camera) override;

private:
	string getBonusFilePath();
};

#endif // !BONUSVIEW_H
